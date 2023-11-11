#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SimpleDHT.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>  



const char* ssid = "Wifi4";
const char* passphrase = "asdfghjkl";

unsigned long DebugTime = 0;
unsigned long DebugTemp = 100;  

unsigned long RequestTime = 0;
unsigned long RequestTemp = 5000;  

unsigned long BaseSensorTemp = 0;
unsigned long BaseSensorTime = 2000; 

unsigned long AdvancedSensorTemp = 0;
unsigned long AdvancedSensorTime = 1000;  

unsigned long ServerTemp = 0;
unsigned long ServerTime = 1000; 


const int button1Pin = 15;  // 按钮连接到数字引脚2

const int pinDHT11 = 16; 
const int pinRain = 5;
const int pinHumi = 4;
const int pinLed = 0;

bool MainMode = 0;
bool DEPL = 1;
bool RainData = 0;
int HumiData = 0;
byte TempData = 0;
byte SoilData = 0;
bool controlValve = 0;
bool autoDetect = 0;
int tempMode = 0;
SimpleDHT11 dht11;

int lastButtonState = HIGH; 
int buttonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; 

void setup() {
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);  
  pinMode(LED_BUILTIN, OUTPUT); 
  pinMode(pinRain, INPUT);
  pinMode(pinHumi, INPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(button1Pin, INPUT); 


  WiFi.begin(ssid, passphrase);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  unsigned long MS = millis();
  handleButton(button1Pin);
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

  // 读取下雨感測器
  if (MS - AdvancedSensorTemp >= AdvancedSensorTime) {
    readSensorData2();
    AdvancedSensorTemp = MS;
  }

  if (MS - ServerTemp >= ServerTime) {
    GetRequest();
    Judge();
    ServerTemp = MS;
  }

  if (MS - DebugTemp >= DebugTime) {
    digitalWrite(LED_BUILTIN,DEPL);
    if(DEPL ==1) DEPL = 0;
    else DEPL = 1;
    DebugTemp = MS;
  }

}

void readSensorData2(){
  RainData = !digitalRead(pinRain);
  HumiData = 1023 - analogRead(pinHumi);
}
void Judge(){
  Serial.print("led type:");
  bool mode = 0;
  if(tempMode == 3) mode = 0;
  if(tempMode == 2) mode = 0;
  if(tempMode == 0) mode = 1;
  if(tempMode == 1){
    if(RainData == 1 && SoilData < 800) mode = 0;
    else mode = 1;
  } 
  if(MainMode == 1) mode = 0; 
  digitalWrite(pinLed,mode); 
  Serial.println(mode);
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
  HTTPClient http;
  WiFiClient client;
  String apiUrl = "http://49.213.238.75:8000/i/local";  
  http.begin(client, apiUrl);
  http.addHeader("Content-Type", "application/json");
  DynamicJsonDocument jsonDoc(256);  
  jsonDoc["humd"] = float(SoilData);
  jsonDoc["temp"] = float(TempData);
  jsonDoc["elev"] = 500.0;
  jsonDoc["pres"] = float(HumiData);
  String data;
  serializeJson(jsonDoc, data);
  // Serial.println(data);
  int httpCode = http.POST(data);
  if (httpCode > 0) {
    String payload = http.getString();
    // Serial.println("HTTP POST request successful");
    // Serial.println("Response: " + payload);
  } else {
    String temp = http.errorToString(httpCode).c_str();  // 获取HTTP错误信息
    Serial.println("HTTP POST request failed. Error: " + temp);
  }
  http.end();
}
void GetRequest() {
  HTTPClient http;
  WiFiClient client;
  String apiUrl = "http://49.213.238.75:8000/i/setting";  
  http.begin(client, apiUrl);
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.GET();
  if (httpCode > 0) {
    String payload = http.getString();
    // Serial.println("HTTP GET request successful");
    // Serial.println("Response: " + payload);
    // 解析JSON响应
    DynamicJsonDocument doc(256); 
    DeserializationError error = deserializeJson(doc, payload);
    // 检查是否解析成功
    if (error) {
      Serial.print("JSON解析失败: ");
      Serial.println(error.c_str());
      return;
    }
    // 提取变量的值
    controlValve = doc["control_valve"];
    autoDetect = doc["auto_detect"];
    tempMode = int(controlValve) * 2 + int(autoDetect);
    Serial.print("control_valve: ");
    Serial.println(controlValve);
    Serial.print("auto_detect: ");
    Serial.println(autoDetect);
    Serial.print("temp:");
    Serial.println(tempMode);
  } else {
    String temp = http.errorToString(httpCode).c_str(); 
    Serial.println("HTTP GET request failed. Error: " + temp);
  }
  http.end();
}

void handleButton(int pin) {
  int reading = digitalRead(pin);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        Serial.println("Button pressed.");
        if(MainMode == 0) MainMode = 1;
        else MainMode = 0;
      }
    }
  }
  lastButtonState = reading;
}
