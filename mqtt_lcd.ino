#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>

const bool debug = false;

const String mqtt_topic_inverter = "inverter/state";
const String mqtt_topic_heartbeat = "inverter/dashboard";
const String heartbeat = "OK";

// FIXME: Use https://github.com/tzapu/WiFiManager
const char *ssid = "";
const char *password = "";
const char *mqtt_broker = ""; // FIXME
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);
DynamicJsonDocument inverter_state(2048);

LiquidCrystal_I2C lcd(0x27,16,2);

unsigned long last_callback = millis();
unsigned long now_callback = millis();
void callback(char *topic, byte *payload, unsigned int length) {
  digitalWrite(LED_BUILTIN, LOW);
  deserializeJson(inverter_state, payload);
  int battery_soc_pct = inverter_state["battery_soc_pct"];
  int battery_power_w = inverter_state["battery_power_w"];
  int pv1_power_w = inverter_state["pv1_power_w"];
  int pv2_power_w = inverter_state["pv2_power_w"];
  if (debug) {
    Serial.print("Battery %: ");
    Serial.println(battery_soc_pct);
    Serial.print("Battery W: ");
    Serial.println(battery_power_w);
  }
  now_callback = millis();
  // tolerate 5 mins staleness
  if (now_callback - last_callback >= 1000*60*5) {
    lcd.noBacklight();
  } else {
    lcd.backlight();
  }
  last_callback = millis();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(String("B: ") + String(battery_soc_pct) + String("%") + " " + String(battery_power_w) + "W");
  lcd.setCursor(0,1);
  lcd.print(String("S: ") + String(pv1_power_w) + String("W ") + String(pv2_power_w) + "W");
  digitalWrite(LED_BUILTIN, HIGH);
}

unsigned long now = millis();
void publishHeartbeat() {
  if (debug) {
    Serial.println(String("Sending heartbeat: ") + heartbeat);
  }
  client.publish(mqtt_topic_heartbeat.c_str(), heartbeat.c_str());
}

void blinkLed(int duration) {
  digitalWrite(LED_BUILTIN, LOW);
  delay(duration);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(duration);
}

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("WiFi SSID:");
  lcd.setCursor(0,1);
  lcd.print(ssid);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    blinkLed(100);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MQTT broker:");
  lcd.setCursor(0,1);
  lcd.print(mqtt_broker);
  client.setBufferSize(2048);
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    String client_id = "esp8266-switch-";
    client_id += String(WiFi.macAddress()); 
    if (!client.connect(client_id.c_str())) {
      blinkLed(1000);
    }
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("MQTT topic:");
  lcd.setCursor(0,1);
  lcd.print(mqtt_topic_inverter);
  client.subscribe(mqtt_topic_inverter.c_str());
  publishHeartbeat();
  if (debug) {
    Serial.begin(115200);
  }
}

unsigned long justnow;
void loop() {
  client.loop();
  now = millis();
  if (now != justnow) {
    if (now % 10000 == 0) {
      publishHeartbeat();
    }
    justnow = now;
  }
  if (!client.connected()) {
    ESP.restart();
  }
}
