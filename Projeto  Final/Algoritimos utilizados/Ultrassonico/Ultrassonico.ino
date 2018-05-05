
/*
********************************************
  14CORE ULTRASONIC DISTANCE SENSOR CODE TEST
********************************************
*/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>
#define TRIGGER 5
#define ECHO    4
Servo servo;

// NodeMCU Pin D1 > TRIGGER | Pin D2 > ECHO

const char* ssid = "NEXT-18ME267";
const char* password = "di37khu6";
const char* mqtt_server = "35.227.106.44";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {

  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {

  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");

      client.subscribe("topic-iot-cefetmg");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      delay(3000);
    }
  }
}

void setup() {

  Serial.begin (115200);
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  servo.attach(2); //D4
  servo.write(0);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  delay(2000);
}

void loop() {

  long duration, distance;
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration / 2) / 29.1;

  Serial.print(distance);

  if (distance >= 10) {

    if (!client.connected()) {
      reconnect();
    }
    Serial.println("Acionado");
    client.loop();
    client.publish("topic-iot-cefetmg", "25");
    delay(30000);
  }
  delay(1000);
}
