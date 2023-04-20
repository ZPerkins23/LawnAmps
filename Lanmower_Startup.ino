
int Relay1 = 7;
int Relay2 = 6;
void setup() {

  Serial.begin(9600);
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);

  digitalWrite(Relay1 , LOW); //  ensure both relays are in off position
  digitalWrite(Relay2 , LOW);
  //delay(1000);
  digitalWrite(Relay1, HIGH); // in-rush relay is turned on (low logic turns relays on)
  //digitalWrite(Relay2 , LOW);
  delay(2000);               // only in rush relay is on for 2 seconds
  digitalWrite(Relay2, HIGH); // main relay and in-rush relay are on for an additional 2 seconds
  delay(2000);
  digitalWrite(Relay1, LOW); // in rush relay is turned off and main relay is on until the machine is powered off
}

void loop() {

}
