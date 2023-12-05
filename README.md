# Cubesat-data-logging - WIP
This repo contains an alternative method for recording data sent from the serial monitor. This aproach is OS and software agnostic, all you need is python 3.9+.

# What it does:
1. Gets serial output from the arduino
2. Puts it into a csv file
3. Outputs to test.csv
4. (Optional - output to google sheet)

# How to use:
1. Clone the repo
2. install the dependancies for the python script
3. Change the serial_port and file variables to match your setup
3. Flash the code to the arduino
4. Connect the arduio and run the python script
5. (optional) Set the online_mode variable to 1
6. (optional) Get your sheet_id and account token by reading the following: https://denisluiz.medium.com/python-with-google-sheets-service-account-step-by-step-8f74c26ed28e
7. (optional) Replace each value in the script

# Info

This is a work in progress which is tailored to our specific setup. You will have to change things to make it work for your own setup. Primarily the "serialport" variable and number of data[] entries in your writerow line. Because Serial tends to return incomplete data I added a try statement so that it doesn't break. This incomplete data is just thrown out.

# Important note:
The arduino will reset when the script is run due to the serial initialization. This is a feature of the arduino. This is probably not ideal in most cases. The common fix for this feature is to put a 10uF capacitor between the RESET and GND pins.

I claim no responcibility for any pain and suffering that may result from reading my code.
