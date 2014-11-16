/*
  GSprinler
  Author: Gaston Gonzalez
  Date  : November 15, 2014  
 */

int GSPRINKLER_COM1 = 7; // Adrunio pin 7
int GSPRINKLER_COM2 = 6; // Adrunio pin 6
int GSPRINKLER_COM3 = 5; // Adrunio pin 5
int GSPRINKLER_COM4 = 4; // Adrunio pin 4

int MILLISECOND = 1000;
int STARTUP_DELAY = 10 * MILLISECOND; // 10 seconds
int DURATION = 30 * MILLISECOND; // 30 seconds

// the setup function runs once when you press reset or power the board
void setup() {
  // Initialize serial interface
  //Serial.begin(9600);

  // Ensure that all relays are inactive at reset
  digitalWrite(GSPRINKLER_COM1,LOW);
  digitalWrite(GSPRINKLER_COM2,LOW);
  digitalWrite(GSPRINKLER_COM3,LOW);
  digitalWrite(GSPRINKLER_COM4,LOW);

  // Initialize output pins  
  pinMode(GSPRINKLER_COM1, OUTPUT);
  pinMode(GSPRINKLER_COM2, OUTPUT);
  pinMode(GSPRINKLER_COM3, OUTPUT);
  pinMode(GSPRINKLER_COM4, OUTPUT);
  
  delay(STARTUP_DELAY);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(GSPRINKLER_COM1,HIGH);// NO1 and COM1 connected;
  delay(DURATION);
  digitalWrite(GSPRINKLER_COM1,LOW);// NO1 and COM1 disconnected;
  digitalWrite(GSPRINKLER_COM2,HIGH);// NO2/COM2 connected;
  delay(DURATION);
  digitalWrite(GSPRINKLER_COM2,LOW);// NO2/COM2 disconnected;
  delay(DURATION);
}
