#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Servo.h>
#define TRIGGER 5
#define ECHO    4
Servo servo;

const char* ssid = "NEXT-18ME267";
const char* password = "di37khu6";

void setup () {

  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  servo.attach(2); //D4
  servo.write(0);
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print("Connecting..");

  }

}

void loop() {
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  long duration, distance;
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration / 2) / 29.1;

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if (distance >= 30 && distance <= 50) {

    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

      Serial.println("----POST----");

      StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
      JsonObject& JSONencoder = JSONbuffer.createObject();

      JSONencoder["valor"] = distance;  //leitura do sensor

      char JSONmessageBuffer[300];
      JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
      Serial.println(JSONmessageBuffer);

      HTTPClient http;  //Declare an object of class HTTPClient

      http.begin("http://35.227.106.44:3000/distancia");      //Specify request destination
      http.addHeader("Content-Type", "application/json");  //Specify content-type header

      int httpCode = http.POST(JSONmessageBuffer);   //Send the request
      String payload = http.getString();

      if (httpCode > 0) { //Check the returning code
        Serial.print("Response Code: ");
        Serial.println(httpCode);
        String payload = http.getString();   //Get the request response payload
        Serial.println(payload);            //Print the response payload

      }

      Serial.println("----GET----");
      http.begin("http://35.227.106.44:3000/distancia/recente");  //Specify request destination
      httpCode = http.GET();                                                                  //Send the request

      if (httpCode > 0) { //Check the returning code
        Serial.print("Response Code: ");
        Serial.println(httpCode);
        String payload = http.getString();   //Get the request response payload
        payload.remove(0, 1);

        Serial.println(payload);             //Print the response payload

        // Parsing
        const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
        DynamicJsonBuffer jsonBuffer(bufferSize);
        JsonObject& root = jsonBuffer.parseObject(payload);
        // Parameters
        int id = root["_id"];
        const char* time = root["time"];
        const char* valor = root["valor"];

        Serial.print("id:");
        Serial.println(id);
        Serial.print("Time:");
        Serial.println(time);
        Serial.print("valor:");
        Serial.println(valor);
      }

      http.end();   //Close connection

    }

    delay(5000);    //Send a request every 30 seconds

  } else {

    if (distance >= 10 && distance <= 29) {

      if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

        Serial.println("----POST----");

        StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
        JsonObject& JSONencoder = JSONbuffer.createObject();

        JSONencoder["valor"] = distance;  //leitura do sensor

        char JSONmessageBuffer[300];
        JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
        Serial.println(JSONmessageBuffer);

        HTTPClient http;  //Declare an object of class HTTPClient

        http.begin("http://35.227.106.44:3000/distancia");      //Specify request destination
        http.addHeader("Content-Type", "application/json");  //Specify content-type header

        int httpCode = http.POST(JSONmessageBuffer);   //Send the request
        String payload = http.getString();

        if (httpCode > 0) { //Check the returning code
          Serial.print("Response Code: ");
          Serial.println(httpCode);
          String payload = http.getString();   //Get the request response payload
          Serial.println(payload);            //Print the response payload

        }

        Serial.println("----GET----");
        http.begin("http://35.227.106.44:3000/distancia/recente");  //Specify request destination
        httpCode = http.GET();                                                                  //Send the request

        if (httpCode > 0) { //Check the returning code
          Serial.print("Response Code: ");
          Serial.println(httpCode);
          String payload = http.getString();   //Get the request response payload
          payload.remove(0, 1);

          Serial.println(payload);             //Print the response payload

          // Parsing
          const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
          DynamicJsonBuffer jsonBuffer(bufferSize);
          JsonObject& root = jsonBuffer.parseObject(payload);
          // Parameters
          int id = root["_id"];
          const char* time = root["time"];
          const char* valor = root["valor"];

          Serial.print("id:");
          Serial.println(id);
          Serial.print("Time:");
          Serial.println(time);
          Serial.print("valor:");
          Serial.println(valor);
        }

        http.end();   //Close connection

      }

      delay(2500);    //Send a request every 30 seconds

    } else {

      if (distance <= 9) {

        if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

          Serial.println("----POST----");

          StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
          JsonObject& JSONencoder = JSONbuffer.createObject();

          JSONencoder["valor"] = distance;  //leitura do sensor

          char JSONmessageBuffer[300];
          JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
          Serial.println(JSONmessageBuffer);

          HTTPClient http;  //Declare an object of class HTTPClient

          http.begin("http://35.227.106.44:3000/distancia");      //Specify request destination
          http.addHeader("Content-Type", "application/json");  //Specify content-type header

          int httpCode = http.POST(JSONmessageBuffer);   //Send the request
          String payload = http.getString();

          if (httpCode > 0) { //Check the returning code
            Serial.print("Response Code: ");
            Serial.println(httpCode);
            String payload = http.getString();   //Get the request response payload
            Serial.println(payload);            //Print the response payload

          }

          Serial.println("----GET----");
          http.begin("http://35.227.106.44:3000/distancia/recente");  //Specify request destination
          httpCode = http.GET();                                                                  //Send the request

          if (httpCode > 0) { //Check the returning code
            Serial.print("Response Code: ");
            Serial.println(httpCode);
            String payload = http.getString();   //Get the request response payload
            payload.remove(0, 1);

            Serial.println(payload);             //Print the response payload

            // Parsing
            const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
            DynamicJsonBuffer jsonBuffer(bufferSize);
            JsonObject& root = jsonBuffer.parseObject(payload);
            // Parameters
            int id = root["_id"];
            const char* time = root["time"];
            const char* valor = root["valor"];

            Serial.print("id:");
            Serial.println(id);
            Serial.print("Time:");
            Serial.println(time);
            Serial.print("valor:");
            Serial.println(valor);
          }

          http.end();   //Close connection

        }

        delay(1000);    //Send a request every 30 seconds
      }
    }
  }
}


