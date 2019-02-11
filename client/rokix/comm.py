import os
import sys
import subprocess
import signal
import time
import serial
import serial.tools.list_ports as list_ports
from rokix.exception import RoKiXException, RoKiXTimeoutException
from rokix import logger
LOGGER = logger.get_logger(__name__)

LOGGER.setLevel(logger.INFO)
# LOGGER.setLevel(logger.ERROR)
# LOGGER.setLevel(logger.DEBUG)

try:
    import pygatt
except ImportError:
    pygatt = None


class Connection(object):
    """Base class of the connection classes."""
    config = None

    def flush(self):
        """Discard any data from input buffers."""
        raise NotImplementedError()

    def read(self, length):
        """Read data.

        Args:
            length (int): Amount of bytes to read.

        Raises:
            RoKiXTimeoutException: The read timed out.

        Returns:
            array.array: Read bytes.
        """
        raise NotImplementedError()

    def write(self, data):
        """Write data.

        Args:
            data (array.array): Array of bytes to send.
        """
        raise NotImplementedError()

    def close(self):
        raise NotImplementedError()


class PySerialConnection(Connection):
    """Base class of all connections through pyserial."""
    def __init__(self):
        self._ser_conn = None  # pyserial connection instance

    def read(self, length=1):
        """Read data from the pyserial connection."""
        data = self._ser_conn.read(length)
        if not data:
            raise RoKiXTimeoutException('No data received.')

        return data

    def flush(self):
        """Flush the input buffers of the pyserial connection."""
        if self._ser_conn.in_waiting:
            self._ser_conn.reset_input_buffer()

    def write(self, data):
        """Write data to the pyserial connection."""
        LOGGER.debug(data)
        self._ser_conn.write(data)

    def close(self):
        """Close the pyserial connection."""
        self._ser_conn.close()


class WinBLEConnection(PySerialConnection):
    """A Windows BLE connection.

    Requires that the BLE-to-socket streamer binary, B2S.exe, is
    located in the working directory or in the directory in which this
    file resides.
    """
    def __init__(self):
        PySerialConnection.__init__(self)
        self._b2s_proc = None  # B2S subprocess instance

    def _start_child_process(self, port, mac_address):
        # https://msdn.microsoft.com/en-us/library/windows/desktop/ms684863(v=vs.85).aspx
        # CREATE_NEW_PROCESS_GROUP=0x00000200 -> If this flag is
        # specified, CTRL+C signals will be disabled
        startupinfo = subprocess.STARTUPINFO()
        startupinfo.dwFlags |= subprocess.STARTF_USESHOWWINDOW
        thispath, _ = os.path.split(__file__)
        b2s_path1 = os.path.join(thispath, 'B2S.exe')
        b2s_path2 = 'B2S.exe'

        if os.path.isfile(b2s_path1):
            b2s_path = b2s_path1
        elif os.path.isfile(b2s_path2):
            b2s_path = b2s_path2
        else:
            raise RoKiXException(
                'B2S.exe not found. It should be located in the working directory or in %s'
                % os.path.split(__file__)[0])

        if mac_address != '':
            self._b2s_proc = subprocess.Popen(
                b2s_path + ' -p %s -m %s' % (port,
                                             mac_address),
                startupinfo=startupinfo,
                creationflags=0x00000200,
                universal_newlines=True,
                stdout=subprocess.PIPE)  # pipe stdout to see only errors in console
        else:
            self._b2s_proc = subprocess.Popen(
                b2s_path + ' -p %s' % port,
                startupinfo=startupinfo,
                creationflags=0x00000200,
                universal_newlines=True,
                stdout=subprocess.PIPE)  # pipe stdout to see only errors in console

        # Check that b2s has established socket connection.
        while True:
            line = self._b2s_proc.stdout.readline()
            if line != '':
                if line.rstrip().startswith('Waiting for a connection'):
                    break
            else:
                time.sleep(1)
                break

    def _stop_child_process(self):
        # NOTE: Must use CTRL + BREAK event instead of CTRL + C, which has been disabled
        os.kill(self._b2s_proc.pid, signal.CTRL_BREAK_EVENT)

    def initialize(self, socket_port=8100, mac_address='', timeout=2):
        """Initialize the B2S connection. (Windows BLE to socket streamer)

        Args:
            socket_port (int): Socket port number (e.g. 8100).
            mac_address (str): Mac address of BLE device (if empty, the
                first found device is connected).
            timeout (float, optional): Read timeout in seconds.
        """
        self._start_child_process(socket_port, mac_address)
        self._ser_conn = serial.serial_for_url('socket://localhost:%d' % socket_port,
                                               timeout=timeout)

    def close(self):
        """Close the socket connection."""
        self._stop_child_process()
        super(WinBLEConnection, self).close()


