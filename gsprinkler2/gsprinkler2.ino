/*
  Sketch: GSprinkler Web Server
  Author: Gaston Gonzalez
  Date  : 16 November 2014
  
  A simple web server for controlling a sprinkler with 3 zones. Based on the Examples > Ethernet > WebServer
  example by David A. Mellis and Tom Igoe.
 */
#include <SPI.h>
#include <EthernetV2_0.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1, 50);

// Arduino COM pins. Uses a 1-based index
int GSPRINKLER_COM[] = { 0, 7, 6, 5, 4 };
int STARTUP_DELAY = 10000; // Startup delay: 10 seconds
int DURATION = 30000;      // Station duration: 30 seconds
int MAX_ZONES = 3;
String currentLine = "";  // Buffer for client requests

// Initialize the Ethernet server library to port 80 (HTTP)
EthernetServer server(80);
#define W5200_CS  10
#define SDCARD_CS 4

void setup() {
  Serial.begin(9600);

  currentLine.reserve(256); // buffer

  // Ensure that all relays are inactive at reset and initialize each pin in sequence.
  for (int i = 1; i <= 4; i++) {
      digitalWrite(GSPRINKLER_COM[i], LOW);
      pinMode(GSPRINKLER_COM[i], OUTPUT);
  }

  delay(STARTUP_DELAY);

  // Note:The SDCARD must be enabled for the ethernet to work. Otherwise, the IP initializes to 0.0.0.0.
  // Our relay switch also uses pin 4, which leaves with only 3 relays.
  pinMode(SDCARD_CS,OUTPUT);
  digitalWrite(SDCARD_CS,HIGH); //Deselect the SD card

  // Start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

// Generates a status response as JSON
String getStatus() {
   String statusJson =  String("{");
   statusJson.concat("\"zones\":[");
   for (int i = 1; i <= MAX_ZONES; i++) {
     statusJson.concat("{\"zoneNum\":");
     statusJson.concat(i);
     statusJson.concat(",\"zoneState\":");
     statusJson.concat(digitalRead(GSPRINKLER_COM[i]));
     statusJson.concat("}");
     if (i != MAX_ZONES) { statusJson.concat(","); }
   }
 statusJson.concat("]}");
 return statusJson;
}

void loop() {
  
  // Listen for requests
  EthernetClient client = server.available();
  if (client) {
    boolean currentLineIsBlank = true;
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        // Check for a zone toggle request
        currentLine += c; 
        if ( currentLine.indexOf("toggle=") != -1 && c == '\n' ) {
          Serial.print("Toggling zone: ");
          char toggleZone = currentLine.charAt( currentLine.indexOf("toggle=") + 7 );
          int zoneNum = String(toggleZone).toInt();
          Serial.println(zoneNum);
          // Toggle the state for the current zone
          digitalWrite(GSPRINKLER_COM[zoneNum], !digitalRead(GSPRINKLER_COM[zoneNum]));          
        }
        
        // End of client HTTP request
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: application/json");
          client.println("Connnection: close\n");
          client.print(getStatus());            
          break;
        }
        if (c == '\n') {
          // Start new line
          currentLineIsBlank = true;
          currentLine = "";
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    // Give the web browser time to receive the data
    delay(1);
    // Close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

