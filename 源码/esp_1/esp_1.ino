#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <BH1750.h>
#include <DHT.h>
#include <Wire.h>

#define DHTPIN 14 
#define DHTTYPE    DHT11  

float t = 0.0;
float h = 0.0;
int time_add=0;
int LED =2;
//const char *ssid = "ZTE-E8820S"; // Enter your WiFi name
//const char *password = "12345678";  // Enter WiFi password
const char *mqtt_broker = "rise.rnrn.tk";
const int mqtt_port = 5010;//默认1883，传透至5010
WiFiClient espClient;
PubSubClient client(espClient);
BH1750 lightMeter;
DHT dht(DHTPIN, DHTTYPE);

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

void delwifi()
{
    ESP.eraseConfig();
    delay(1000);
    Serial.println("已清除wifi信息，正在重启！");
    ESP.reset();
    ESP.restart();
}


void bled()
{
 digitalWrite(LED_BUILTIN, LOW);
 delay(10);
 digitalWrite(LED_BUILTIN, HIGH);
}

void setup() {
    // Set software serial baud to 115200;
    Serial.begin(115200); 
    dht.begin();
    pinMode(LED, OUTPUT); 
    Wire.begin();
    lightMeter.begin();
    wifi();
    // connecting to a WiFi network
//    WiFi.begin(ssid, password);
//    while (WiFi.status() != WL_CONNECTED) {
//        delay(500);
//        Serial.println("Connecting to WiFi..");
//    }
    
    Serial.println("Connected to the WiFi network");
    //connecting to a mqtt broker
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    while (!client.connected()) {
        Serial.println("Connecting to public emqx mqtt broker.....");
        if (client.connect("esp8266-client")) {
            Serial.println("Public emqx mqtt broker connected");
        } else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
    // publish and subscribe
    
    client.subscribe("LXED");
}

void callback(char *topic, byte *payload, unsigned int length) 
{
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) 
    {
        Serial.print((char) payload[i]);
    }
}
//读取数据发送到串口 发布到MQTT
void read_data() 
{
   //检测温度
   float newT = dht.readTemperature();
    if (isnan(newT)) 
    {
      Serial.println("Failed to read from DHT sensor!");
    }
    else 
    {
      t = newT;
      Serial.print("温度:");
      Serial.print(t);
      Serial.println("°C");
    }  
    
    //检测湿度
    float newH = dht.readHumidity();
    // if humidity read failed, don't change h value 
    if (isnan(newH)) 
    {
      Serial.println("Failed to read from DHT sensor!");
    }
    else 
    {
      h = newH;
      Serial.print("湿度:");
      Serial.print(h);
      Serial.println("%");
    }

    //检测光照度
    float lux = lightMeter.readLightLevel();
    Serial.print("光照度: ");
    Serial.print(lux);
    Serial.println("lx");  

    //发布到MQTT
    client.publish("esp_1/Temperature",String(t).c_str(), true);
    client.publish("esp_1/Humidity",String(h).c_str(), true);
    client.publish("esp_1/Light",String(lux).c_str(), true);
}

String s1="delwifi";
void loop() {
    client.loop();
    delay(1000);
    time_add++;
    if(time_add%15==0)   //每十五秒上传一次数据
    {
      read_data();   //显示数据
      bled();
    }
    if(time_add==60)
    {
      time_add=0;
    }
    
  if(Serial.available()){
  String s=Serial.readStringUntil('\n');
  if (s.indexOf(s1)!=NULL)
   {   
    delwifi();
   }
  }
    
}
