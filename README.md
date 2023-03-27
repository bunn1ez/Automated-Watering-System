# Automated-Watering-System
This is the code for an Arduino Uno project that controls a Submersible Water Pump based on a Capacitive Soil moisture sensor. Then displays on a LCD the current state of the plant and when the water is being extruded through the rubber tubing. 
The supplies used are as listed:
1.  QAPASS LiquidCrystal_I2C
2.  Relay: Songle SRD-05VDC-SL-C
3.  Arduino Uno R3
4.  Capacitive Soil Moisture Sensor v1.2, with values 250-550 [(250 = Very Wet) & (550 = Usually in open air)]
5.  Pump: 5VDC 0.3A, Submersible Water Pump, for this project 120VAC is fed to a DC power inverter that turns 120VAC to 5VDC
6.  Jumper Wires & male and female wire adapters
7.  120VAC Cord: For SRD-05VDC-SL-C, Relay
8.  120VAC Power from outlet
9.  5VDC 0.5mA Power Supply: For Arduino Uno
10. 5/16" Rubber Tubing, around 2-3 feet long
11. One ANPTGHT 1/2" Hose Barb Fitting Equal Barbed Y Shaped 3 Way Plastic Tubing Joint Splicer: 
    This is for the circle that will be created from the rubber tubing to water the plants and feed to the pump
    
Note: For the LCD_I2C, make sure for the lcd, that the ~A5 pin is matches with SCL on the LCD_I2C and the ~A4 pin is matched with the SDA pin on the LCD_I2C
