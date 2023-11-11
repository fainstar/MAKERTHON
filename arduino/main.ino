#include <SimpleDHT.h>

int pinDHT11 = A0;
SimpleDHT11 dht11;

void setup() {
  Serial.begin(9600);
  pinMode(A1, INPUT);  
  pinMode(2, INPUT);  

}

void loop() {
  int num = analogRead(A1);  
  int num2 = digitalRead(2);  

  byte temperature = 0;
  byte humidity = 0;
    int err = SimpleDHTErrSuccess;
    Serial.println("=================================");
    if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
       Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
       return;
    }
  
  Serial.print("土壤 = ");
  Serial.println(num);
   Serial.print("下雨 = ");
  Serial.println(num2);
  Serial.print("湿度 = ");
  Serial.println((int)humidity);
  Serial.print("温度 = ");
  Serial.print((int)temperature);
  Serial.println("C");

  delay(500);  // 每3秒显示一次
}
