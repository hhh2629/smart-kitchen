#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <Servo.h>

#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <AsyncMqttClient.h>

//#define WIFI_SSID "ZTE-E8820S"
//#define WIFI_PASSWORD "12345678"

//#define MQTT_HOST IPAddress(www.xiaotao2333.top)
#define MQTT_HOST "rise.rnrn.tk"
#define MQTT_PORT 5010 //默认1883，传透至5010

// Temperature MQTT Topics
#define MQTT_PUB_TEMP "esp_2/temperature"
#define MQTT_PUB_HUM  "esp_2/humidity"
#define MQTT_PUB_SMOK "esp_2/smoker"
#define MQTT_PUB_RAIN "esp_2/rain"
#define MQTT_PUB_POS  "esp_2/pos"


AsyncMqttClient mqttClient;
Ticker mqttReconnectTimer;
WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
Ticker wifiReconnectTimer;


#define DHTPIN 5
#define DHTTYPE    DHT11     // DHT 11
DHT dht(DHTPIN, DHTTYPE);

const int analogInPin = A0;  //ESP8266模拟引脚ADC0,也就是A0
int sensorValue = 0;
int rain = 4;//D2
int key = 12;//D6
int LED =2;
int duoji_satage;//全局变量储存舵机角度

Servo myServo;  // 定义Servo对象来控制
int pos = 0;    // 角度存储变量
int rain_satage;


void connectToWifi() {
  Serial.println("Connecting to Wi-Fi...");
 // WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  wifi();
}

void connectToMqtt() {
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}

void onWifiConnect(const WiFiEventStationModeGotIP& event) {
  Serial.println("Connected to Wi-Fi.");
  connectToMqtt();
}

void onWifiDisconnect(const WiFiEventStationModeDisconnected& event) {
  Serial.println("Disconnected from Wi-Fi.");
  mqttReconnectTimer.detach(); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
  wifiReconnectTimer.once(2, connectToWifi);
}

void onMqttConnect(bool sessionPresent) {
  Serial.println("Connected to MQTT.");
  Serial.print("Session present: ");
  Serial.println(sessionPresent);

  uint16_t packetIdSub = mqttClient.subscribe("key_ctrl", 2);
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  Serial.println("Disconnected from MQTT.");

  if (WiFi.isConnected()) {
    mqttReconnectTimer.once(2, connectToMqtt);
  }
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos) {
  Serial.println("Subscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
  Serial.print("  qos: ");
  Serial.println(qos);
}
void onMqttUnsubscribe(uint16_t packetId) {
  Serial.println("Unsubscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
  Serial.println("Publish received.");
  Serial.print("  topic: ");
  Serial.println(topic);
  Serial.print("  msg: ");
  for (int i = 0; i < len; i++)
  {
    Serial.print(payload[i]);
  }
  Serial.println();

 if(topic[0]=='k'&&topic[1]=='e'&&topic[2]=='y')
  {
    if(payload[0]=='3')
    {myServo.write(180); duoji_satage=180;}
    if(payload[0]=='2')
    {myServo.write(90); duoji_satage=90;}
    if(payload[0]=='1')
    {myServo.write(0); duoji_satage=0;}
  }

  //待改写
  
}

void onMqttPublish(uint16_t packetId) {
  Serial.println("Publish acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void bled()
{
 digitalWrite(LED_BUILTIN, LOW);
 delay(10);
 digitalWrite(LED_BUILTIN, HIGH);
}
void wifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin();
  int i=0;
  while(i<=30){
    Serial.println(i);
    delay(100);
    if (WiFi.status() == WL_CONNECTED)break;
    i++;
    
  }
  
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("AutoConfig Success");
    Serial.printf("SSID:%s\r\n", WiFi.SSID().c_str());
    Serial.printf("PSW:%s\r\n", WiFi.psk().c_str());
    WiFi.printDiag(Serial);
  }
  else
  {
    smartConfig();//调用smartconfig
  }
}
void smartConfig() {
  Serial.println("begin stmart config...");
  WiFi.beginSmartConfig();
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("place use ESP-touch app to config wifi...");
    digitalWrite(LED, HIGH);
    
    delay(300);
    digitalWrite(LED, LOW);
    delay(300);
    if (WiFi.smartConfigDone()) {
      Serial.println("\r\nsmartconfig success");
      Serial.printf("SSID:%S", WiFi.SSID().c_str());
      Serial.printf("PW:%s", WiFi.psk().c_str());
      break;
    }
  }
}
/*
 smartconfig 配套清除wifi信息函数
*/
void delwifi()
{
    ESP.eraseConfig();
    delay(1000);
    Serial.println("已清除wifi信息，正在重启！");
    ESP.reset();
    ESP.restart();
}

void read_data()
{
  float newT = dht.readTemperature();
  float newH = dht.readHumidity();

  sensorValue = analogRead(analogInPin);
  rain_satage=digitalRead(rain);
  
  Serial.print("温度：");
  Serial.println(newT); 
  Serial.print("湿度：");
  Serial.println(newH);
  Serial.print("sensor = ");
  Serial.println(sensorValue);
  Serial.print("rain = ");
  Serial.println(rain_satage);
  Serial.print("key = ");
  Serial.println(digitalRead(key));
  Serial.print("pos = ");
  Serial.println(duoji_satage);
  
  mqtt_pub(newT,newH,sensorValue,rain_satage,duoji_satage);//mqtt 发布
  Serial.println("-------send ok!-------");
}

void mqtt_pub(float newT,float newH,int sensorValue,int rain_satage,int duoji_satage )
{
  uint16_t packetIdPub1 = mqttClient.publish(MQTT_PUB_TEMP, 1, true, String(newT).c_str());
  uint16_t packetIdPub2 = mqttClient.publish(MQTT_PUB_HUM, 1, true, String(newH).c_str());
  uint16_t packetIdPub3 = mqttClient.publish(MQTT_PUB_SMOK, 1, true, String(sensorValue).c_str());
  uint16_t packetIdPub4 = mqttClient.publish(MQTT_PUB_RAIN, 1, true, String(rain_satage).c_str());
  uint16_t packetIdPub5 = mqttClient.publish(MQTT_PUB_POS, 1, true, String(duoji_satage).c_str());
  
}


void duoji(int pos)
{
  myServo.write(pos);
  delay(1000);
}

int k=0;
void key_ctrl()
{
  if(digitalRead(key)==1)
  {
    delay(3);
    if(digitalRead(key)==1)
    { k++;
      //Serial.println(digitalRead(key));
      if(k%2==0)
      {duoji(180);duoji_satage=180;}
      else{duoji(0);duoji_satage=0;}
      
    }
  }
}


void setup(){
  Serial.begin(115200);
  myServo.attach(2,554,2500);//（针脚，方波最小，方波最大）
  dht.begin(); 
  pinMode(rain, INPUT);
  pinMode(key, INPUT);
  pinMode(LED, OUTPUT);
  wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
  wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onSubscribe(onMqttSubscribe);
  mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);

  connectToWifi();
  

}
int time_add=0;
String s1="delwifi";
void loop(){  

  
  key_ctrl();
 // myServo.write(sensorValue*0.17578125);
  delay(1000);
  time_add++;
  if(time_add%15==0)
  {
    read_data();
    bled();
  }
  if(time_add==60)
  {time_add=0;}

  if(Serial.available()){
  String s=Serial.readStringUntil('\n');
  if (s.indexOf(s1)!=NULL)
   {   
    delwifi();
   }
  }
  
}
