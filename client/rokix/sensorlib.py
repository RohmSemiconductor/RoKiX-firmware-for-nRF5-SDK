import struct
from collections import OrderedDict

class BaseSensor(object):
    def read_raw_sample(self):
        pass

    def convert_sample(self, sample):
        pass


class KX122(BaseSensor):
    def __init__(self, connection):
        self._conn = connection
        # Unpack format for struct.unpack().
        self._unpack_fmt = '<hhh'
        self._read_size = struct.calcsize(self._unpack_fmt)

    def read_raw_sample(self):
        raw_data = self._conn.read(self._read_size)
        unpacked_data = struct.unpack(self._unpack_fmt, raw_data)
        return OrderedDict([
            ('acc_x', unpacked_data[0]),
            ('acc_y', unpacked_data[1]),
            ('acc_z', unpacked_data[2]),
        ])

    def convert_sample(self, sample):
        """Convert a raw sample's values into g's."""
        # Calculated for a 2g range.
        f = lambda x: (x * 1.99994) / (2**15 - 1)
        names = ['acc_x', 'acc_y', 'acc_z']
        return OrderedDict(zip(names, map(f, sample.values())))


class KXG08(BaseSensor):
    def __init__(self, connection):
        self._conn = connection
        # Unpack format for struct.unpack().
        self._unpack_fmt = '<hhhhhhh'
        self._read_size = struct.calcsize(self._unpack_fmt)

    def read_raw_sample(self):
        raw_data = self._conn.read(self._read_size)
        unpacked_data = struct.unpack(self._unpack_fmt, raw_data)
        return OrderedDict([
            # Temperature.
            ('temp', unpacked_data[0]),
            # Gyro x, y, and z.
            ('gyro_x', unpacked_data[1]),
            ('gyro_y', unpacked_data[2]),
            ('gyro_z', unpacked_data[3]),
            # Accelerometer x, y, and z.
            ('acc_x', unpacked_data[4]),
            ('acc_y', unpacked_data[5]),
            ('acc_z', unpacked_data[6]),
        ])

    def convert_sample(self, sample):
        # No open specification for this sensor.
        raise NotImplementedError()


class KMX62(BaseSensor):
    def __init__(self, connection):
        self._conn = connection
        # Unpack format for struct.unpack().
        self._unpack_fmt = '<hhhhhhh'
        self._read_size = struct.calcsize(self._unpack_fmt)

    def read_raw_sample(self):
        raw_data = self._conn.read(self._read_size)
        unpacked_data = struct.unpack(self._unpack_fmt, raw_data)
        return OrderedDict([
            # Accelerometer x, y, and z.
            ('acc_x', unpacked_data[0]),
            ('acc_y', unpacked_data[1]),
            ('acc_z', unpacked_data[2]),
            # Magnetometer x, y, and z.
            ('mag_x', unpacked_data[3]),
            ('mag_y', unpacked_data[4]),
            ('mag_z', unpacked_data[5]),
            # Temperature.
            ('temp', unpacked_data[6]),
        ])

    def convert_sample(self, sample):
        """Convert a raw sample's values into other units.

        - Acceleration values are converted to g's.
        - Magnetometer values are converted to microteslas
        - Temperature values are converted to celsius.
        """
        return OrderedDict([
            # Accelerometer x, y, and z.
            ('acc_x', self._convert_acceleration(sample['acc_x'])),
            ('acc_y', self._convert_acceleration(sample['acc_y'])),
            ('acc_z', self._convert_acceleration(sample['acc_z'])),
            # Magnetometer x, y, and z.
            ('mag_x', self._convert_magnetic_field(sample['mag_x'])),
            ('mag_y', self._convert_magnetic_field(sample['mag_y'])),
            ('mag_z', self._convert_magnetic_field(sample['mag_z'])),
            # Temperature.
            ('temp', self._convert_temp(sample['temp'])),
        ])

    @staticmethod
    def _convert_acceleration(value):
        # This equation is only valid for a 2g range.
        return (value * 1.99994) / (2**15 - 1)

    @staticmethod
    def _convert_magnetic_field(value):
        return (value * 1199.96338) / (2**15 - 1)

    @staticmethod
    def _convert_temp(value):
        return (value * (40.0 + 85.0)) / (10240 + 21760)


class BM1383AGLV(BaseSensor):
    def __init__(self, connection):
        self._conn = connection
        # Unpack format for struct.unpack().
        self._unpack_fmt = '>BBBBh'
        self._read_size = struct.calcsize(self._unpack_fmt)

    def read_raw_sample(self):
        raw_data = self._conn.read(self._read_size)
        unpacked_data = struct.unpack(self._unpack_fmt, raw_data)
        return OrderedDict([
            ('status', unpacked_data[0]),
            # Pressure.
            ('pres_msb', unpacked_data[1]),
            ('pres_lsb', unpacked_data[2]),
            ('pres_xl', unpacked_data[3]),
            # Temperature.
            ('temp', unpacked_data[4]),
        ])

    def convert_sample(self, sample):
        return OrderedDict([
            ('status', sample['status']),
            ('pres', self._convert_pressure(sample['pres_msb'],
                                            sample['pres_lsb'],
                                            sample['pres_xl'])),
            ('temp', self._convert_temp(sample['temp'])),
        ])

    @staticmethod
    def _convert_pressure(msb, lsb, xl):
        # The result is in hPa.
        counts = (msb * 2**14) + (lsb * 2**6) + (xl & 0x1f)
        return counts / 2048

    @staticmethod
    def _convert_temp(value):
        # The result is in degrees Celsius.
        return value / 32


class BM1422GMV(BaseSensor):
    def __init__(self, connection):
        self._conn = connection
        # Unpack format for struct.unpack().
        self._unpack_fmt = '<Hhhh'
        self._read_size = struct.calcsize(self._unpack_fmt)

    def read_raw_sample(self):
        raw_data = self._conn.read(self._read_size)
        unpacked_data = struct.unpack(self._unpack_fmt, raw_data)
        return OrderedDict([
            # Temperature.
            ('temp', unpacked_data[0]),
            # Magnetometer x, y, and z.
            ('magx', unpacked_data[1]),
            ('magy', unpacked_data[2]),
            ('magz', unpacked_data[3]),
        ])

    def convert_sample(self, sample):
        raise NotImplementedError()
