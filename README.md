# Cubesat-data-logging - WIP
This repo contains our current code for retrieving data from the arduino on our cubesat

# How to use:
1. Clone the repo
2. install the dependancies for the python script
3. Change the serial_port and file variables to match your setup
3. Flash the code to the arduino
4. Connect the arduio and run the python script

# For Google sheets output (Optional):
1. Set the online_mode variable to 1
2. Get your sheet_id and account token - See this Guide: https://denisluiz.medium.com/python-with-google-sheets-service-account-step-by-step-8f74c26ed28e
3. Replace each value in the script

This is a work in progress which is tailored to our specific setup. If you wish to use any of this for your own project it will require a bit of modification. I'll probably make another repository with a more barebones version once this is complete.

# Important note:
The arduino will reset when the script is run due to the serial initialization. This is a feature of the arduino. This is probably not ideal in most cases. The common fix for this feature is to put a 10uF capacitor between the RESET and GND pins.
