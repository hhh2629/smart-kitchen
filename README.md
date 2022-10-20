

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
