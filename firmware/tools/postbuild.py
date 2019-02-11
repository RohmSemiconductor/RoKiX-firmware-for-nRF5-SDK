"""A post-build script for the RoKiX Sensor Node template application.

Requirements:

- Python 2.7 or 3.x.
- `nrfutil` must be installed and in PATH.
- the nRF5x Command Line Tools must be installed and in PATH.

"""
import shutil
import os
import argparse
import subprocess


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("APP_HEX_PATH", help="path to the application hex-file")
    parser.add_argument(
        "OUT_NAME",
        help="name of the firmware output file without any extensions")
    args = parser.parse_args()
    return (os.path.abspath(args.APP_HEX_PATH), args.OUT_NAME)


def merge_hex_files(in_paths, out_path):
    args = ["mergehex", "-m"]
    args.extend(in_paths)
    args.extend(["-o", out_path])
    subprocess.check_call(args)


def main():
    app_hex_path, out_name = parse_args()
    
    dfu_zip_path, filename = os.path.split(app_hex_path)
    
    dfu_zip_path = os.path.join(dfu_zip_path, "{}.zip".format(out_name))
    
    subprocess.check_call([
        "nrfutil", "pkg", "generate",
        "--application", app_hex_path,
        "--hw-version", "52",
        "--application-version", "1",
        "--sd-req", "0x00A9,0x00AE",
        dfu_zip_path])


if __name__ == "__main__":
    main()
