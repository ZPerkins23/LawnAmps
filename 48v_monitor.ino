// 48V Battery monitoring system senior project
// Author: Zach Perkins
// External author LiquidCrystal_I2C.h: Frank de Brabander
// LIquidCrystal_I2C is an open source header file used to connect the Arduino to the LCD display
// Wire.h and math.h are included in the Arduino IDE, math.h is for math functions, Wire.h is to send data to I2Cs
# include <Wire.h>
#include <LiquidCrystal_I2C.h>
# include <math.h>

//define I2C address......
LiquidCrystal_I2C lcd(0x27, 20, 4); // address of the 20x4 LCD
// Create battery character
byte Battery[8] = {
  0b01110,
  0b10001,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

bool alerted20 = false;   // Battery warning messege alerts
bool alerted15 = false;

void setup() {
  Serial.begin(9600); // set baudrate
  lcd.init(); // initialize lcd display
  lcd.clear(); // clear the screen
  lcd.backlight(); // turn on the backlight
  lcd.createChar(0, Battery); // loads the battery character to be displayed
  //Print startup display
  lcd.setCursor(3, 1); //
  lcd.print("Battery Monitor");
  lcd.setCursor(10, 2);
  lcd.write(byte(0));
  delay(2000);
  lcd.clear();    // clears startup display
  // sets up the screen for title and information to be displayed
  lcd.setCursor(6, 0);
  lcd.print("LawnAmps");
  delay(500);
  lcd.setCursor(0, 2);
  lcd.print("Battery:");
  lcd.setCursor(15, 2);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Voltage:");
  lcd.setCursor(15, 1);
  lcd.print("V");
}

void loop() {
  int signal = analogRead(A0); // reads the signal from the voltage sensor
  double V = signal * (5.0 / 1023.0); // Create Voltage variable
  V = (V * 11)/0.83;                  // multiplies the voltage to achieve actual batter voltage
  float Bat = 0.0;                              // Create Battery variable
  if (V >= 54.40) {                          // displays up to maximum voltage of batteries
    V = 54.40;
    Bat = 100.00;
  }
  // approximation is used from 100-30% due to limited voltage changes between percentages
  if (V >= 53.60 && V < 54.40) {

    Bat = 95.00; 
  }
   else if (V >= 53.00 && V < 53.60) {

    Bat = 90.00; 
  }
  else if (V >= 53.2 && V < 53.00) {

    Bat = 80.00; 
  }
  else if (V >= 52.80 && V < 53.20) {

    Bat = 70.00; 
  }
   else if (V >= 52.60 && V < 52.80) {

    Bat = 60.00; 
  }
   else if (V >= 52.50 && V < 52.60) {

    Bat = 50.00;
  }
   else if (V >= 52.40 && V < 52.50) {

    Bat = 40.00; 
  }
   else if (V >= 51.10 && V < 52.40) {

    Bat = 30.00; 
  }
  // higher precesion calculation used below 30% due to accuracy of calculation and critical charge levels
  else if (V < 51.10) {
    Bat = ((V - 40.1) / 40.1) * 100;
  }
  // sets upper and lower bounds of charge percentage
  if (Bat < 0) {
    Bat = 0.0;
  }
  else if (Bat > 100) {
    Bat = 100.0;
  }
  int B = (int)Bat;                      // converts percentage data type to int for easer to read display
  lcd.setCursor(9, 1);
  lcd.print(V);                         // Display the Voltage
 // lcd.setCursor(0, 3);
 // lcd.print("                    ");     // once displayed warning message remains
  lcd.setCursor(9, 2);
  lcd.print("   ");                       // Clear battery percentage
  lcd.setCursor(9, 2);
  lcd.print(B);                        // Displays battery percentage
  // B <= 20 && B % 10 == 0
  if (B <= 20 && !alerted20) {         // alert user once charge is 20% or below once
    lcd.setCursor(0, 3);
    lcd.print("Warning Low Battery");
    for (int k = 0; k < 4; k++) {
      lcd.noDisplay();                  // Displays warning message and blinks screen
      delay(200);
      lcd.display();
      delay(200);
      alerted20 = true;
    }
  }
  else if (B <= 15 && !alerted15) {     // alert user once charge is 15% or below
    lcd.setCursor(0, 3);
    lcd.print("Warning Low Battery");    // Displays warning message and blinks the screen
    for (int k = 0; k < 4; k++) {
      lcd.noDisplay();
      delay(200);
      lcd.display();
      delay(200);
      alerted15 = true;
    }
  }

  else if (B <= 10) {                        // Continually warn user once charge is 10% or less
    lcd.setCursor(0, 3);
    lcd.print("Warning Low Battery");       // Displays warning message and blinks the screen
    for (int k = 0; k < 2; k++) {
      lcd.noDisplay();
      delay(200);
      lcd.display();
      delay(200);
    }
  }

  delay(1000);                        // Takes a measurement every second
}