class LinuxBLEConnection(Connection):
    def __init__(self, _=None):
        if pygatt is None:
            raise RuntimeError('pygatt could not be imported')

        # Many devices, e.g. Fitbit, use random addressing - this is
        # required to connect.
        self.ADDRESS_TYPE = pygatt.BLEAddressType.random
        self.NUS_TX_CHARACTERISTIC = '6E400002-B5A3-F393-E0A9-E50E24DCCA9E'
        self.NUS_RX_CHARACTERISTIC = '6E400003-B5A3-F393-E0A9-E50E24DCCA9E'

        self.rx_buffer = []
        timeout = 1
        self.timeout = timeout
        # Connected BLE device.
        self.device = None

    def initialize(self, mac_address):
        LOGGER.info('Establishing BLE connection to %s.', mac_address)
        adapter = pygatt.GATTToolBackend()
        adapter.start()
        self.device = adapter.connect(mac_address, address_type=self.ADDRESS_TYPE)
        self.device.subscribe(self.NUS_RX_CHARACTERISTIC, self.callback, False)
        LOGGER.info('BLE connection established.')

    def read(self, length=1):
        data = ''
        for _ in range(100):
            if len(self.rx_buffer) >= length:
                break
            time.sleep(self.timeout / 100.0)

        if not len(self.rx_buffer) >= length:
            raise RoKiXTimeoutException(
                'Not enough data received. Expected %d bytes, received %d.'
                % (length, len(self.rx_buffer)))

        for _ in range(length):
            data += chr(self.rx_buffer.pop(0))
        return data

    def write(self, data):
        LOGGER.debug(data)
        self.device.char_write(self.NUS_TX_CHARACTERISTIC, bytearray(data), True)

    def flush(self):
        self.rx_buffer = []

    def close(self):
        self.flush()
        self.device.disconnect()

    def callback(self, handle, value):
        for i in value:
            self.rx_buffer.append(i)


class SerialConnection(PySerialConnection):
    """Serial port connection.

    Attributes:
        config (dict): Connection configuration.
        baudrate (int): Baud rate.
    """
    def __init__(self, config=None):
        PySerialConnection.__init__(self)

    def initialize(self, comport, timeout=2):
        """Initialize the serial connection.

        Args:
            comport (str): Name of the serial device
                (e.g. 'COM9' or '/dev/ttyACM0').
            timeout (float, optional): Read timeout in seconds.
        """
        self._ser_conn = serial.Serial(port=comport, timeout=timeout)

    def get_com_port(self):
        """Autodetect connected serial devices and return their names.

        Raises:
            EvaluationKitException: Autodetection found no devices.

        Returns:
            List[str]: The names of the detected serial devices
                (e.g. ['COM2']).
        """
        matching_ports = []
        LOGGER.debug('Listing serial ports.')
        for port in list_ports.comports():
            LOGGER.debug(port.name)
            LOGGER.debug(port.description)
            LOGGER.debug(port.vid)
            LOGGER.debug(port.pid)

            # matcing port found based in vid and pid?
            if port.vid == 1205 and port.pid == 1538:
                matching_ports.append(port.device)
                continue

        if not matching_ports:
            raise RoKiXException('Automatic search found no suitable devices.')

        return matching_ports



