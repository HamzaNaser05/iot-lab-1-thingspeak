#include <WiFi.h>
#include "ThingSpeak.h"
#include "DHT.h"

const char* studentName  = "Hamza Nasser";
const char* universityID = "12324183";

const char* WIFI_Name = "Wokwi-GUEST"; 
const char* WIFI_Pass = "";            

const unsigned long channelNumber = 3549775; 
const char* apiKey = "DVJ7EF6NDWZ1FUT2";

#define DHTPIN 15       
#define DHTTYPE DHT22   

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("==========================================");
  Serial.println("     ESP32 -> ThingSpeak Telemetry        ");
  Serial.println("==========================================");
  Serial.print("Student Name  : "); Serial.println(studentName);
  Serial.print("University ID : "); Serial.println(universityID);
  Serial.println("==========================================\n");

  dht.begin();

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_Name, WIFI_Pass);

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n[Wi-Fi] Connected successfully!");
  Serial.print("[Wi-Fi] IP Address: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); 

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("[ERROR] Failed to read from DHT sensor! Check connections.");
    delay(2000);
    return;
  }

  Serial.println("\n------------------------------------------");
  Serial.print("University ID : "); Serial.println(universityID);
  Serial.print("Temperature   : "); Serial.print(temperature, 1); Serial.println(" °C");
  Serial.print("Humidity      : "); Serial.print(humidity, 1); Serial.println(" %");

  ThingSpeak.setField(1, temperature);            // Field 1: Temperature
  ThingSpeak.setField(2, humidity);               // Field 2: Humidity
  ThingSpeak.setStatus(universityID);             // Requirement #4 in HTTP request

  int httpCode = ThingSpeak.writeFields(channelNumber, apiKey);

  if (httpCode == 200) {
    Serial.println("[ThingSpeak] Success: Data sent to cloud (HTTP 200)");
  } else {
    Serial.print("[ERROR] ThingSpeak update failed, HTTP code: ");
    Serial.println(httpCode);
  }

  Serial.println("Waiting 20 seconds for next transmission...");
  delay(20000);
}
