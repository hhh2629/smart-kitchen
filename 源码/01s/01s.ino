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
