import serial
import csv
import time

serialport = '/dev/ttyACM0'
record_delay = 1
file = 'test.csv'
mode = 'w' #write mode - a to append, w to overwrite.

def main():
    ser = serial.Serial(serialport, 115200) #init serial monitor
    csv_file = open(file, mode=mode) #open file
    output_storage = csv.writer(csv_file, delimiter=",")
    time.sleep(2)
    output_storage.writerow(["timestamp","altitude","barometer","temp","pressure","accel(X)","accel(Y)","accel(Z)","Radiation", "UV"])
    while True:
        output = ser.readline()
        output = output.decode('utf-8')
        data = str(output).split(",")
        print(data) #for a live feed
        try: #catch incomplete/broken data
            output_storage.writerow([data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8],data[9]]) #could be done with a loop but this is more explicit
        except Exception as e:
            #print(e) 
            print("Incomplete output 💢💢💢")
            time.sleep(record_delay)

main()