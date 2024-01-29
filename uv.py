import time
import datetime
import csv
import board
import busio
import adafruit_veml6075

i2c = busio.I2C(board.SCL, board.SDA)

veml = adafruit_veml6075.VEML6075(i2c, integration_time=100)

csv_file = open("Altimeter.csv", mode="w")
output_storage = csv.writer(csv_file, delimiter=",")
output_storage.writerow(["Time","Pressure"])

while True:
    uv = veml.uv_index
    now = datetime.now()
    output_storage.writerow([now,uv])
    time.sleep(1)