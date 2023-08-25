#include <WiFiNINA.h>
#include <ThingSpeak.h>

// Define the digital pin connected to the IR sensor
#define IRSENSORPIN 3

// WiFi network credentials
#define WIFI_SSID "OnePlus Nord CE 2 Lite 5G"
#define WIFI_PASS "12345678"

// ThingSpeak channel and API credentials
#define THINGSPEAK_CHANNEL_ID 2251626
#define API_KEY "NKXLANAFTEL3G3RK"

WiFiClient client;

void setup() {
  // Start serial communication at 9600 bps
  Serial.begin(9600);

  // Set the IR sensor pin as input
  pinMode(IRSENSORPIN, INPUT);

  // Connect to the WiFi network
  connectWiFi();

  // Initialize ThingSpeak communication
  ThingSpeak.begin(client);

  // Set built-in LED pin as output
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Read the state of the IR sensor (HIGH or LOW)
  int irSensorState = digitalRead(IRSENSORPIN);

  // Send the IR sensor state to ThingSpeak for analysis
  sendDataToThingSpeak(irSensorState);

  // Delay for 30 seconds before the next data transmission
  delay(30000);
}

// Function to establish a connection to the WiFi network
void connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

// Function to transmit data to ThingSpeak
void sendDataToThingSpeak(int irSensorState) {
  // Set the field for IR sensor state in the ThingSpeak channel
  ThingSpeak.setField(1, irSensorState);

  // Upload the field to the ThingSpeak channel
  int httpCode = ThingSpeak.writeFields(THINGSPEAK_CHANNEL_ID, API_KEY);

  // Check if the data was successfully transmitted
  if (httpCode == 200) {
    Serial.println("Data sent to ThingSpeak");
    digitalWrite(LED_BUILTIN, HIGH); // Turn on the built-in LED
    delay(1000); // Wait for a second
    digitalWrite(LED_BUILTIN, LOW); // Turn off the built-in LED
  } else {
    Serial.println("Error sending data to ThingSpeak");
  }
}
