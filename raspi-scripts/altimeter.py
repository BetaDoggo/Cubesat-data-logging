import time
import csv
import board
import adafruit_bmp3xx

i2c = board.I2C()  # uses board.SCL and board.SDA

bmp = adafruit_bmp3xx.BMP3XX_I2C(i2c)

bmp.pressure_oversampling = 8
bmp.temperature_oversampling = 2

csv_file = open("Altimeter.csv", mode="w")
output_storage = csv.writer(csv_file, delimiter=",")
output_storage.writerow(["Pressure","Temperature","Altitude"])

while True:
    Pressure = bmp.pressure
    Temperature = bmp.temperature
    Altitude = bmp.altitude(1013.25)
    output_storage.writerow([Pressure,Temperature,Altitude])
    time.sleep(1)