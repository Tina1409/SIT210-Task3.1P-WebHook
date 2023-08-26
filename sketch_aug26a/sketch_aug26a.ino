#include <WiFiNINA.h>
#include <ThingSpeak.h>
#define IRSENSORPIN 3 // Defining the pin of the IR sensor

// Adding Hotspot credentials
#define SSID "OnePlus Nord CE 2 Lite 5G"
#define PASS "12345678"

// ThingSpeak channel credentials
#define THINGSPEAK_CHANNEL_ID 2251626
#define API_KEY "NKXLANAFTEL3G3RK"

WiFiClient client; //creating an instance of WiFiClient

void setup() {
  // Initializing serial communication with a width of 9600 bauds.
  Serial.begin(9600);

  // Setting the IR sensor pin as input
  pinMode(IRSENSORPIN, INPUT);

  // Connecting to WiFi
  connectWiFi();

  // Initializing ThingSpeak
  ThingSpeak.begin(client);

  // Setting the LED pin as output
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int irSensorState = digitalRead(IRSENSORPIN);

  // Sending the IR sensor state to ThingSpeak
  sendDataToThingSpeak(irSensorState);

  // Waiting for 30 seconds to perform the next iteration
  delay(30000);
}

// Function to connect to WiFi with no return type -->Procedure
void connectWiFi() {
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

// Function to send data to ThingSpeak with no return type -->Procedure
void sendDataToThingSpeak(int irSensorState) {
  // Setting the field value on thingspeak
  ThingSpeak.setField(1, irSensorState);

  // Writing data to ThingSpeak channel and get HTTP response code
  int httpCode = ThingSpeak.writeFields(THINGSPEAK_CHANNEL_ID, API_KEY);

  // Control Statement block to check if the data is sent or not
  if (httpCode == 200) {
    Serial.println("Data sent to ThingSpeak");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    Serial.println("Error sending data to ThingSpeak");
  }
}
