#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SimpleDHT.h>

const char* ssid = "Wifi4";
const char* passphrase = "asdfghjkl";

const char* apiUrl = "https://api.example.com/data";  // 替换为你的目标API地址

unsigned long RequestTime = 0;
unsigned long RequestTemp = 5000;  

unsigned long BaseSensorTemp = 0;
unsigned long BaseSensorTime = 2000;  // 传感器读取的执行间隔

unsigned long AdvancedSensorTemp = 0;
unsigned long AdvancedSensorTime = 1000;  // 传感器读取的执行间隔

int pinDHT11 = 16; //溫濕度
int pinRain = 5;
int pinHumi = 4;

SimpleDHT11 dht11;


void setup() {
  pinMode(pinRain, INPUT);
  pinMode(pinHumi, INPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, passphrase);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  unsigned long MS = millis();

  // 执行传感器读取
  if (MS - BaseSensorTemp >= BaseSensorTime) {
    readSensorData();
    BaseSensorTemp = MS;
  }

  // 执行API请求
  if (MS - RequestTime >= RequestTemp) {
    performHttpRequest();
    RequestTime = MS;
  }

  // 读取下雨感測器
  if (MS - AdvancedSensorTemp >= AdvancedSensorTime) {
    int RainState = !digitalRead(pinRain);
    int HumiState = analogRead(pinHumi);
    Serial.print("Rain Sensor: ");
    Serial.println(RainState);
    Serial.print("Humi Sensor: ");
    Serial.println(HumiState);
    AdvancedSensorTemp = MS;
  }

  // 在主循环中可以执行其他操作
}



void readSensorData() {
  // 读取传感器数据
  int err;
  byte temperature = 0;
  byte humidity = 0;

  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.print(err); Serial.println("SimpleDHT");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%  Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
}

void performHttpRequest() {
  // 执行HTTP请求函数
  // HTTPClient http;
  // http.begin(apiUrl);

  // int httpCode = http.GET();
  // if (httpCode > 0) {
  //   String payload = http.getString();
  //   Serial.println("HTTP GET request successful");
  //   Serial.println("Response: " + payload);
  // } else {
  //   Serial.println("HTTP GET request failed");
  // }

  // http.end();
    Serial.println("API");
}
