# Cubesat-data-logging - WIP
This repo contains an alternative method for recording data sent from the serial monitor. This aproach is OS and software agnostic, all you need is python 3.9+.

# How to use:
1. Clone the repo
2. install the dependancies for the python script
3. Flash the code to the arduino
4. Connect the arduio and run the python script

# Pros:
1. FOSS
2. No Microsoft
3. Should work on everything

# Cons: 
1. Barely tested
2. Requires manual tweaking to fit your setup.
3. Probably some other things I haven't discovered/don't care about

This is a work in progress which is tailored to our specific setup. You will have to change things to make it work for your own setup. Primarily the "serialport" variable and number of data[] entries in your writerow line. Because Serial tends to return incomplete data I added a try statement so that it doesn't break. This incomplete data is just thrown out.

# Important note:
The arduino will reset when the script is run due to the serial initialization. This is a feature of the arduino. This is probably not ideal in most cases. The common fix for this feature is to put a 10uF capacitor between the RESET and GND pins.

I claim no responcibility for any pain and suffering that may result from reading my code.