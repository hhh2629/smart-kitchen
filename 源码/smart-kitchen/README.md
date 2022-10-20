

# 1、背景介绍

随着科技的进步，智慧厨房系统也随之得到迅猛发展。智慧厨房系统利用主机，通过无线或有线连接各类探测器，实现防盗报警功能。此系统通常由：探测器(又称报警器)、传输通道和报警控制器三部分构成。传感器是监测探测器的核心元件。采用不同原理的传感器件，可以构成不同种类、不同用途、达到不同探测目的的报警探测装置。常见的探测器有红外人体感应器，门窗磁感应器，烟雾火灾探测器，燃气泄漏探测器等。本系统选用温DHT11温湿度传感器，BH1750光照传感器，MQ135空气质量传感器，雨滴传感器。为人们提供一个安全，舒适，智能的厨房环境，保证家庭人员的安全。

 ![系统组成及逻辑功能](https://s2.loli.net/2022/08/15/oKq8LdI2FZASCv7.png)



<center> 图1 系统框架</center>



# 2、系统框架设计

本系统主要包括感知设备、通信设备、处理装置3 个部分；单片机使用的是国产芯片乐鑫科技的ESP-8266及ESP-01s两种芯片，系统组成及逻辑功能如图1所示。





<img src="https://i2.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/05/ESP8266-NodeMCU-kit-12-E-pinout-gpio-pin.png?w=817&quality=100&strip=all&ssl=1" style="zoom:67%;" />

<center> 图2-2 esp8266单片机</center>



 

 

此系统能够实现多种监测报警，比如可燃气泄漏报警、邮箱提醒，温湿度和光照检测，并使用MQTT协议上报数据，服务器进行数据处理。服务器使用的是国产嵌入式微计算机香橙派4lts，具有高性价比同时兼顾性能。

 

 

# 3、通信协议选择

​         现主流的物联网通信协议有很多，如NB-IOT，ZigBee，*LoRa**，Wi-Fi，蓝牙等；在本项目中，鉴于在家庭内使用，不需要安全性高，速率高的通信协议，只需要保证每个家庭都具有，且成本较低，种种平衡之下，我们选择了Wi-Fi的2.4GHz频段。*

​        无线网络上网可以简单的理解为无线上网，几乎所有智能手机、平板电脑和笔记本电脑都支持Wi-Fi上网，是当今使用最广的一种无线网络传输技术。实际上就是把有线网络信号转换成无线信号，就如在开头为大家介绍的一样，使用无线路由器供支持其技术的相关电脑，手机，平板等接收。手机如果有Wi-Fi功能的话，     

​          在有Wi-Fi无线信号的时候就可以不通过移动联通的网络上网，省掉了流量费。并且本项目的开发板也支持Wi-Fi协议。使用此协议还有一个好处是发射Wi-Fi信号的路由器还可充当物联网设备的网关，使得设备的接入更容易。

![img](https://s2.loli.net/2022/08/15/7KeP9XdjHpYbtGn.jpg)

<center>图3-1 Wi-Fi网关 </center>



​      我们的数据传输协议采用的是MQTT协。MQTT(消息队列遥测传输)是ISO 标准(ISO/IEC PRF 20922)下基于发布/订阅范式的消息协议。它工作在 TCP/IP协议族上，是为硬件性能低下的远程设备以及网络状况糟糕的情况下而设计的发布/订阅型消息协议，为此，它需要一个消息中间件 。

​       MQTT是一个基于客户端-服务器的消息发布/订阅传输协议。MQTT协议是轻量、简单、开放和易于实现的，这些特点使它适用范围非常广泛。在很多情况下，包括受限的环境中，如：机器与机器（M2M）通信和物联网（IoT）。

![img](https://s2.loli.net/2022/08/15/KrEa3BoXgl5s1mG.gif)

<center> 图3-2 MQTT</center>



 

 

![img](https://s2.loli.net/2022/08/15/ewL6EjrXukHtMPK.jpg)

<center>图3-3 本项目使用的主题 </center>



 

# 4、服务器选择

​       本项目原先想选择国内较火的阿里云，腾讯云主流的物联网平台，其优点是实时性高，24小时在线，但是其也有很多缺点，一是其免费的消息度是有限的，每个用户每个月只有几万条消息额度，超过是需要收费的；其二是操作门槛较高，需要有一定的网络知识，繁琐的验证机构等，这与家庭使用场景就产生冲突了；种种权衡之下，我们选择了自建服务器，自建物联网服务平台，省去很多麻烦的情况下还能长久使用，又可基于内网和外网开发，相比之下不存在消息额度，非常具有性价比。

我们最终选择了国产的开发板公司香橙派公司出品的嵌入式微计算机 香橙派4 lts开发板，其搭载了Ubuntu 16.4系统，高效流畅的运行本项目所需的服务程序。

![image-20220815144705283](https://s2.loli.net/2022/08/15/wRU3xL4dOASM8mF.png)

<center> 图4-1 香橙派4lts嵌入式微计算机</center>

# 5、系统硬件设计

### 5.1、 ESP_01室内监测模块





![image-20220825212644907](https://s2.loli.net/2022/08/25/4M8S5rWNE7BKfiF.png)

 

<center>图5-1室内监控模块 </center>



![image-20220825212754323](https://s2.loli.net/2022/08/25/EIoBftMjaQX4dvb.png)

<center> 图5-2室内监控模块流程图</center>

 

![image-20220825212854923](https://s2.loli.net/2022/08/25/uRJxgbKkMYTreEm.png)

<center>图5-3室内监控模块实物图 </center>





​       室内监测模块较为简单，使用两个传感器，分别是DHT11温湿度传感器及BH1750光照传感器，单片机使用的是esp8266，主要功能是监测室内环境的温湿度及光照，并进行数据上报，配合服务器监测室内环境。其中，BH1750使用的是IIC协议，只需两根线即可完成读取工作，DHT11为库函数调用。

![image-20220825212926264](https://s2.loli.net/2022/08/25/jOsRwtfBxpFubN7.png)

<center> 图5-4室内监测模块电路图</center>

#### 模块源码

```c
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

```



### 5.2、 ESP_2室外监测模块

 

![](https://s2.loli.net/2022/08/25/9YSWz6P5y3wAGJM.png)

<center> 图5-5室外监测模块</center>



![](https://s2.loli.net/2022/08/25/omlFBSk7WPEGjZb.png)

<center> 图5-6室外监测模块实物图</center>



 

![image-20220825213649428](https://s2.loli.net/2022/08/25/eSjkoirTQUg1JdM.png)

<center>图5-7室外监测模块流程图 </center>



​            室外监控模块使用了三个传感器：MQ135空气质量传感器读取空气质量，DHT11温湿度传感器以及一个雨滴传感器MH-RD;单片机也使用是esp8266；主要功能是监控室外（主要是窗处）的环境变量，判断室内外的差异，并进行数据上报或是命令接收；按键为强制控制舵机，一共三个挡位，0°，90°及180°。当无网络或紧急状态是，此按键无需网络即可控制舵机的开合度，继而达到控制窗户或其他部件。

![](https://s2.loli.net/2022/08/25/AanHLKMFe792IsU.png)

<center>图5-8室外监测模块电路图 </center>

#### 模块源码

```
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

```

 

### 5.3、 ESP_3中控模块

 

​                               

<img src="https://s2.loli.net/2022/08/27/phPZoLTyex2zbEr.png" alt="image-20220827152421449" style="zoom:50%;" />

<center> 图5-9 中控模块</center>

![image-20220827152953768](https://s2.loli.net/2022/08/27/hp64Z5rbRJEvCo3.png)

 

<center>图5-10 中控模块实物图 </center>



​        其中LCD屏幕作为数据展示，两个按键分别绑定在室外监控模块的舵机上和继电器模块上，实现远程控制的作用，此功能需要所有设备接入网络和服务器，若模块离线或者服务器离线则起不到远程控制的作用，可以去模块本身的按键控制模块。

 

![image-20220827153046214](https://s2.loli.net/2022/08/27/IiUKbHvBLRQh3o4.png)

<center> 图5-11 中控模块流程图</center>



​        此模块为中控模块，主要功能为数据展示和按键远程控制舵机与继电器的状态。LCD屏幕有三页屏，分别是时钟页，数据页和二维码页，如图所示：

 ![image-20220827153416788](https://s2.loli.net/2022/08/27/HMA7DYvCtjPwRkq.png)

​     

<center>图5-12 中控模块LCD页 </center>



![](https://s2.loli.net/2022/08/27/QrHADhvNIVolJFa.png)

<center> 图5-13 中控模块电路图</center>



 

 

​         中控模块连接服务器后订阅系统内的各个量，收到数据会处理后显示在LCD屏幕的相应位置上，当某些量超过阈值会做出相应动作，比如空气质量值，小于500为绿色，500至700为黄色，以上为红色，若超过阈值太多次则会触发邮件发送命令，为用户邮箱发送一封报警邮件。至于为什么选择邮件方式是因为邮箱普遍人均一个，不需要成本，且及时方便。

 

![](https://s2.loli.net/2022/08/27/Uq3rjVoSk2dn9QO.png)

 

<center> 图5-14 报警邮件</center>

#### 模块源码

```C
#include <SPI.h>//导入库
#include <TFT_eSPI.h>
#include <Ticker.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <AsyncMqttClient.h>
#include "String.h"
#include <ESP_Mail_Client.h>
#include "2.h"

#define MQTT_HOST "rise.rnrn.tk"
#define MQTT_PORT 5010  //默认1883，传透至5010
#define MQTT_PUB_POS  "esp_2/pos"
#define MQTT_PUB_ESW  "01s/switch"

#define SMTP_HOST "smtp.qq.com"
#define SMTP_PORT 465
/* The sign in credentials */
#define AUTHOR_EMAIL "**********qq.com"//发送邮箱
#define AUTHOR_PASSWORD "**********"//stmp密钥
/* Recipient's email*/
#define RECIPIENT_EMAIL "********@qq.com"//收件邮箱
/* The SMTP Session object used for Email sending */
SMTPSession smtp;
SMTP_Message message;
/* Callback function to get the Email sending status */
void smtpCallback(SMTP_Status status);
void stmp_server();



AsyncMqttClient mqttClient;
Ticker mqttReconnectTimer;

WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
Ticker wifiReconnectTimer;

#define WIFI_SSID "ZTE-E8820S"
#define WIFI_PASSWORD "12345678"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp.aliyun.com"); //NTP地址

TFT_eSPI tft = TFT_eSPI();
//Ticker ticker;

int s=0,m=0,h=0,d=0,mon=0,w=1;//时间
String ss,mm,hh;

int esp_2t,esp_2h,esp_2s,esp_2r,esp_2p;
int esp_1t,esp_1h,esp_1l;
int e01s_s;
int send_email_cmd=0,send_time=0;
int key1=16,key2=4,LED=2;

void wifi();
void net_time();
void get_time();
void key_1();
void key_2();



/*smtp初始化*/
void stmp_server()
{
  /** Enable the debug via Serial port
     none debug or 0
     basic debug or 1
  */
  smtp.debug(1);

  /* Set the callback function to get the sending results */
  smtp.callback(smtpCallback);

  /* Declare the session config data */
  ESP_Mail_Session session;

  /* Set the session config */
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = "";

  /* Declare the message class */
  /*SMTP_Message message;*/

  /* Set the message headers */
  message.sender.name = "ESP-SAFT";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "warming！";
  message.addRecipient("Sara", RECIPIENT_EMAIL);
  /*Send HTML message*/
  String htmlMsg = "<div style=\"color:#2f4468;\"><h1>家庭内存在异常，请及时检查，若无法避免，请及时逃生！</h1><p>- Sent from ESP board</p></div>";
  message.html.content = htmlMsg.c_str();
  message.html.content = htmlMsg.c_str();
  message.text.charSet = "us-ascii";
  message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  /*
    //Send raw text message
    String textMsg = "Hello World! - Sent from ESP board";
    message.text.content = textMsg.c_str();
    message.text.charSet = "us-ascii";
    message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

    message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
    message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;*/

  /* Set the custom message header */
  //message.addHeader("Message-ID: <abcde.fghij@gmail.com>");

  /* Connect to server with the session config */
  if (!smtp.connect(&session))
    return;



  /* Start sending Email and close the session */
  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());

}







void wifi()
{
  WiFi.mode(WIFI_STA);
  //WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
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





void connectToWifi() {
  Serial.println("Connecting to Wi-Fi...");
  //WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
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

  uint16_t packetIdSub1 = mqttClient.subscribe("esp_2/temperature", 2);
  uint16_t packetIdSub2 = mqttClient.subscribe("esp_2/humidity", 2);
  uint16_t packetIdSub3 = mqttClient.subscribe("esp_2/smoker", 2);
  uint16_t packetIdSub4 = mqttClient.subscribe("esp_2/rain", 2);
  uint16_t packetIdSub5 = mqttClient.subscribe("esp_2/pos", 2);

  uint16_t packetIdSub6 = mqttClient.subscribe("esp_1/Temperature", 2);
  uint16_t packetIdSub7 = mqttClient.subscribe("esp_1/Humidity", 2);
  uint16_t packetIdSub8 = mqttClient.subscribe("esp_1/Light", 2);

  uint16_t packetIdSub9 = mqttClient.subscribe("01s/switch", 2);

  uint16_t packetIdSub10 = mqttClient.subscribe("email", 2);

  //带改写
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
  char t[len];
  for (int i = 0; i < len; i++)
  {
    Serial.print(payload[i]);
    t[i]=payload[i];
    digitalWrite(LED, LOW);
    digitalWrite(LED, HIGH);
  }
  Serial.println();
  
  if(topic[4]=='2'&&topic[6]=='t') //out_temp
  { String s=t;
    esp_2t=s.toInt();
  }
  if(topic[4]=='2'&&topic[6]=='h')//out_hum
  { String s=t;
    esp_2h=s.toInt();
  }
  if(topic[4]=='2'&&topic[6]=='p')//out_pos
  { String s=t;
    esp_2p=s.toInt();
  }
  if(topic[4]=='2'&&topic[6]=='r')//out_rain
  { String s=t;
    esp_2r=s.toInt();
  }
  if(topic[4]=='2'&&topic[6]=='s')//out_smoker
  { String s=t;
    esp_2s=s.toInt();
  }
  if(topic[4]=='1'&&topic[6]=='T')//in_temp
  { String s=t;
    esp_1t=s.toInt();
  }
   if(topic[4]=='1'&&topic[6]=='H')//in_temp
  { String s=t;
    esp_1h=s.toInt();
  }
 if(topic[4]=='1'&&topic[6]=='L')//in_temp
  { String s=t;
    esp_1l=s.toInt();
  }
 if(topic[0]=='0'&&topic[1]=='1'&&topic[2]=='s')//switch
  { String s=t;
    e01s_s=s.toInt();
  }

  if(topic[0]=='e'&&topic[1]=='m'&&topic[2]=='a'&&topic[3]=='i')//email
  { if(payload[0]=='1')
    {
    send_email_cmd=1;
    }
  }
  
}
void onMqttPublish(uint16_t packetId) {
  Serial.println("Publish acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}


int t=0,p=0;
void key_1()
{
  
  if(digitalRead(key1)==1)
  {
    delay(3);
    if(digitalRead(key1)==1)
    {  t++;
       Serial.println(t);
       uint16_t packetIdPub1 = mqttClient.publish("key_ctrl", 1, true, String(t).c_str());
       if(t==3){t=0;}
    }
  }
}
void key_2()
{
 if(digitalRead(key2)==1)
  {
    delay(3);
    if(digitalRead(key2)==1)
    {
      p++;
      if(p%2==0)
      {           
        Serial.println(p);
        uint16_t packetIdPub1 = mqttClient.publish(MQTT_PUB_ESW, 1, true, String(0).c_str());
      }
      else{
        uint16_t packetIdPub1 = mqttClient.publish(MQTT_PUB_ESW, 1, true, String(1).c_str());
        }
      if(p==100)
      {p=0;}
      
      
      
    }
  }
  
}
void bled()
{
 digitalWrite(LED_BUILTIN, LOW);
 delay(10);
 digitalWrite(LED_BUILTIN, HIGH);
}


void setup() {
  Serial.begin(115200);
  digitalWrite(key1, LOW);
  digitalWrite(key2, LOW);
  pinMode(key1,INPUT);
  pinMode(key2,INPUT);
  pinMode(LED,OUTPUT);
  

  
  

  tft.setTextColor(TFT_RED);
  tft.drawCentreString("wifi",120,100,6);
  
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
    
  tft.init();//初始化
  tft.fillScreen(TFT_WHITE);//屏幕颜色
 
  
   
}
String s1="delwifi";
void loop() {
  
  get_time(); 
  if((s>0&&s<=10)||(s>30&&s<=40))
  {
     ui_1();   net_time();     //首页
  }
  if((s>10&&s<20)||(s>40&&s<=50))
  {
  display_data();
  }
  if((s>20&&s<=30)||(s>50&&s<=60))
  {
  ui_qrcode();  
  }

    key_1();
    key_2();
    if(send_email_cmd==1)
    { 
      send_time++;
      if(send_time==5)
      {
        stmp_server();
        Serial.println("已发送一封警告邮件！"); 
        uint16_t packetIdPub1 = mqttClient.publish("01s/switch", 1, true, "1"); 
        uint16_t packetIdPub2 = mqttClient.publish("key_ctrl", 1,true, "3");    
        send_time=0;
      }
      send_email_cmd=0;
    }
    

  if(Serial.available()){
  char s=Serial.read();
  if (s=='d')
   {   
    delwifi();
   }
   if (s == 'y')
    {
      //sendemail();
      stmp_server();
      Serial.println("已发送一封警告邮件！");
   }
  }

}


void net_time()
{
  timeClient.begin();
  timeClient.setTimeOffset(28800); //+1区，偏移3600，+8区，偏移3600*8
  timeClient.update();
  unsigned long epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime((time_t *)&epochTime);
  d= ptm->tm_mday;//日
  mon= ptm->tm_mon + 1;//月
  h= timeClient.getHours();   //时
  m= timeClient.getMinutes(); //分
  s= timeClient.getSeconds(); //秒
  w= timeClient.getDay();     //星期
}

void display_data()
{
  tft.fillScreen(TFT_WHITE);//屏幕颜色
  tft.setTextColor(TFT_BLACK,TFT_WHITE);
  tft.drawCentreString("Show  Data", 120, 10, 4);
  tft.drawLine(0, 5, 240, 5, TFT_BLACK),
  tft.drawLine(0, 45, 240, 45, TFT_BLACK),
  /*名称-----------------------------------------数据------------------------------单位*/
  tft.drawString("T_IN :", 10, 50,2);   tft.drawString((String)esp_1t, 50, 50,2);     tft.drawString("c", 70, 50,2);
  tft.drawString("H_IN :", 10, 90,2);   tft.drawString((String)esp_1h, 50, 90,2);     tft.drawString("%", 70, 90,2);
  tft.drawString("L_IN :", 10, 130,2);  tft.drawString((String)esp_1l, 50, 130,2);  tft.drawString("lx", 90, 130,2);
  tft.drawString("T_OUT :", 10, 170,2); tft.drawString((String)esp_2t, 65, 170,2);    tft.drawString("c", 90, 170,2);
  tft.drawString("H_OUT :", 10, 210,2); tft.drawString((String)esp_2h, 65, 210,2);    tft.drawString("%", 90, 210,2);
  
  tft.drawString("RAIN   :", 120, 50,2);
  if(esp_2r==1){
   tft.fillCircle(190,56,8,TFT_GREEN);
  }else{tft.fillCircle(190,56,8,TFT_RED);}
  
  tft.drawString("SWITCH:", 120, 90,2); 
  if(e01s_s==0)
  { tft.fillCircle(190,96,8,TFT_GREEN);}
  if(e01s_s==1){tft.fillCircle(190,96,8,TFT_BLACK);}

  
  tft.drawString("SMOKER:", 120, 130,2);
  if(esp_2s<500)
  {tft.fillCircle(190,136,8,TFT_GREEN);}
  if(esp_2s>500&&esp_2s<700)
  {tft.fillCircle(190,136,8,TFT_YELLOW);}
  if(esp_2s>700){tft.fillCircle(190,136,8,TFT_RED);}

  
  tft.drawString("EN_POS:", 120, 170,2);
  tft.drawString((String)esp_2p, 183, 170,2);


}

void ui_1(){
  
  tft.fillScreen(TFT_WHITE);//屏幕颜色
  tft.drawLine(0, 5, 240, 5, TFT_BLACK),
  tft.drawLine(0, 45, 240, 45, TFT_BLACK),
  tft.setTextColor(TFT_BLACK,TFT_WHITE);
  tft.drawCentreString("Smart  Home", 120, 10, 4); // Draw text centre at position 80, 24 using font 4

  /*连接*/
  tft.drawString("MQTT", 20, 50,2);
  tft.fillCircle(70,56,8,TFT_GREEN);
  tft.drawString("WIFI", 95, 50,2);
  tft.fillCircle(140,56,8,TFT_GREEN);
  tft.drawString("DATA", 165, 50,2);
  tft.fillCircle(210,56,8,TFT_GREEN);

  /*时间*/
  tft.drawString(hh, 27, 90, 6); // Draw text centre at position 80, 24 using font 6 H
  tft.drawString(":", 80, 90, 6); // Draw text centre at position 80, 24 using font 6  :
  tft.drawString(mm, 93, 90, 6); // Draw text centre at position 80, 24 using font 6 M
  tft.drawString(":", 149, 90, 6); // Draw text centre at position 80, 24 using font 6  :
  tft.drawString(ss, 164, 90, 6); // Draw text centre at position 80, 24 using font 6 S

  tft.drawString("Month:", 23, 170, 2);
  tft.drawString((String)mon, 67, 170, 4);
  
  tft.drawString("Day:", 90, 170, 2);
  tft.drawString((String)d, 120, 170, 4);
  
  tft.drawString("Week:", 157, 170, 2);
  tft.drawString((String)w, 197, 170, 4);
  
}

void ui_qrcode(){
  tft.fillScreen(TFT_WHITE);//屏幕颜色
  tft.pushImage(0, 0, 240, 240, (uint16_t*)gImage_qr);
}

void get_time()
{
  delay(1000);
  s++;  
  if(s==60)
  {
    s=0;
    m++;
     
    if(m==60)
    {
       m=0;
       h++;    
       if(h==24)
       {h=0;}
    }
  }
  if(s<10){ss="0"+(String)s;}
     else{ss=(String)s+"   ";}
  if(m<10){mm="0"+(String)m;}
     else{mm=(String)m+"   ";}
  if(h<10){hh="0"+(String)h;}
     else{hh=(String)h+"   ";}
  
  
}



/* Callback function to get the Email sending status
  邮箱回调函数
*/
void smtpCallback(SMTP_Status status) {
  /* Print the current status */
  Serial.println(status.info());

  /* Print the sending result */
  if (status.success()) {
    Serial.println("----------------");
    ESP_MAIL_PRINTF("Message sent success: %d\n", status.completedCount());
    ESP_MAIL_PRINTF("Message sent failled: %d\n", status.failedCount());
    Serial.println("----------------\n");
    struct tm dt;

    for (size_t i = 0; i < smtp.sendingResult.size(); i++) {
      /* Get the result item */
      SMTP_Result result = smtp.sendingResult.getItem(i);
      time_t ts = (time_t)result.timestamp;
      localtime_r(&ts, &dt);
      ESP_MAIL_PRINTF("Message No: %d\n", i + 1);
      ESP_MAIL_PRINTF("Status: %s\n", result.completed ? "success" : "failed");

    }
    Serial.println("----------------\n");
  }

}

```





### 5.4、 ESP_01s继电器模块

![image-20220827154502886.png](https://s2.loli.net/2022/08/27/HMqRD9LBxcXdviY.png)

​                                  

<center> 图 5-15继电器模块</center>



 

![image-20220827155202296](https://s2.loli.net/2022/08/27/Kt89O4wMkI5Ci1T.png)

 

<center> 图 5-16继电器模块实物图</center>



 

![image-20220827155210140](https://s2.loli.net/2022/08/27/B9yoSxuztRvMCjI.png)

<center>图 5-17继电器模块流程图 </center>



![image-20220827155225788](https://s2.loli.net/2022/08/27/hct8V4b1d3NgvRu.png)

<center>图 5-18继电器模块电路图 </center>

​         此模块功能较为单一，主要为接收服务器的命令，进行对继电器的开合，实现电器的开关，使用的为esp8266的最小系统芯片esp01s，优点是低功率，能联网，支持tcp/ip协议，价格低廉，性价比高。底座的控制管脚为GPIO0，故只需控制0口的电平即可控制继电器。

 

#### 模块源码

```C
/*
基本的ESP8266 MQTT示例

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "ZTE-E8820S";//手机Wi-Fi热点名
const char* password = "12345678";//手机Wi-Fi热点密码
const char* mqtt_server = "rise.rnrn.tk";//服务器地址 可以是域名

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int GPIO = 0;
int value = 0;
int ledPin = 2; // GPIO2 of ESP8266




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
    digitalWrite(ledPin, HIGH);
    
    delay(300);
    digitalWrite(ledPin, LOW);
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










void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("接收消息[");Serial.print(topic);Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  if ((char)payload[0] == '1') {          // 通过接收的信息 '1' 来控制开或关
    digitalWrite(GPIO, HIGH); 
    digitalWrite(ledPin, HIGH);
    Serial.println("HIGH  状态：关闭");
  } else {
    digitalWrite(GPIO, LOW); 
    digitalWrite(ledPin, LOW);
    Serial.println("LOW  状态：打开");
  }
}

 
void reconnect() {
    String clientId = "JYC";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {         //连接成功
      client.subscribe("01s/switch");
      client.publish("testone", "state：open[0]");     // 连接成功发送主题和消息
    } else {
      delay(5000);                                  // Wait 5 seconds before retrying
    }
}

void setup() {
  pinMode(GPIO, OUTPUT);
  digitalWrite(GPIO, LOW);  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(115200);
  wifi();
  client.setServer(mqtt_server, 5010);//默认1883，传透至5010
  client.setCallback(callback);
}

String s1="delwifi";

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if(Serial.available()){
  String s=Serial.readStringUntil('\n');
  if (s.indexOf(s1)!=NULL)
   {   
    delwifi();
   }
  }
  
}

```



# 6、系统软件设计

## 6.1 、系统

由于本系统选择在本地化搭建后台，所以选择了Ubuntu，基于Linux框架，系统运行效率高，系统资源占用小，具有很高的实时性。



![image-20220827161056444.png](https://s2.loli.net/2022/08/27/LjMmg4luqhACkG8.png)

方法也很简单，首先到官网下载对应型号的镜像，解压后打开烧写软件，选择u盘写入即可。

烧写好后插电开机插网线。等待开机后查看服务器的ip地址。我们需要用到ssh。

这里说明几个软件：

| win32  | 镜像烧写    |
| ------ | ----------- |
| Putty  | ssh连接     |
| winscp | ftp文件管理 |



登录ssh后简单设置一下时区和软件包更新即可。

## 6.2 、Docker

一键安装命令

```
yum install docker-ce docker-ce-cli containerd.io
```

安装完成后检查版本

```
docker version
```



## 6.3、EMQX 7.0

本项目使用的MQTT需要一个中间件，作为数据的暂存，在嵌入式微计算机中搭建MQTT服务器环境，这里使用的是EMQX软件，优点是有网页可监视数据流向，消息订阅，设备数等功能，还有丰富的插件，数据过滤，数据统计等功能。 

![image-20220827165353051.png](https://s2.loli.net/2022/08/27/26gWCpXxtbsikqo.png)

安装命令：详情参考[官方文档](https://www.emqx.io/docs/zh/v5.0/deploy/install.html#%E9%80%9A%E8%BF%87-docker-%E8%BF%90%E8%A1%8C-%E5%8C%85%E5%90%AB%E7%AE%80%E5%8D%95%E7%9A%84-docker-compose-%E9%9B%86%E7%BE%A4)

```
docker pull emqx/emqx:5.0.0
```



运行命令

```
docker run -d --name emqx -p 1883:1883 -p 8083:8083 -p 8883:8883 -p 8084:8084 -p 18083:18083 emqx/emqx:5.0.0
```

![image-20220827165441393.png](https://s2.loli.net/2022/08/27/KzwJsO6g92BYFUR.png)

本项目中大体分为四个部分，由下至上分别为传感器/执行模块，路由网关，MQTT中间件，前台面板组成。各个模块的功能顾名思义。

| 端口说明 |              |
| -------- | ------------ |
| 1883     | mqtt消息端口 |
| 18083    | 面板端口     |
| 面板账号 | admin        |
| 面板密码 | public       |



## 6.4、NodeRed

​          本项目中采用的是基于node.js框架开发的开源数据处理软件node red；此软件对性能要求较低，时延低，数据处理能力强，还具有图形化开发功能，对一些小项目支持非常友好，而且开源。其中本项目中用到的控件有：mqtt in（数据流入），mqtt out (数据流出)，text（文本），gauge（码表），chart（图表），function（函数），button（按钮）以及switch（开关）和numeric（滑块）等；

1、docker拉取镜像

```
docker pull nodered/node-red
```

2、运行启动容器

```
sudo docker run -it -p 1880:1880 --name=nodered --restart=always --user=root --net=host -v /data/nodered:/data -e TZ=Asia/Shanghai nodered/node-red
```

-v:文件挂载到宿主机上。–net=host：端口与宿主机一样，不用映射。访问1ip:1880,进入node-red界面。 --name 定义容器名字



进入后台1880端口，即可自定义消息展示

![](https://s2.loli.net/2022/08/27/htGzEy3D6c981xe.png)



想要看到展示页面只需在ip:1880后加上/ui即可自动跳转



![2.png](https://s2.loli.net/2022/08/27/Nuq68TX9kZatFgo.png)





# 
