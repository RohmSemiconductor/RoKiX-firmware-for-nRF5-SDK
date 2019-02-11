import struct, sys
from rokix import comm
from rokix import sensorlib


def conn_usb_serial():
    conn = comm.SerialConnection()
    
    # connet to RoKiX node which is found first during USB device scan
    conn.initialize(conn.get_com_port()[0])
    return conn

def conn_ble(mac_address_str=None):
    if sys.platform.startswith('win32'):
        conn = comm.WinBLEConnection()

    elif sys.platform.startswith('linux'):
        conn = comm.LinuxBLEConnection(None)

    else:
        raise RuntimeError('BLE is not supported on %s' % sys.platform)

    conn.initialize(mac_address=mac_address_str)
    return conn

def connect():
    #
    # Open connection 

    # Select which way to connect USB or BLE
    
    conn = conn_usb_serial() # Open USB connection

    # mac='FD:8A:F0:1C:88:E6' # TODO change to mac address of your RoKiX Sensor Node
    # conn = conn_ble(mac) # Open BLE connection
    return conn

def read_raw_data(conn):
    #
    # Define how to interprent received data
    # 

    # formatter string defines how to interpret data
    # https://docs.python.org/2/library/struct.html#format-characters

    fmt = 'hhh' # hhh = three signed 16 bit values

    #
    # Receive data until CTRL+C is pressed
    # 

    while True:

        # read data from RoKiX Sensor Node
        data =conn.read(length=struct.calcsize(fmt))

        # covert binary data to list of values
        value_list = struct.unpack(fmt, data)

        # print values in separate colums
        print('%d\t'*len(value_list) % value_list)

def read_sensor_data(conn):

    #
    # Create sensor for data reading and interpreting
    # 
    sensor = sensorlib.KX122(conn)

    #
    # Receive data until CTRL+C is pressed
    # 
    while True:
        sample = sensor.convert_sample(sensor.read_raw_sample())
        print(',    '.join(['{:5s} {:9.3f}'.format(k, v) for k, v in sample.items()]))



if __name__ == '__main__':
    connection = connect()

    # select which way to read data from the RoKiX sensor node
    read_raw_data(connection)
    # read_sensor_data(connection)
