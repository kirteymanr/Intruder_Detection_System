>#  E3-258 Design for IoT
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;M.Tech. Electronic Product Design 2022-24
># Intrusion Detection System 

####  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; - PATIL SARVJIT AJIT
####  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; - KIRTEYMAN RAJPUT

>## Door Mat

####  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; - PATIL SARVJIT AJIT

>## Installation

>### Libraries
Use the library manager to include following libraries 

* [UniversalTelegramBot](https://www.arduinolibraries.info/libraries/universal-telegram-bot) or [this](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot)

* [ArduinoJson](https://www.arduinolibraries.info/libraries/arduino-json) 

* [WiFi](https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/src/WiFi.h) 

* [WiFiClientSecure](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFiClientSecure) 


>## Usage

>### *1. Telegram Bot*
#### Making own Telegram Bot
*  Follow [this](https://www.hackster.io/Salmanfarisvp/telegram-bot-with-raspberry-pi-f373da) tutorial (step -1) to make you telegram bot.

* We need to have chat ID that our Telegram bot generates when first message is sent to the bot. This chat is is then further used for sharing messages.

* To get this chat ID, in Arduino IDE go to File -> Examples -> UniversalTelegramBot -> ESP32 -> EchoBot

* Run this example code and send message to the bot you just created in the last step. Now the chat ID is displayed on the Serial Monitor. 

* Copy this and save this some where because we need this ID to send the alert messages later.

>### *2. Wifi*
  * Use [this](https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/) tutorial to get more functionalities of ESP32 WiFi and BLE 

>### *3. Intruder Detection using doot mat*
* You will find the code for same in Design of IoT - 2022 July -> Intruder Detection System -> Door Mat -> Using ESP32 -> SP_Matrix_v9_ESP_32_LPM_28-11-2022
* You need to change some lines of code for WiFi connection and Telegram Chat ID for sending message to your chat ID.

```c
const char* ssid = "Your_SSID";
const char* password = "Your_Password";
```

```c
#define CHAT_ID "Your_chat_ID"
```
>#### *3.1 Connections*

* The mat will have 4 rows and 7 columns. 

* The 7 columns are connected to following digital pins of ESP32 : 4, 16, 17, 5, 18, 3, 15.

* The 4 rows are connected to following analog pins of ESP32 : 39, 34, 35, 32.

* Velostat connections are shown below

![](https://raw.githubusercontent.com/sarvp/Universal-Remote/IoT_Images/img/velostat_con.png)

* Connection to each of the row pins are as follows

![](https://raw.githubusercontent.com/sarvp/Universal-Remote/IoT_Images/img/Interfacing_Velostat.png)



* After all the connections the mat looks like 

![](https://raw.githubusercontent.com/sarvp/Universal-Remote/IoT_Images/img/Mat_img.png)


>#### *3.2 Setting the Authentication Key*

You can set the following matrices in the code to set your own authentication key.

```python
int key_1 [rownum] [columnnum] =   {0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 1, 1, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,};

int key_2 [rownum] [columnnum] =   {0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 1, 1, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0,};
```
* The '1' s in the arrays denote the nodes on the mat to be stamped on.

* The Key_1 tells you where the first step has to be stamped in order to start authenticated.

* The Key_2 tells where the second step has to be stamped in get authenticated before 3 seconds after starting authentication.

* Now you can upload the code on ESP32 and run the system.

>#### *3.3 Running the system*

* Once the ESP32 flshed and started, first it connects to WiFi and sends message to your Telegram chat through the Bot you created previously.

* When any intruder stamps on the mat, atleast two consecutive nodes will get activated (cross the threshold). This implies step detection, which is conveyed to the authorised user by sending alert message to the telegrsm chat.

>#### *3.4 Authenticating yourself*

* In order to authenticate yourself you have to stamp on the nodes of mat according to the Keys you set in step 1.2.

* When person starts the authentication process by stepping on the mat according to the Key_1, the blue LED on ESP32 will be be turned ON for 3 seconds, which is the time before which you have to complete the authentication by stepping on nodes of mat according to the Key_2 set earlier.

* If authentication is successfull the BLUE LED will blink trice with delay 300 ms and sends the message stsing user is authenticated.

>#### *3.5 Understanding LED notifications*

1. Connecting to the WiFi :
 
 * Failed -> BLUE LED blinks every 300 ms.

 * Successful & Message Sent -> BLUE LED will be ON for 1000 ms.

3. On staring Authentication -> BLUE LED will be ON for 3000 ms.

4. On successful authentication -> BLUE LED will blink thrice for 300 ms.


