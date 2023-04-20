// 48V Battery monitoring system senior project
// Author: Zach Perkins
// External authors for Wire.h and LiquidCrystal_I2C.h: Frank de Brabander
# include <Wire.h>
#include <LiquidCrystal_I2C.h>
# include <math.h>

//define I2C address......
LiquidCrystal_I2C lcd(0x27, 20, 4);
// Create hour glass character
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

bool alerted20 = false;
bool alerted15 = false;

void setup() {
  Serial.begin(9600); // set baudrate
  lcd.init(); // initialize lcd display
  lcd.clear(); // clear the screen
  lcd.backlight(); // turn on the backlight
  lcd.createChar(0, Battery);
  //Print startup display
  lcd.setCursor(3, 1); //
  lcd.print("Battery Monitor");
  lcd.setCursor(10, 2);
  lcd.write(byte(0));
  delay(2000);
  lcd.clear();
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
  int signal = analogRead(A0);
  double V = signal * (5.0 / 1023.0); // Create Voltage variable
  V = (V * 11)/0.83;
  float Bat = 0.0;                              // Create Battery variable
  if (V > 54.30) {
    V = 54.30;
    Bat = 100.00;
  }
  if (V >= 53.60 && V < 54.40) {

    Bat = 95.00; // Formula to determine Battery percentage with compensation
  }
   else if (V >= 53.00 && V < 53.60) {

    Bat = 90.00; // Formula to determine Battery percentage with compensation
  }
  else if (V >= 53.2 && V < 53.00) {

    Bat = 80.00; // Formula to determine Battery percentage with compensation
  }
  else if (V >= 52.80 && V < 53.20) {

    Bat = 70.00; // Formula to determine Battery percentage with compensation
  }
   else if (V >= 52.60 && V < 52.80) {

    Bat = 60.00; // Formula to determine Battery percentage with compensation
  }
   else if (V >= 52.50 && V < 52.60) {

    Bat = 50.00; // Formula to determine Battery percentage with compensation
  }
   else if (V >= 52.40 && V < 52.50) {

    Bat = 40.00; // Formula to determine Battery percentage with compensation
  }
   else if (V >= 51.10 && V < 52.40) {

    Bat = 30.00; // Formula to determine Battery percentage with compensation
  }
  else if (V < 51.10) {
    Bat = ((V - 40.1) / 40.1) * 100;
  }
  if (Bat < 0) {
    Bat = 0.0;
  }
  else if (Bat > 100) {
    Bat = 100.0;
  }
  int B = (int)Bat;
  lcd.setCursor(9, 1);
  lcd.print(V);                         // Display the Voltage
 // lcd.setCursor(0, 3);
 // lcd.print("                    ");     // Clear line 4 of warning message
  lcd.setCursor(9, 2);
  lcd.print("   ");                       // Clear battery percentage
  lcd.setCursor(9, 2);
  lcd.print(B);                        // Displays battery percentage
  // B <= 20 && B % 10 == 0
  if (B <= 20 && !alerted20) {
    lcd.setCursor(0, 3);
    lcd.print("Warning Low Battery");
    for (int k = 0; k < 4; k++) {
      lcd.noDisplay();
      delay(200);
      lcd.display();
      delay(200);
      alerted20 = true;
    }
  }
  else if (B <= 15 && !alerted15) {
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

  else if (B <= 10) {
    lcd.setCursor(0, 3);
    lcd.print("Warning Low Battery");       // Displays warning message and blinks the screen
    for (int k = 0; k < 2; k++) {
      lcd.noDisplay();
      delay(200);
      lcd.display();
      delay(200);
    }
  }

  delay(1000);                        // Takes a measurement every second (demo mode)
}
