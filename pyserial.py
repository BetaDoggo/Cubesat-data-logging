import serial
import csv
import time

serialport = '/dev/ttyACM0'
record_delay = 1

def main():
    ser = serial.Serial(serialport, 115200) #init serial monitor
    rowcount = 0
    time.sleep(2)
    with open('test.csv', mode='w') as output_storage:
        output_storage = csv.writer(output_storage, delimiter=",", quotechar='"', quoting=csv.QUOTE_MINIMAL)
        output_storage.writerow(["timestamp: ","altitude: ","Baro: ","temp: ","pressure: ","accel(X): ","accel(Y): ","accel(Z): ","Rad: ", "UV: "])
        while True:
            output = ser.readline()
            output = output.decode('utf-8')
            #print(output)
            data = str(output).split(",")
            try:
                output_storage.writerow([data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8],data[9]])
                rowcount = rowcount + 1
                print("row " + str(rowcount))
            except Exception as e:
                #print(e)
                print("Serial bad 💢")
            time.sleep(record_delay)
            

main()