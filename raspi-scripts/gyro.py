import time
import csv
import board
import adafruit_mpu6050

i2c = board.I2C()

mpu = adafruit_mpu6050.MPU6050(i2c)

csv_file = open("gyro.csv", mode="w")
output_storage = csv.writer(csv_file, delimiter=",")
output_storage.writerow(['Xaccel','Yaccel','Zaccel','Xgyro','Ygyro','Zgyro','Temp'])

while True:
    Xaccel, Yaccel, Zaccel = mpu.acceleration
    Xgyro, Ygyro, Zgyro = mpu.gyro
    output_storage.writerow([Xaccel,Yaccel,Zaccel,Xgyro,Ygyro,Zgyro])
    time.sleep(1000)