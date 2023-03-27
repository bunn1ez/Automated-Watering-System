/*********************************************************************************
 * This program is free software: you can redistribute it and/or modify        *
 * it under the terms of the GNU General Public License as published by          *
 * the Free Software Foundation, either version 2 of the License, or             *
 * (at your option) any later version.                                            *
 *                                                                               *
 * This program is distributed in the hope that it will be useful,               *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 *
 * GNU General Public License for more details.                                  *
 *                                                                               *
 * You should have received a copy of the GNU General Public License             *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.         *
 *********************************************************************************/

/****************************************************************************************************************************************
The parts used in this project are:
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
Note: For the LCD_I2C, make sure that the ~A5 pin is matched with SCL on the LCD_I2C, and the ~A4 pin is matched with the SDA pin on the LCD_I2C
*****************************************************************************************************************************************/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define pin assignments and thresholds
#define waterSensor A0 // This is setting the input pin for the Capacitive Moisture Sensor v1.2
int relaySignal = 5; 
int THRESHOLD = 420; // This is +20 over the value 400 for error which represents the minimum value it takes for the soil to get moist and turn the pump off
int voltageSensor = 8; // This is the input voltage for the sensor to recieve 5VDC to turn on and start getting input
int relayInput = 3; // This setting up the 5VDC input from the Arduino to the relay
unsigned long startTime; // This initiates the millis(); function that starts the 36 hour timer for the intervals between watering cycles 

// Initialize the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // The 0x27 is used for allocating the RAM storage for the lcd model to use, while the 16 is represented as the number of characters in a row by 2 rows

void setup() {
  // Set up serial communication
  Serial.begin(9600); // This iniates the Baud Rate (bps) at 9600

  // Set pin modes
  pinMode(waterSensor, INPUT); // This sets the pin A0 as the input pin for the Capacitive Moisture Sensor
  pinMode(voltageSensor, OUTPUT); // The Capacitive Moisture Sensor's source of power is from the digital pin 8
  pinMode(relaySignal, OUTPUT); // This is setting digital pin 5 as the 5VDC output for the relay signal to be powered 
  pinMode(relayInput, OUTPUT); // This sets the digital pin 3 as the output for the relay's power

  // Initialize the LCD and turn on the backlight
  lcd.init();
  lcd.backlight();
  
  // Clear the LCD screen and set voltage sensor pin to low
  lcd.clear();
  digitalWrite(voltageSensor, LOW);
}

void loop() {
  int i; // This sets the for value i as an integer

  // Turn on the voltage sensor and the relay input
  digitalWrite(voltageSensor, HIGH);
  digitalWrite(relayInput, HIGH);
  delay(10);

  // Clear the LCD screen and set the cursor position to 0,0
  lcd.clear();
  lcd.setCursor(0, 0); // This initializes the LCD's cursor at column zero, row zero

  // Check the water sensor 5 times with 500ms intervals
  for (i=0; i < 5; i++){
    delay(500);
    int value = analogRead(waterSensor);

    // If the soil is dry, turn on the pump for 20 seconds
    if (value > THRESHOLD) {
      lcd.print("Soil's Dry: ");
      Serial.println("Soil's Dry: \n");
      delay(100);
      lcd.setCursor(0,1);
      lcd.print("Starting Pump...");
      Serial.println("Starting Pump...\n");
      delay(10);
      digitalWrite(relaySignal,HIGH); // This allows the pump to recieve the 5VDC to operate by passing the 120VAC to the 5VDC power inverter
      delay(20000);
    }

    // If the soil is moist, turn off the pump and exit the loop
    else {
      lcd.print("Soil's Moist: ");
      Serial.println("Soil's Moist: \n");
      delay(100);
      lcd.setCursor(0,1);
      lcd.print("Turning Pump off...");
      Serial.println("Turning Pump off...\n");
      delay(10);
      digitalWrite(relaySignal,LOW);
      delay(100);
      break; 
    }
  }

  // Display "Done Watering!" on the LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Done Watering!");
  delay(10);

  // Turn off the voltage sensor, relay signal, and relay input
  digitalWrite(voltageSensor,LOW);
  delay(10);
  digitalWrite(relaySignal, LOW);
  delay(10);
  digitalWrite(relayInput, LOW);
  delay(5);

  // Start a timer for 36 hours and display the time remaining on the LCD
  startTime = millis(); 
  while (millis() - startTime < 3600000UL * 36) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Water in:"); // Prints to the lcd that the watering cycle will repeat in # amount of time
    lcd.setCursor(10, 1);
    lcd.print((3600000UL * 36 - (millis() - startTime)) / 3600000);
    delay(2000);
    lcd.print("hours");
    delay(1000);
  }
  
  // Clear the LCD screen after the timer ends
  lcd.clear();
}