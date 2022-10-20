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
#define AUTHOR_EMAIL "674695729@qq.com"
#define AUTHOR_PASSWORD "jdglvmioqjybbcci"
/* Recipient's email*/
#define RECIPIENT_EMAIL "674695729@qq.com"
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
