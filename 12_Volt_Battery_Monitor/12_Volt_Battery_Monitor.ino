#define BLYNK_TEMPLATE_ID "TMPL********"                               // Input your template ID from your Bylnk App
#define BLYNK_TEMPLATE_NAME "Ioniq Power Monitor"                      // Input your template name from your Bylnk App
#define BLYNK_AUTH_TOKEN "********************************"            // Input your device authentication token from your Bylnk App
#define BLYNK_FIRMWARE_VERSION "0.0.1"                                 // Firmware version is used if you would like to do over the air updates with Blynk, Handy for quick calibration changes
#define USE_NODE_MCU_BOARD
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <DHTesp.h>
#include <Wire.h>
#include "INA226.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <WiFiClient.h>
double Voltage;
double Voltage_Raw;
double Humidity;
double Temperature;
double Current;
double Shunt_Voltage;
double Voltage_Calibration = 0.0170920971867008;                       // Voltage Calibration, make minor changes if your voltage is not accurate
double Current_Calibration = -1.7361111111;                            // Current Calibration, make minor changes if your current is not accurate
const char* ssid1 = "*******";                                         // Network 1 Credentials. WIFI Name
const char* password1 = "********";                                    // Network 1 Crednetials. WIFI Password
const char* ssid2 = "************";                                    // Network 2 Crednetials. WIFI Name           -- If you dont have two networks make this the same as the first.
const char* password2 = "********";                                    // Networt 2 Crednetials. WIFI Password       -- If you dont have two networks make this the same as the first.
int Signal = A0;
int Relay = D0;
int sensor_value[3] = { 0 };
int Timer = 0;
bool WIFI_Sleep = false;
unsigned long WIFI_Timer;
String overTheAirURL = "";

DHTesp dht;
INA226 INA(0x40);

void setup() {
  Serial.begin(115200);
  Blynk.config(BLYNK_AUTH_TOKEN);
  pinMode(Signal, INPUT);
  pinMode(Relay, OUTPUT);
  dht.setup(D4, DHTesp::DHT22);
  Wire.begin();
  INA.setAverage(2);
}

void loop() {
  if ((WiFi.status() != WL_CONNECTED) && (WIFI_Sleep == false)) {
    Serial.println("WIFI not connected");
    WiFi.begin(ssid1, password1);
    Serial.print("Attempting to connect to ");
    Serial.println(ssid1);
    while ((WiFi.status() != WL_CONNECTED) && (Timer <= 30)) {
      delay(500);
      Serial.print(".");
      Timer++;
    }
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("");
      Serial.println("Succesfully connected to ");
      Serial.println(ssid1);
      Serial.print("IP Addrress ");
      Serial.println(WiFi.localIP());
      Timer = 0;
    } else {
      Serial.println("");
      Serial.println("Failed to connect to ");
      Serial.println(ssid1);
      // Attempt connection to second SSID
      WiFi.begin(ssid2, password2);
      Serial.print("Attempting to connect to ");
      Serial.println(ssid2);
      while ((WiFi.status() != WL_CONNECTED) && (Timer <= 60)) {
        delay(500);
        Serial.print(".");
        Timer++;
      }
      if (WiFi.status() == WL_CONNECTED) {
        Serial.println("");
        Serial.println("Succesfully connected to ");
        Serial.println(ssid2);
        Serial.print("IP Addrress ");
        Serial.println(WiFi.localIP());
        Timer = 0;
      } else {
        Serial.println("");
        Serial.println("Failed to connect to ");
        Serial.println(ssid2);
        Serial.println("Failed to connect to all networks");
        Serial.println("WIFI going to sleep for 10 minutes");
        WIFI_Sleep = true;
        WIFI_Timer = millis();
      }
    }
  }
  if (WIFI_Sleep == true) {
    WiFi.mode(WIFI_OFF);
    Timer = 0;
  }
  if (millis() - WIFI_Timer >= 600000) {
    WiFi.mode(WIFI_STA);
    WIFI_Sleep = false;
  }
  Blynk.run();
  readsensors();
  Voltage = Voltage_Raw * Voltage_Calibration;
  Serial.print("Voltage = ");
  Serial.println(Voltage);
  Serial.print("Temperature = ");
  Serial.println(Temperature);
  Serial.print("Humidity = ");
  Serial.println(Humidity);
  Current = Shunt_Voltage * Current_Calibration;
  Serial.print("Current = ");
  Serial.println(Current);
  Blynk.virtualWrite(V0, Voltage);
  Blynk.virtualWrite(V1, Current);
  Blynk.virtualWrite(V2, Temperature);
  Blynk.virtualWrite(V3, Humidity);
  delay(1000);
  if (Voltage >= 12.75) {
    digitalWrite(Relay, HIGH);
  }
  if (Voltage < 12.75) {
    digitalWrite(Relay, LOW);
  }
}

void readsensors() {
  Shunt_Voltage = INA.getShuntVoltage_mV();
  Voltage_Raw = analogRead(A0);
  Temperature = dht.getTemperature();
  Humidity = dht.getHumidity();
}

BLYNK_WRITE(InternalPinOTA) {
  Serial.println("OTA Started");
  overTheAirURL = param.asString();
  Serial.print("overTheAirURL = ");
  Serial.println(overTheAirURL);
  WiFiClient my_wifi_client;
  HTTPClient http;
  http.begin(my_wifi_client, overTheAirURL);
  t_httpUpdate_return ret = ESPhttpUpdate.update(my_wifi_client, overTheAirURL);
  switch (ret) {
    case HTTP_UPDATE_FAILED:
      Serial.println("[update] Update failed.");
      break;
    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("[update] Update no Update.");
      break;
    case HTTP_UPDATE_OK:
      Serial.println("[update] Update ok.");
      break;
  }
}
