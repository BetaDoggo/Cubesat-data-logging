import httplib2
from apiclient import discovery
from google.oauth2 import service_account

import os
import serial
import csv
import time
import datetime

serialport = '/dev/ttyACM0'
record_delay = 1
file = 'test.csv' #local output file
mode = 'w' #write mode - a to append, w to overwrite. - csv only
sheet_id = "1sEDggr_FbgNbnXzKLG-3iYj2N4-BMM2zQLfWGCZCi6g" #spreadsheet id, only if outputing to google sheets
token = ("/home/mrp/Desktop/auth.json") #service account credentials
online_mode = 0 # Whether or not to write to google sheet

def auth(): #authenticate api
    global api
    try:
        scopes = ["https://www.googleapis.com/auth/drive", "https://www.googleapis.com/auth/drive.file", "https://www.googleapis.com/auth/spreadsheets"]
        creds = service_account.Credentials.from_service_account_file(token, scopes=scopes)
        api = discovery.build("sheets", "v4", credentials=creds) 
    except Exception as e:
        print(e)


def main():
    global api
    row = 2 #stores the row count - start at two because of heading
    ser = serial.Serial(serialport, 115200) #init serial monitor
    csv_file = open(file, mode=mode) #open file
    output_storage = csv.writer(csv_file, delimiter=",")
    time.sleep(2) #delay for arduino startup
    output_storage.writerow(["Recorded time","Arduino time","row","altitude","barometer","temp","pressure","accel(X)","accel(Y)","accel(Z)","Radiation", "UV"]) #write heading
    while True:
        range = ("Sheet1!A" + str(row) + ":L" + str(row)) #sets the range for the online sheet
        output = ser.readline()
        recordtime = datetime.datetime.now() #get time of retrieval - backup for rtc on arduino, also
        output = output.decode('utf-8')
        data = str(output).split(",")
        #print(data) #uncomment for a live feed in terminal
        try: #catch incomplete/broken data
            output_storage.writerow([data[0],recordtime,data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8],data[9],data[10]]) #could be done with a loop but this is more explicit
            row = row + 1
            if (online_mode == 1): #send to sheets
                try:
                    values = [[data[0],str(recordtime),data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8],data[9],data[10]],[]] #data must be 2d list 🤓
                    sheet_output = {"values" : values}
                    api.spreadsheets().values().update(spreadsheetId=sheet_id, body=sheet_output, range=range, valueInputOption='USER_ENTERED').execute()
                except Exception as e:
                    #print(e)
                    print("Writing to Google sheets failed")
        except Exception as e:
            #print(e) 
            print("Incomplete output 💢💢💢")
        
        time.sleep(record_delay)
        
if (online_mode == 1):
    auth()
main()