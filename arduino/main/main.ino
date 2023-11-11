#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SimpleDHT.h>

const char* ssid = "Wifi4";
const char* passphrase = "asdfghjkl";

const char* apiUrl = "http://127.0.0.1:8000/i/local/";  // 替换为你的目标API地址

unsigned long RequestTime = 0;
unsigned long RequestTemp = 5000;  

unsigned long BaseSensorTemp = 0;
unsigned long BaseSensorTime = 2000;  // 传感器读取的执行间隔

unsigned long AdvancedSensorTemp = 0;
unsigned long AdvancedSensorTime = 1000;  // 传感器读取的执行间隔

int pinDHT11 = 16; //溫濕度
int pinRain = 5;
int pinHumi = 4;

bool RainData = 0;
int HumiData = 0;
byte TempData = 0;
byte SoilData = 0;

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
    PostRequest();
    RequestTime = MS;
  }

  // 读取下雨感測器
  if (MS - AdvancedSensorTemp >= AdvancedSensorTime) {
    readSensorData2();
    AdvancedSensorTemp = MS;
  }

  // 在主循环中可以执行其他操作
}

void readSensorData2(){
  RainData = !digitalRead(pinRain);
  HumiData = analogRead(pinHumi);
}

void readSensorData() {
  // 读取传感器数据
  int err;
  if ((err = dht11.read(pinDHT11, &TempData, &SoilData, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.print(err); Serial.println("SimpleDHT");
    return;
  }
}

void PostRequest() {
  // 执行HTTP请求函数
  HTTPClient http;

  // 创建一个WiFiClient实例，以便将其传递给HTTPClient
  WiFiClient client;

  // 使用WiFiClient实例创建HTTP连接
  http.begin(client, apiUrl);

  // 设置HTTP请求头（如果需要）
  http.addHeader("Content-Type", "application/json");  // 设置请求头为JSON格式

  // 准备要发送的数据
  String data = "{\"humd\": " + String(SoilData) + ", \"temp\": " + String(TempData) + ", \"elev\": " + String(500) + ", \"pres\": " + String(HumiData)+ "}";

  int httpCode = http.POST(data);

  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println("HTTP POST request successful");
    Serial.println("Response: " + payload);
  } else {
    Serial.println("HTTP POST request failed");
  }

  http.end();
}
