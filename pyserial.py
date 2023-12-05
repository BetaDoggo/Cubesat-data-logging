import httplib2
from apiclient import discovery
from google.oauth2 import service_account

import os
import serial
import csv
import time

serialport = '/dev/ttyACM0'
record_delay = 1
file = 'test.csv' #local output file
mode = 'w' #write mode - a to append, w to overwrite.
sheet_id = "1sEDggr_FbgNbnXzKLG-3iYj2N4-BMM2zQLfWGCZCi6g" #spreadsheet id, only if outputing to google sheets

def auth(): #authenticate api
    global api
    try:
        scopes = ["https://www.googleapis.com/auth/drive", "https://www.googleapis.com/auth/drive.file", "https://www.googleapis.com/auth/spreadsheets"]
        token = ("/home/mrp/Desktop/auth.json")
        creds = service_account.Credentials.from_service_account_file(token, scopes=scopes)
        api = discovery.build("sheets", "v4", credentials=creds) #sheet object used for writing
    except Exception as e:
        print(e)


def main():
    global api
    row = 2 #stores the row count - start at two because of heading
    ser = serial.Serial(serialport, 115200) #init serial monitor
    csv_file = open(file, mode=mode) #open file
    output_storage = csv.writer(csv_file, delimiter=",")
    time.sleep(2)
    output_storage.writerow(["timestamp","altitude","barometer","temp","pressure","accel(X)","accel(Y)","accel(Z)","Radiation", "UV"]) #write heading
    while True:
        range = ("Sheet1!A" + str(row) + ":J" + str(row)) #sets the range for the online sheet
        output = ser.readline()
        output = output.decode('utf-8')
        data = str(output).split(",")
        #print(data) #uncomment for a live feed in terminal
        try: #catch incomplete/broken data
            output_storage.writerow([data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8],data[9]]) #could be done with a loop but this is more explicit
            #write to online sheet - comment out to disable
            values =[[data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8],data[9]],[]] 
            sheet_output = {"values" : values}
            api.spreadsheets().values().update(spreadsheetId=sheet_id, body=sheet_output, range=range, valueInputOption='USER_ENTERED').execute()
            row = row + 1
        except Exception as e:
            #print(e) 
            print("Incomplete output 💢💢💢")
        time.sleep(record_delay)
        

auth()
main()