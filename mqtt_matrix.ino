#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const bool debug = false;

const String mqtt_topic_inverter = "inverter/state";
const String mqtt_topic_heartbeat = "inverter/dashboard2";
const String heartbeat = "OK";

// FIXME: Use https://github.com/tzapu/WiFiManager
const char *ssid = "";
const char *password = "";
const char *mqtt_broker = ""; // FIXME
const int mqtt_port = 1883;

const int STALENESS_THRESHOLD_MS = 1000*60*5;

WiFiClient espClient;
PubSubClient client(espClient);
DynamicJsonDocument inverter_state(2048);

// Uncomment according to your hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Defining size, and output pins
#define MAX_DEVICES 4
#define CS_PIN 5

MD_Parola Display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

int battery_soc_pct = 0;
int battery_power_w = 0;
int pv1_power_w = 0;
int pv2_power_w = 0;

long last_callback = -STALENESS_THRESHOLD_MS-1;
void callback(char *topic, byte *payload, unsigned int length) {
  deserializeJson(inverter_state, payload);
  battery_soc_pct = inverter_state["battery_soc_pct"];
  battery_power_w = inverter_state["battery_power_w"];
  pv1_power_w = inverter_state["pv1_power_w"];
  pv2_power_w = inverter_state["pv2_power_w"];
  if (debug) {
    Serial.print("Battery %: ");
    Serial.println(battery_soc_pct);
    Serial.print("Battery W: ");
    Serial.println(battery_power_w);
  }
  last_callback = millis();
}

unsigned long now = millis();
void publishHeartbeat() {
  client.publish(mqtt_topic_heartbeat.c_str(), heartbeat.c_str());
}

bool stale_data = true;
unsigned int option = 0;
unsigned long justnow;
void loop() {
  /*
  // Use for longer boot scroll messages to completion
  while (!Display.displayAnimate()) {
    // noop
  }
  */
  client.loop();
  now = millis();
  if (now != justnow) {
    if (now % 10000 == 0) {
      publishHeartbeat();
    }
    if (now % 2000 == 0) {
      if (now - last_callback >= STALENESS_THRESHOLD_MS) {
        stale_data = true;
      } else {
        stale_data = false;
      }
      Display.displayClear();
      if (! stale_data) {
        //Display.setInvert(false);
        Display.setTextAlignment(PA_RIGHT);
        option++;
        if (option == 1) {
          Display.print(String(battery_soc_pct) + "%");
        } else if (option == 2) {
          Display.print(String(battery_power_w) + "W");
          option = 0;
        }
      } else {
        //Display.setInvert(true);
        Display.setTextAlignment(PA_CENTER);
        Display.print("data?");
      }
    }
    justnow = now;
  }
  if (!client.connected()) {
    ESP.restart();
  }
}

void setup() {
  if (debug) {
    Serial.begin(115200);
  }
  Display.begin();
  Display.setIntensity(0);
  Display.displayClear();
  Display.displayScroll("hi", PA_LEFT, PA_SCROLL_RIGHT, 60);
  Display.displayAnimate();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (debug) {
    Serial.print("Connecting to WiFi ..");
  }
  while (WiFi.status() != WL_CONNECTED) {
    Display.displayAnimate();
  }
  if (debug) {
    Serial.println(WiFi.localIP());
  }
  client.setBufferSize(2048);
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    Display.displayAnimate();
    String client_id = "esp32-dashboard-";
    client_id += String(WiFi.macAddress()); 
    if (!client.connect(client_id.c_str())) {
      Display.displayAnimate();
    }
  }
  client.subscribe(mqtt_topic_inverter.c_str());
  Display.displayAnimate();
  publishHeartbeat();
  Display.displayAnimate();
}
