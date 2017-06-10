
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
//#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include <TimeLib.h> 
#include <SoftwareSerial.h>
#include <WiFiUdp.h>
extern "C" {
#include "user_interface.h"
}

// Device ID
uint32_t DeviceID = 12345678;
String host = "api.thingspeak.com";
WiFiClient client;
StaticJsonBuffer<300> jsonBuffer;

// NTP Servers:
//IPAddress timeServer(132, 163, 4, 101); // time-a.timefreq.bldrdoc.gov
const int timeZone = -3;
WiFiUDP Udp;
unsigned int localPort = 8888; 
const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

// NTP Servers:
//static const char ntpServerName[] = "us.pool.ntp.org";
static const char ntpServerName[] = "time.nist.gov";
//static const char ntpServerName[] = "time-a.timefreq.bldrdoc.gov";
//static const char ntpServerName[] = "time-b.timefreq.bldrdoc.gov";
//static const char ntpServerName[] = "time-c.timefreq.bldrdoc.gov";

time_t getNtpTime();

//FRIENDLY NAME
//SmartCare
//SID
//SK8913fbf2dc12dc94140afd697bec5d05
//SECRET
//FjBrjN5kShzQxId26JRuTw0ULELT6AZz

// Wifi possible states
enum WIFI_STATES {SCAN, SETUP_SERVER, WAIT_USER, CONNECT, CONFIGURED} WIFI_STATES;

// Radio possible states
enum RADIO_STATES {OFF, FIND, SYNC} RADIO_STATES;

// AccessPoint possible states
enum POWER_STATES {INITIALIZING, RUNNING} POWER_STATES;

// EEPROM Addresses 
#define EEPROM_CHECK 0
#define EEPROM_STATE 1
#define EEPROM_DEV_ID 2
#define EEPROM_SSID 10
#define EEPROM_PWD 110
#define EEPROM_TS_CHANNEL 220
#define EEPROM_TS_ID 240

#define EEPROM_VALID_KEY 4

#define LED_POWER 12
#define LED_RADIO 13
#define LED_WIFI 14
#define SW_RESET 15
#define AP_TX 5
#define AP_RX 4

String cmdReadWatchData = "";
String cmdSendDateTime = "";
String cmdSendMedicineTimes = "";
String cmdBuffer = "";
char recvTemp = 0;

SoftwareSerial SerialAP(AP_RX, AP_TX);
 
// Wi-Fi Settings
const char *ssid = "SmartCare Wi-Fi";

// E-mail Server Data
const char* IFTTThost = "maker.ifttt.com";
const char* IFTTTapiKey = "lAFacIWQFFrzX6caLAiGHyZQIXdy75OHFAkzqrraCSD";
// Pages
// Index page
const String index_page = "<!DOCTYPE html><html><head> <title>SmartCare - Configuração</title> <style>.loader{border: 16px solid #f3f3f3; border-top: 16px solid #3498db; border-radius: 50%; width: 120px; height: 120px; animation: spin 2s linear infinite; text-align: center;}@keyframes spin{0%{transform: rotate(0deg);}100%{transform: rotate(360deg);}}.title{font-family: verdana; color: rgb(52, 73, 94); text-align: center; font-size: 100%;}.input{font-family: verdana; box-sizing: border-box; z-index: 21; height: 45px; width: 304px; border: 2px solid rgb(189, 195, 199); background-color: rgb(255, 255, 255); border-radius: 5px; font-size: 14px; color: rgb(52, 73, 94); padding: 0px 6px; transition: border-color 200ms ease;}.button{box-sizing: border-box; z-index: 18; height: 40px; width: 125px; padding: 0px; cursor: inherit; background: none rgb(26, 188, 156); border: none; text-align: center; font-family: verdana; font-size: 14px; color: rgb(255, 255, 255); line-height: 1; border-radius: 5px; transition: box-shadow 200ms ease, background 200ms ease; box-shadow: none;}</style></head><body style='text-align: center; width: 100%'> <h1 class='title' style='font-size:300%;'>SmartCare</h1> <h1 class='title'>Olá! Vamos realizar a configuração do seu SmartCare em apenas um passo!</h1> <h1 class='title'>Para isso, informe os dados abaixo. É necessário ao menos um e-mail para finalizar a configuração. Caso não saiba algum dos campos, você pode completá-los no aplicativo depois.</h1> </br> <form action='/connect' method='POST'> <div> <input type='input' required name='OwnerName' placeholder='Nome da pessoa monitorada' class='input' tabindex='1'> </input> </div></br> <div> <input type='input' required name='Person1Name' placeholder='Nome do primeiro monitor' class='input' tabindex='1'> </input> <input type='input' name='Person2Name' placeholder='Nome do segundo monitor' class='input' tabindex='4'> </input> </div></br> <div> <input type='email' required name='Person1Email' placeholder='Email do primeiro monitor' class='input' tabindex='2'> </input> <input type='email' name='Person2Email' placeholder='Email do segundo monitor' class='input' tabindex='5'> </input> </div></br> <div> <input type='input' name='Person1Twitter' placeholder='Twitter do primeiro monitor' class='input' tabindex='3'> </input> <input type='input' name='Person2Twitter' placeholder='Twitter do segundo monitor' class='input' tabindex='6'> </input> </div></br> <div> <input type='tel' name='Person1Phone' placeholder='Telefone do primeiro monitor' class='input' tabindex='3'> </input> <input type='tel' name='Person2Phone' placeholder='Telefone do segundo monitor' class='input' tabindex='6'> </input> </div></br> <div> <input type='text' pattern='([0-1]{1}[0-9]{1}|20|21|22|23):[0-5]{1}[0-9]{1}' name='Medicine1' placeholder='Horário de remédio (hh:mm)' class='input' tabindex='7'> </input> <input type='text' pattern='([0-1]{1}[0-9]{1}|20|21|22|23):[0-5]{1}[0-9]{1}' name='Medicine2' placeholder='Horário de remédio (hh:mm)' class='input' tabindex='8'> </input> </div></br> <div> <input type='text' pattern='([0-1]{1}[0-9]{1}|20|21|22|23):[0-5]{1}[0-9]{1}' name='Medicine3' placeholder='Horário de remédio (hh:mm)' class='input' tabindex='9'> </input> <input type='text' pattern='([0-1]{1}[0-9]{1}|20|21|22|23):[0-5]{1}[0-9]{1}' name='Medicine4' placeholder='Horário de remédio (hh:mm)' class='input' tabindex='10'> </input> </div></br> <div> <input type='text' pattern='([0-1]{1}[0-9]{1}|20|21|22|23):[0-5]{1}[0-9]{1}' name='Medicine5' placeholder='Horário de remédio (hh:mm)' class='input' tabindex='3'> </input> <input type='text' pattern='([0-1]{1}[0-9]{1}|20|21|22|23):[0-5]{1}[0-9]{1}' name='Medicine6' placeholder='Horário de remédio (hh:mm)' class='input' tabindex='11'> </input> </div></br> <div> <input type='text' pattern='([0-1]{1}[0-9]{1}|20|21|22|23):[0-5]{1}[0-9]{1}' name='Medicine7' placeholder='Horário de remédio (hh:mm)' class='input' tabindex='12'> </input> <input type='text' pattern='([0-1]{1}[0-9]{1}|20|21|22|23):[0-5]{1}[0-9]{1}' name='Medicine8' placeholder='Horário de remédio (hh:mm)' class='input' tabindex='13'> </input> </div></br> <div> <input type='input' required name='SSID' placeholder='Nome da Wi-Fi' class='input' tabindex='14'> </input> </div></br> <div align='center'> <input type='password' required name='password' placeholder='Senha' class='input' tabindex='15'> </input> </div></br> <div align='center'> <input type='submit' name='SUBMIT' value='Conectar' class='button' tabindex='16'></input> </div></form> </br> <div align='center'> <h1 class='title'>Lista de redes Wi-Fi detectadas: </br> </br> AAAAAA </h1> </div></br> <h1 class='title'>Caso a conexão seja bem sucedida, a rede 'SmartCare' deverá desaparecer e será enviado um e-mail com o código de acesso para ser utilizado no aplicativo. Anote este número!</h1> <div align='center' style='display:none'> <div align='center' id='loader' class='loader'/> </div></body></html>";
const String connect_page = "<!DOCTYPE html><html><head> <title>SmartCare - Configuração</title> <style>.loader{border: 16px solid #f3f3f3; border-top: 16px solid #3498db; border-radius: 50%; width: 120px; height: 120px; animation: spin 2s linear infinite; text-align: center;}@keyframes spin{0%{transform: rotate(0deg);}100%{transform: rotate(360deg);}}.title{font-family: verdana; color: rgb(52, 73, 94); text-align: center; font-size: 100%;}.input{font-family: verdana; box-sizing: border-box; z-index: 21; height: 45px; width: 304px; border: 2px solid rgb(189, 195, 199); background-color: rgb(255, 255, 255); border-radius: 5px; font-size: 14px; color: rgb(52, 73, 94); padding: 0px 6px; transition: border-color 200ms ease;}.button{box-sizing: border-box; z-index: 18; height: 40px; width: 125px; padding: 0px; cursor: inherit; background: none rgb(26, 188, 156); border: none; text-align: center; font-family: verdana; font-size: 14px; color: rgb(255, 255, 255); line-height: 1; border-radius: 5px; transition: box-shadow 200ms ease, background 200ms ease; box-shadow: none;}</style></head><body style='text-align: left; width: 100%'> <h1 class='title' style='font-size:300%;'>SmartCare</h1> <h1 class='title'>A conexão com a rede AAAAAA está sendo realizada. Em caso de sucesso, a rede Wi-Fi SmartCare irá desaparecer e você deverá checar o seu email com o código de acesso do aplicativo.</h1> <h1 class='title'>Obrigado por usar o SmartCare!</h1> </br> <div align='center'> <div align='center' id='loader' class='loader'/> </div></body></html>";
const String success_page = "<!DOCTYPE html><html><head><title>SmartCare - Status</title> <style>.title{font-family:verdana; color: rgb(52, 73, 94); text-align:center; font-size:100%;}</style></head><body style='text-align: left; width: 100%'><h1 class='title' style='font-size:300%;'>SmartCare</h1><h1 class='title' >Seu dispositivo já está online! Para visualizar as informações pelo seu aplicativo e configurar os alertas, use os seguintes dados na configuração do app:</h1> </br> <h1 class='title' >Canal: AAAAAA</h1> </body> </html>";

// Email messages
//const String configuration_html_msg = "<!DOCTYPE html><html><head><style>.title{font-family: verdana; color: rgb(52, 73, 94); text-align: center; font-size: 100%;}</style></head><body style='text-align: left; width: 100%'> <h1 class='title' style='text-align: left; font-size: 150%;'>Olá AAAAAA!</h1> </br> <h1 class='title' style='text-align: left;'>Para finalizar a configuração do seu SmartCare e começar a cuidar de quem ama, anote o seguinte código de acesso ao aplicativo. </h1></br> <h1 class='title' style='font-size: 150%;'>Código: BBBBBB</h1></br></br> <h1 class='title' style='text-align: left;'>Caso ainda não tenha o feito, abra o aplicativo e faça seu cadastro inserindo este código. Pronto, agora é só usar.</br></br> Obrigado por nos escolher para cuidar de quem importa.</br></br></br>SmartCare Devices</h1> <h1 class='title' style='text-align: left;'>smartcaredevices@gmail.com</h1></body></html>";
//const String alert_html_msg = "<!DOCTYPE <html><html><head> <style>.title{font-family: verdana; color: rgb(52, 73, 94); text-align: center; font-size: 100%;}</style></head><body style='text-align: left; width: 100%'> <h1 class='title' style='text-align: left; font-size: 150%;'>Olá AAAAAA,</h1> </br> <h1 class='title' style='text-align: left;'>Nós detectamos um alerta de BBBBBB gerado por CCCCCC</h1></br> </br> <h1 class='title' style='text-align: left;'>Sugerimos entrar em contato com CCCCCC e/ou chamar assistência. Após averiguar a situação, visite o aplicativo para indicar que está tudo bem. Caso Contrário, este alerta será reenviado periodicamente.</br></br> Atenciosamente,</br> SmartCare Devices</h1> <h1 class='title' style='text-align: left;'>smartcaredevices@gmail.com</h1></body></html>";
//const String configuration_text_msg = "Olá AAAAAA!\n\nPara finalizar a configuração do seu SmartCare e começar a cuidar de quem ama, anote o seguinte código de acesso ao aplicativo.\n\nCódigo: BBBBBB\n\n\n\nCaso ainda não tenha o feito, abra o aplicativo e faça seu cadastro inserindo este código. Pronto, agora é só usar.\n\n\nObrigado por nos escolher para cuidar de quem importa.\n\n\nSmartCare Devices\nsmartcaredevices@gmail.com";
//const String alert_text_msg = "Olá AAAAAA,\n\nNós detectamos um alerta de BBBBBB gerado por CCCCCC.\n\nSugerimos entrar em contato com CCCCCC e/ou chamar assistência. Após averiguar a situação, visite o aplicativo para indicar que está tudo bem. Caso Contrário, este alerta será reenviado periodicamente.\n\nAtenciosamente,\nSmartCare Devices\nsmartcaredevices@gmail.com";

const String sms_alert = "ALERTA DE AAAAAA! Entre em contato com BBBBBB e/ou chame assistencia. SmartCare";
const String sms_config = "Para finalizar a configuração do seu SmartCare, anote o codigo de acesso: AAAAAA";

// Global Variables
// Wifi state machine
uint8_t WiFiState = SCAN;

// Radio Communication state
uint8_t RadioState = FIND;

// Power state
uint8_t PowerState = INITIALIZING;

// SSIID After configuration (Will always reconnect until reset)
String permanentSSID;
// Password after configurarion
String pernamentPassword;
// If it is configured succesfully (Will try to reconnect always)
uint8_t isConfigured = 0;

uint8_t nWifiScanned = 0;
String SSIDScanned[32];

// Thingspeak data
String TS_Private_Key = "HQAS6YIOT64BGGWG";
String TS_Channel_Key = "";
String TS_Channel_ID = "";
String TS_Twitter_Key = "U55FTXV3Q7QZ8XN0";

String AlertName = "";
String OwnerName = "";
String Person1Name = "";
String Person2Name = "";
String Person1Email = "";
String Person2Email = "";
String Person1Twitter = "";
String Person2Twitter = "";
String Person1Phone = "";
String Person2Phone = "";
String MedicineList = "0";
String MedicineListOld = "0";

ESP8266WebServer server(80);

uint8_t sendEmail(String action, String value1, String value2, String value3);
uint8_t sendTweet(String ToUserName, String message);
unsigned long webUnixTime (WiFiClient &client);

os_timer_t ledWifiTimer;
os_timer_t ledPowerTimer;
os_timer_t ledRadioTimer;


unsigned long lastCheck = 0;
unsigned long timeNow = 0;
unsigned long lastWatchRead = 0;
unsigned long lastAlarmSent = 0;
unsigned long watchTime = 0;
tmElements_t watchTimeSt;

int lastHeartRate = 60;
int lastBattery = 100;
int lastRadioPower = 100;
int lastTemperature = 25;

int timeSync = 0;
int t_day = 12;
int t_month = 06;
int t_year = 2017;

int t_hour = 00;
int t_minute = 00;
int t_second = 00;
int t_dow = 00;

uint8_t DSTflag = 0;
uint8_t MedicineChangedFlag = 0;

uint8_t alarmCode = 0;
uint8_t alarmCodeChannel = 0;

#define NO_ALARM    0x00
#define FALL        0x01
#define HEARTRATE   0x02
#define EMERGENCY   0x04
#define MEDICINE    0x08
#define NO_COMMS    0x10
#define LOW_BATT    0x20
#define CLEAR_ALARMS  0x40


void ledWiFiHandler(void *pArg)
{
    if (WiFiState == CONFIGURED)
    {
      digitalWrite(LED_WIFI, LOW);
    }
    else
    {
      digitalWrite(LED_WIFI, HIGH);
    }
}

void ledPowerHandler(void *pArg)
{
  if (WiFiState == SCAN || SETUP_SERVER)
  {
    digitalWrite(LED_WIFI, HIGH);
  }
  else if (WiFiState == WAIT_USER || CONNECT)
  {
    digitalWrite(LED_POWER, !digitalRead(LED_POWER));
  }
  else
  {
    digitalWrite(LED_POWER, LOW);
  }
}

void ledRadioHandler(void *pArg)
{
    if (RadioState == FIND)
    {
        digitalWrite(LED_RADIO, !digitalRead(LED_RADIO));
    }
    else if (RadioState == SYNC)
    {
        digitalWrite(LED_RADIO, LOW);
    }
    else
    {
        digitalWrite(LED_RADIO, HIGH);
    }
}

void handleSuccess()
{
    String htmlSSIDs = "";
    String Page = success_page;

    Serial.println("Success page reached.");
    
    Page.replace("AAAAAA", TS_Channel_ID);
    server.send(200, "text/html", Page);
}

void handleRoot()
{
    int i =0;
    String htmlSSIDs = "";
    String Page = index_page;

    Serial.println("Index page reached.");
    
    for (i = 0; i < 32; i++)
    {
        if (SSIDScanned[i].length() > 0)
        {
            htmlSSIDs += "<div>" + SSIDScanned[i] + "</div>";
        }
    }
    Page.replace("AAAAAA", htmlSSIDs);
    server.send(200, "text/html", Page);
}

void handleConnect()
{
    int i = 0;
    uint8_t foundWifi = 0;

    Serial.println("Connect page reached.");
    
    if (server.hasArg("SSID") && server.hasArg("password"))
    {
        Serial.println("Connecting to...");
        Serial.println(server.arg("SSID"));
        Serial.println(server.arg("password"));
    }

    for (i = 0; i < nWifiScanned; i++)
    {
        if (SSIDScanned[i] == server.arg("SSID"))
        {
            permanentSSID = server.arg("SSID");
            pernamentPassword = server.arg("password");
            foundWifi = 1;
            
      			if (server.hasArg("OwnerName"))
      			{
      				OwnerName = server.arg("OwnerName");
              Serial.println("OwnerName: " + OwnerName);
      			}
      			if (server.hasArg("Person1Name"))
      			{
              if (server.arg("Person1Name").length() > 0)
              {
                Person1Name = server.arg("Person1Name");
              }
              else
              {
               Person1Name = " ";
              }
              Serial.println("Person1Name: " + Person1Name);
      			}
      			if (server.hasArg("Person2Name"))
      			{
      				if (server.arg("Person2Name").length() > 0)
              {
                Person2Name = server.arg("Person2Name");
              }
              else
              {
               Person2Name = " ";
              }
      			}
      			if (server.hasArg("Person1Email"))
      			{
      				if (server.arg("Person1Email").length() > 0)
              {
                Person1Email = server.arg("Person1Email");
              }
              else
              {
               Person1Email = " ";
              }
      			}
      			if (server.hasArg("Person2Email"))
      			{
      				if (server.arg("Person2Email").length() > 0)
              {
                Person2Email = server.arg("Person2Email");
              }
              else
              {
               Person2Email = " ";
              }
      			}
      			if (server.hasArg("Person1Twitter"))
      			{
      				if (server.arg("Person1Twitter").indexOf("@") == -1)
              {
                Person1Twitter = "@" + server.arg("Person1Twitter");
                Serial.println("Person1Twitter: " + Person1Twitter);
              }
              else
              {
                Person1Twitter = server.arg("Person1Twitter");
                Serial.println("Person1Twitter: " + Person1Twitter);
              }
      			}
      			if (server.hasArg("Person2Twitter"))
      			{
              if (server.arg("Person2Twitter").indexOf("@") == -1)
              {
                Person2Twitter = "@" + server.arg("Person2Twitter");
                Serial.println("Person2Twitter: " + Person2Twitter);
              }
              else
              {
      				  Person2Twitter = server.arg("Person2Twitter");
                Serial.println("Person2Twitter: " + Person2Twitter);
              }
      			}
            if (server.hasArg("Person1Phone"))
            {
              if (server.arg("Person1Phone").length() > 0)
              {
                Person1Phone = server.arg("Person1Phone");
              }
              else
              {
               Person1Phone = " ";
              }
            }
            if (server.hasArg("Person2Phone"))
            {
              if (server.arg("Person2Phone").length() > 0)
              {
                Person2Phone = server.arg("Person2Phone");
              }
              else
              {
               Person2Phone = " ";
              }
            }
      			MedicineList = "";
      			if (server.hasArg("Medicine1"))
      			{
              if (server.arg("Medicine1").length() > 0)
              {
                MedicineList += server.arg("Medicine1") + ",";
              }
      				else
              {
                MedicineList += "--:--,";
              }
      			}
      			if (server.hasArg("Medicine2"))
      			{
      				if (server.arg("Medicine2").length() > 0)
              {
                MedicineList += server.arg("Medicine2") + ",";
              }
              else
              {
                MedicineList += "--:--,";
              }
            }
      			if (server.hasArg("Medicine3"))
      			{
      				if (server.arg("Medicine3").length() > 0)
              {
                MedicineList += server.arg("Medicine3") + ",";
              }
              else
              {
                MedicineList += "--:--,";
              }
            }
      			if (server.hasArg("Medicine4"))
      			{
      				if (server.arg("Medicine4").length() > 0)
              {
                MedicineList += server.arg("Medicine4") + ",";
              }
              else
              {
                MedicineList += "--:--,";
              }
            }
      			if (server.hasArg("Medicine5"))
      			{
      				if (server.arg("Medicine5").length() > 0)
              {
                MedicineList += server.arg("Medicine5") + ",";
              }
              else
              {
                MedicineList += "--:--,";
              }
            }
      			if (server.hasArg("Medicine6"))
      			{
      				if (server.arg("Medicine6").length() > 0)
              {
                MedicineList += server.arg("Medicine6") + ",";
              }
              else
              {
                MedicineList += "--:--,";
              }
            }
      			if (server.hasArg("Medicine7"))
      			{
      				if (server.arg("Medicine7").length() > 0)
              {
                MedicineList += server.arg("Medicine7") + ",";
              }
              else
              {
                MedicineList += "--:--,";
              }
            }
      			if (server.hasArg("Medicine8"))
      			{
      				if (server.arg("Medicine8").length() > 0)
              {
                MedicineList += server.arg("Medicine8") + ",";
              }
              else
              {
                MedicineList += "--:--";
              }
            }
            Serial.println("MedicineList: " + MedicineList);
            break;
        }
    }

    if (foundWifi == 1)
    {
        WiFiState = CONNECT;
        String Page = connect_page;
        Page.replace("AAAAAA", permanentSSID);
        server.send(200, "text/html", Page);
    }
    else
    {
        handleRoot();
    }
}

void setup()
{
    Serial.begin(115200);
    Serial.println();
    Serial.println("SmartCare Access Point starting...");

    // initialize LED Pins
    pinMode(LED_POWER, OUTPUT);
    pinMode(LED_RADIO, OUTPUT);
    pinMode(LED_WIFI, OUTPUT);
  
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(14, HIGH);

    PowerState = INITIALIZING;
    RadioState = FIND;
    
    os_timer_setfn(&ledWifiTimer, ledWiFiHandler, NULL);
    os_timer_arm(&ledWifiTimer, 500, true);

    os_timer_setfn(&ledPowerTimer, ledPowerHandler, NULL);
    os_timer_arm(&ledPowerTimer, 500, true);

    os_timer_setfn(&ledRadioTimer, ledRadioHandler, NULL);
    os_timer_arm(&ledRadioTimer, 250, true);

    yield();
    // 
	  uint8_t i = 0;
    for (i = 0; i < 32; i++)
    {
        SSIDScanned[i] = "";
    }

    Serial.println("Starting AP Serial...");
    pinMode(AP_RX, INPUT);
    pinMode(AP_TX, OUTPUT);
    SerialAP.begin(9600);
    cmdReadWatchData += 'R';
    cmdReadWatchData += '\r';
    cmdSendDateTime = "D12,06,2017,14,15,00";
    cmdSendDateTime += '\r';
    cmdSendMedicineTimes = "H--:--,--:--,--:--,--:--,--:--,--:--,--:--,--:--";
    cmdSendMedicineTimes += '\r';

    Serial.println("Reading EEPROM...");
    EEPROM.begin(512);

    if (EEPROM.read(EEPROM_CHECK) == EEPROM_VALID_KEY)
    {
        Serial.println("EEPROM is valid");
        Serial.println("State = ");
        WiFiState = EEPROM.read(EEPROM_STATE);
        Serial.println(WiFiState);
        
        char temp[100];
        for (i = 0; i < 100; i++)
        {
            temp[i] = EEPROM.read(EEPROM_SSID+i);
        }
        Serial.println("SSID = ");
        permanentSSID = temp;
        Serial.println();
        Serial.println(permanentSSID);
        for (i = 0; i < 100; i++)
        {
            temp[i] = EEPROM.read(EEPROM_PWD+i);
        }
        pernamentPassword = temp;
        
        TS_Channel_ID = temp;
        Serial.println("Password found");
        uint8_t *ptr = (uint8_t*) &DeviceID;
        *(ptr) =  EEPROM.read(EEPROM_DEV_ID);
        *(ptr+1) =  EEPROM.read(EEPROM_DEV_ID+1);
        *(ptr+2) =  EEPROM.read(EEPROM_DEV_ID+2);
        *(ptr+3) =  EEPROM.read(EEPROM_DEV_ID+3);

        Serial.println("Device ID = ");
        Serial.println(DeviceID);

        if (WiFiState == CONFIGURED)
        {
            Serial.println("Connecting to ");
            Serial.println(permanentSSID);
            
            WiFi.begin(permanentSSID.c_str(), pernamentPassword.c_str());
            
            while (WiFi.status() != WL_CONNECTED)
            {
                yield();
                Serial.print(".");
            }
            WiFiState = CONFIGURED;
            Serial.println("");
            Serial.println("WiFi connected");  
            Serial.println("IP address: ");
            Serial.println(WiFi.localIP());
            
            Udp.begin(localPort);
            setSyncProvider(getNtpTime);

            for (i = 0; i < 100; i++)
            {
                temp[i] = 0;
            }
            for (i = 0; i < 16; i++)
            {
                temp[i] = EEPROM.read(EEPROM_TS_CHANNEL+i);
            }
            TS_Channel_Key = temp;
            for (i = 0; i < 16; i++)
            {
                temp[i] = EEPROM.read(EEPROM_TS_ID+i);
            }
            TS_Channel_ID = temp;

            Serial.println("Channel key = " + TS_Channel_Key);
            Serial.println("Channel ID = " + TS_Channel_ID);
        }
    }
    else
    {
        Serial.println("EEPROM is not valid, loading default values");
        Serial.println("State = 0, no SSID, no password, Device ID 12345678");
        
        EEPROM.write(EEPROM_CHECK, EEPROM_VALID_KEY);
        EEPROM.write(EEPROM_STATE, SCAN);
        for (i = 0; i < 100; i++)
        {
            EEPROM.write(EEPROM_SSID+i, 0);
            EEPROM.write(EEPROM_PWD+i, 0);
        }
        for (i = 0; i < 16; i++)
        {
            EEPROM.write(EEPROM_TS_CHANNEL+i, 0);
            EEPROM.write(EEPROM_TS_ID+i, 0);
        }

        uint8_t *ptr = (uint8_t*) &DeviceID;
        EEPROM.write(EEPROM_DEV_ID, *(ptr));
        EEPROM.write(EEPROM_DEV_ID+1, *(ptr+1));
        EEPROM.write(EEPROM_DEV_ID+2, *(ptr+2));
        EEPROM.write(EEPROM_DEV_ID+3, *(ptr+3));
        
        EEPROM.commit();
    }   
    PowerState = RUNNING;
}

void loop()
{
    int i = 0;
    int temp = 0;
    char temp1, temp2, temp3, temp4;
    if (WiFiState == SCAN)
    {
        Serial.println("State: Scan");
    
        // Set WiFi to station mode and disconnect from an AP if it was previously connected
        WiFi.mode(WIFI_STA);
        WiFi.disconnect();
        yield();
        
        Serial.println("Starting Wi-Fi scanning");
        nWifiScanned = WiFi.scanNetworks();
        if (nWifiScanned == 0)
        {
             Serial.println("No networks found");
        }
        else
        {
            Serial.print(nWifiScanned);
            Serial.println(" networks found");
            for (i = 0; i < nWifiScanned; i++)
            {
                 Serial.println(WiFi.SSID(i));
                 SSIDScanned[i] = WiFi.SSID(i);
            }
        }
        WiFiState = SETUP_SERVER;
    }
    else if(WiFiState == SETUP_SERVER)
    {
        Serial.println("State: Setup HTML Server");
        WiFi.softAP(ssid);
        IPAddress myIP = WiFi.softAPIP();
        Serial.print("AP IP address: ");
        Serial.println(myIP);
        server.on("/", handleRoot);
        server.on("/connect", handleConnect);
        server.begin();
        Serial.println("HTTP server started");
        WiFiState = WAIT_USER;
        Serial.println("State: HTML Server handling");
    }
    else if (WiFiState == WAIT_USER)
    {
        //Serial.println("State: HTML Server handling");
      
        server.handleClient();
    }
    else if (WiFiState == CONNECT)
    {
        server.stop();
        Serial.println("State: Connect");
        Serial.print("Connecting to ");
        Serial.println(permanentSSID);
        
        if (WiFi.status() != WL_CONNECTED)
        {
            WiFi.begin(permanentSSID.c_str(), pernamentPassword.c_str());
        
            while (WiFi.status() != WL_CONNECTED)
            {
                yield();
                Serial.print(".");
            }
            
            Serial.println("");
            Serial.println("WiFi connected");  
            Serial.println("IP address: ");
            Serial.println(WiFi.localIP());
            Serial.println("Saving connection info in EEPROM");
        
            for (i = 0; i < 100; i++)
            {
                EEPROM.write(EEPROM_SSID+i, permanentSSID[i]);
                EEPROM.write(EEPROM_PWD+i, pernamentPassword[i]);
            }
            EEPROM.commit();
        }
       
        if (client.connect(host.c_str(), 80))
        {
            String jsonReply;
            String url;
            String medicineListTemp = MedicineList;
            //medicineListTemp.replace(",", "%%2C");
            if (TS_Channel_Key == "" || TS_Channel_ID == "")
            {
                url = "/channels.json?api_key=" + TS_Private_Key + 
                "&description=" + OwnerName + 
                "&field1=Nível de Bateria" + 
                "&field2=Sinal do Relógio" + 
                "&field3=Temperatura Ambiente" + 
                "&field4=Batimentos" +
                "&metadata=" + Person1Name + "," + Person2Name + "," + 
				                Person1Email + "," + Person2Email + "," + 
                                Person1Twitter + "," + Person2Twitter + "," + 
                                Person1Phone + "," + Person2Phone + "," +
								"0," + medicineListTemp + ",0" +
                "&name=SmartCare Device " + String(DeviceID);

                Serial.println(url);
                
                client.print(String("POST ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Connection: Keep-Alive\r\n\r\n");

                while (client.connected())
                {
                    yield();
                    String line = client.readStringUntil('\n');
                    Serial.println(line);
                    if (line.indexOf("{\"id\":") != -1)
                    {
                        jsonReply = line;
                        break;
                    }
                }

                Serial.println(jsonReply);
                
                int start_idx = jsonReply.indexOf("{\"id\":");
                int end_idx = jsonReply.indexOf(",\"name\":");
                TS_Channel_ID = jsonReply.substring(start_idx+6, end_idx);
                
                start_idx = jsonReply.indexOf("{\"api_key\":\"");
                end_idx = jsonReply.indexOf("\",\"write_flag");
                TS_Channel_Key = jsonReply.substring(start_idx+12, end_idx);
                
                Serial.println("Channel ID" + TS_Channel_ID);
                Serial.println("Channel KEY" + TS_Channel_Key);
                for (i = 0; i < 16; i++)
                {
                    EEPROM.write(EEPROM_TS_ID+i, TS_Channel_ID[i]);
                    EEPROM.write(EEPROM_TS_CHANNEL+i, TS_Channel_Key[i]);
                }
								
				        Serial.println("Checking channel");
                url = "/channels/" + TS_Channel_ID + ".json?api_key=" + TS_Channel_Key;
                
                client.print(String("POST ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Connection: Keep-Alive\r\n\r\n");

                while (client.connected())
                {
                    yield();
                    String line = client.readStringUntil('\n');
                    Serial.println(line);
                    if (line.indexOf("{\"id\":") != -1)
                    {
                        jsonReply = line;
                        break;
                    }
                }

                Serial.println(jsonReply);

                if (jsonReply.indexOf("{\"id\":" + TS_Channel_ID) != -1)
                {
                    if (sendEmail("configuration_done", Person1Email, Person1Name, TS_Channel_ID))
                    {
                      WiFiState = CONFIGURED;
                      MedicineChangedFlag = 1;
                      EEPROM.write(EEPROM_STATE, CONFIGURED);
                      EEPROM.commit();
                      Serial.println(Person2Email);
                      if (Person2Email != "" && Person2Email != " ")
                      {
                        sendEmail("configuration_done", Person2Email, Person2Name, TS_Channel_ID);
                      }
                      if (Person1Phone != "" && Person1Phone != " ")
                      {
                        String fullnumber = "%2B" + Person1Phone;
                        String message = sms_config;
                        message.replace("AAAAAA", TS_Channel_ID);
                        sendSMS(fullnumber, message);
                      }
                      if (Person2Phone != "" && Person2Phone != " ")
                      {
                        String fullnumber = "%2B" + Person2Phone;
                        String message = sms_config;
                        message.replace("AAAAAA", TS_Channel_ID);
                        sendSMS(fullnumber, message);
                      }
                    }
                    else
                    {// email error
                      WiFiState = SCAN;
                
                      EEPROM.write(EEPROM_STATE, CONNECT);
                      EEPROM.commit();
                    }

                    if (Person1Twitter != "@")
                    {
                      sendTweet(Person1Twitter, "Seu SmartCare está quase configurado! Confira seu e-mail.");
                    }
                    if (Person2Twitter != "@")
                    {
                      sendTweet(Person2Twitter, "Seu SmartCare está quase configurado! Confira seu e-mail.");
                    }
                }
            }
            else
            {
                Serial.println("Checking channel");
                url = "/channels/" + TS_Channel_ID + ".json?api_key=" + TS_Channel_Key;
                
                client.print(String("POST ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Connection: Keep-Alive\r\n\r\n");

                while (client.connected())
                {
                    yield();
                    String line = client.readStringUntil('\n');
                    Serial.println(line);
                    if (line.indexOf("{\"id\":") != -1)
                    {
                        jsonReply = line;
                        break;
                    }
                }

                Serial.println(jsonReply);

                if (jsonReply.indexOf("{\"id\":" + TS_Channel_ID) == -1)
                {
                    WiFiState = SCAN;
                
                    EEPROM.write(EEPROM_STATE, SCAN);
                    EEPROM.commit();
                }
                else
                {
                    WiFiState = CONFIGURED;
                
                    EEPROM.write(EEPROM_STATE, CONFIGURED);
                    EEPROM.commit();
                }                
            }
        }
        else
        {
            Serial.println("connection failed");
        }
    }
    else if (WiFiState == CONFIGURED)
    {
        server.stop();
        WiFi.mode(WIFI_STA);
        WiFi.softAPdisconnect(false);
        WiFi.enableAP(false);
        
        Serial.println("CONFIGURADO");// handle device and internet connections

        timeNow = now();
        Serial.println(timeNow);
        Serial.println(lastCheck);

        t_day = day();
        t_month = month();
        t_year = year();
        t_hour = hour();
        t_minute = minute();
        t_second = second();
        
        Serial.println(hour());
        Serial.println(minute());
        Serial.println(second());
        Serial.println(day());
        Serial.println(month());
        Serial.println(year()); 
        
        if ((timeNow - lastCheck) > 60)
        {
          getChannelInfo();

          SerialAP.print(cmdReadWatchData);
  
          delay(200);
          
          while (SerialAP.available() > 0 )
          {
            recvTemp = SerialAP.read();
            cmdBuffer += recvTemp;
            if (recvTemp == 0x0D)
            {
              if (cmdBuffer[0] == 'R')
              {
                Serial.println("Resposta R recebida: " + cmdBuffer);
                RadioState = SYNC;
                
                lastBattery = (cmdBuffer[1]-0x30)*100 + (cmdBuffer[2]-0x30)*10 + (cmdBuffer[3]-0x30);
                lastRadioPower = (cmdBuffer[5]-0x30)*100 + (cmdBuffer[6]-0x30)*10 + (cmdBuffer[7]-0x30);
                lastTemperature = (cmdBuffer[9]-0x30)*100 + (cmdBuffer[10]-0x30)*10 + (cmdBuffer[11]-0x30);
                lastHeartRate = (cmdBuffer[13]-0x30)*100 + (cmdBuffer[14]-0x30)*10 + (cmdBuffer[15]-0x30);
                alarmCode = (cmdBuffer[17]-0x30)*10 + (cmdBuffer[18]-0x30);

                // read date time
                watchTimeSt.Day = (cmdBuffer[20]-0x30)*10 + (cmdBuffer[21]-0x30);
                watchTimeSt.Month = (cmdBuffer[23]-0x30)*10 + (cmdBuffer[24]-0x30);
                watchTimeSt.Year = ((cmdBuffer[26]-0x30)*1000 + (cmdBuffer[27]-0x30)*100 + (cmdBuffer[28]-0x30)*10 + (cmdBuffer[29]-0x30)) - 1970;
                watchTimeSt.Hour = (cmdBuffer[31]-0x30)*10 + (cmdBuffer[32]-0x30);
                watchTimeSt.Minute = (cmdBuffer[34]-0x30)*10 + (cmdBuffer[35]-0x30);
                watchTimeSt.Second = (cmdBuffer[37]-0x30)*10 + (cmdBuffer[38]-0x30);
                watchTimeSt.Wday = (cmdBuffer[40]-0x30)*10 + (cmdBuffer[41]-0x30);

                lastWatchRead = timeNow;
                watchTime = makeTime(watchTimeSt);
                Serial.print("timenow: ");
                Serial.println(timeNow);
                Serial.print("watchnow: ");
                Serial.println(watchTime);
                
                // if difference is more than 5 minutes
                if (((watchTime - timeNow) > 300 || (watchTime - timeNow) < -300) && timeSync == 1)
                {
                  t_day = day();
                  t_month = month();
                  t_year = year();
                  t_hour = hour();
                  t_minute = minute();
                  t_second = second();
                  t_dow = weekday();
                  
                  cmdSendDateTime = "D";
                
                  temp = t_day;
                  
                  temp1 = (temp % 10) + 0x30;
                  temp /= 10;
                  temp2 = (temp % 10) + 0x30;
  
                  cmdSendDateTime += temp2;
                  cmdSendDateTime += temp1;
                  cmdSendDateTime += ",";
  
                  temp = t_month;
                  
                  temp1 = (temp % 10) + 0x30;
                  temp /= 10;
                  temp2 = (temp % 10) + 0x30;
  
                  cmdSendDateTime += temp2;
                  cmdSendDateTime += temp1;
                  cmdSendDateTime += ",";
  
                  temp = t_year;
  
                  temp1 = (((temp % 1000) % 100) % 10) + 0x30;
                  temp /= 10;
                  temp2 = ((temp % 100) % 10) + 0x30;
                  temp /= 10;
                  temp3 = (temp % 10) + 0x30;
                  temp /= 10;
  
                  temp4 = temp + 0x30;
  
                  cmdSendDateTime += temp4;
                  cmdSendDateTime += temp3;
                  cmdSendDateTime += temp2;
                  cmdSendDateTime += temp1;
                  cmdSendDateTime += ",";
  
                  temp = t_hour;
                  
                  temp1 = (temp % 10) + 0x30;
                  temp /= 10;
                  temp2 = (temp % 10) + 0x30;
  
                  cmdSendDateTime += temp2;
                  cmdSendDateTime += temp1;
                  cmdSendDateTime += ",";
  
                  temp = t_minute;
                  
                  temp1 = (temp % 10) + 0x30;
                  temp /= 10;
                  temp2 = (temp % 10) + 0x30;
  
                  cmdSendDateTime += temp2;
                  cmdSendDateTime += temp1;
                  cmdSendDateTime += ",";
  
                  temp = t_second;
                  
                  temp1 = (temp % 10) + 0x30;
                  temp /= 10;
                  temp2 = (temp % 10) + 0x30;
  
                  cmdSendDateTime += temp2;
                  cmdSendDateTime += temp1;
                  cmdSendDateTime += ",";

                  temp = t_dow;
                  
                  temp1 = (temp % 10) + 0x30;
                  temp /= 10;
                  temp2 = (temp % 10) + 0x30;
  
                  cmdSendDateTime += temp2;
                  cmdSendDateTime += temp1;
                  cmdSendDateTime += ",";
  
                  cmdSendDateTime[23] = 0x0D;
  
                  Serial.println(cmdSendDateTime);
                  SerialAP.print(cmdSendDateTime);
                }

                delay(200);
                
                // check if new medicine was programmed
                if (MedicineChangedFlag == 1)
                {
                  cmdSendMedicineTimes = "H";
                  for (i = i; i < 8; i++)
                  {
                      cmdSendMedicineTimes += getValue(MedicineList, ',', i) + ",";
                  } 
  
                  cmdSendMedicineTimes[48] = '\r';
  
                  SerialAP.print(cmdSendMedicineTimes);
                  Serial.print(cmdSendMedicineTimes);
                  MedicineChangedFlag = 0;
                  delay(200);
                }
              }
              else if (cmdBuffer[0] == 'E')
              {
                Serial.println("Resposta E recebida: " + cmdBuffer);
              }
              
              cmdBuffer = "";
            }
          }
          
          if (lastWatchRead != 0 && (timeNow - lastWatchRead) > 300)
          {
            alarmCode |= NO_COMMS;
            RadioState = OFF;
          }
          
          if (alarmCodeChannel == CLEAR_ALARMS)
          {
            alarmCode = NO_ALARM;
            // envia sinal para limpar alarm no relogio
            cmdSendMedicineTimes = "";
            cmdSendMedicineTimes += "C";
            cmdSendMedicineTimes[1] = 0x0D;
            SerialAP.print(cmdSendMedicineTimes);
          }
          if (client.connect(host.c_str(), 80))
          {
            String url = "/channels/" + TS_Channel_ID + "?api_key=" + TS_Private_Key + 
              "&metadata=" + Person1Name + "," + Person2Name + "," + 
                      Person1Email + "," + Person2Email + "," + 
                              Person1Twitter + "," + Person2Twitter + "," + 
                              Person1Phone + "," + Person2Phone + "," +
              String(alarmCode) + "," + MedicineList + ",0";
  
              Serial.println(url);
              
              client.print(String("PUT ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: Keep-Alive\r\n\r\n");
  
              while (client.connected())
              {
                  yield();
                  String line = client.readStringUntil('\n');
                  Serial.println(line);
                  if (line.indexOf("{\"id\":") != -1)
                  {
                    
                      break;
                  }
              }
          }

          // send alarm every 5 minutes
          if ((alarmCode != NO_ALARM)&& ((timeNow - lastAlarmSent) > 300))
          {
            lastAlarmSent = timeNow;
            if (alarmCode & NO_COMMS)
            {
              AlertName = "dispositivo offline";
            }
            else if (alarmCode & EMERGENCY)
            {
              AlertName = "botao de panico";
            }
            else if (alarmCode & FALL)
            {
              AlertName = "queda ou movimento brusco";
            }
            else if (alarmCode & HEARTRATE)
            {
              AlertName = "alteracao de batimentos cardiacos";
            }
            else if (alarmCode & MEDICINE)
            {
              AlertName = "esquecimento de remedio";
            }
            else if (alarmCode & LOW_BATT)
            {
              AlertName = "dispositivo com bateria fraca";
            }
            
            if (Person1Email != "" && Person1Email != " ")
              {
                sendEmail("emergency", Person1Email, AlertName, OwnerName);
              }
              if (Person2Email != "" && Person2Email != " ")
              {
                sendEmail("emergency", Person2Email, AlertName, OwnerName);
              }
              if (Person1Phone != "" && Person1Phone != " ")
              {
                String fullnumber = "%2B" + Person1Phone;
                String message = sms_alert;
                message.replace("AAAAAA", AlertName);
                message.replace("BBBBBB", OwnerName);
                sendSMS(fullnumber, message);
              }
              if (Person2Phone != "" && Person2Phone != " ")
              {
                String fullnumber = "%2B" + Person2Phone;
                String message = sms_alert;
                message.replace("AAAAAA", AlertName);
                message.replace("BBBBBB", OwnerName);
                sendSMS(fullnumber, message);
              }
              if (Person1Twitter != "@")
              {
                String message = sms_alert;
                message.replace("AAAAAA", AlertName);
                message.replace("BBBBBB", OwnerName);
                sendTweet(Person1Twitter, message);
              }
              if (Person2Twitter != "@")
              {
                String message = sms_alert;
                message.replace("AAAAAA", AlertName);
                message.replace("BBBBBB", OwnerName);
                sendTweet(Person2Twitter, message);
              }
          }
          else
          {
            //lastAlarmSent = timeNow;
          }

          if (client.connect(host.c_str(), 80))
          {
            String url = "/update?api_key=" + TS_Channel_Key + 
            "&field1=" + String(lastBattery) +
            "&field2=" + String(lastRadioPower) +
            "&field3=" + String(lastTemperature) +
            "&field4=" + String(lastHeartRate);
            Serial.println(url);
          
            client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: Keep-Alive\r\n\r\n");

            while (client.connected())
            {
                yield();
                String line = client.readStringUntil('\n');
                Serial.println(line);
                if (line.indexOf("{\"id\":") != -1)
                {
                    break;
                }
            }
          }
          lastCheck = timeNow;
        }

        delay(10000);
    }
    else
    {
        WiFiState = SCAN;
    }
    yield();
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

uint8_t getChannelInfo()
{
  Serial.println("Getting Channel Informawtion");
  
  if (!client.connect(host.c_str(), 80))
  {
        Serial.println("connection failed");
    return 0;
  }
  String url = "/channels/" + TS_Channel_ID + ".json?api_key=" + TS_Private_Key;
                
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
     "Host: " + host + "\r\n" +
     "Connection: Keep-Alive\r\n\r\n");

  while (client.connected())
  {
      yield();
      String line = client.readStringUntil('\n');
      String line2 = line;
      Serial.println(line);
      
      if (line.indexOf("{\"id\":") != -1)
      {
        line = line.substring(11+line.indexOf("metadata"),line.indexOf(",\"license_id")-1);
        Person1Name = getValue(line, ',', 0);
        Person2Name = getValue(line, ',', 1);
        Person1Email = getValue(line, ',', 2);
        Person2Email = getValue(line, ',', 3);
        Person1Twitter = getValue(line, ',', 4);
        Person2Twitter = getValue(line, ',', 5);
        Person1Phone = getValue(line, ',', 6);
        Person2Phone = getValue(line, ',', 7);
        Serial.println(Person1Name);
        Serial.println(Person2Name);
        Serial.println(Person1Email);
        Serial.println(Person2Email);
        Serial.println(Person1Twitter);
        Serial.println(Person2Twitter);
        Serial.println(Person1Phone);
        Serial.println(Person2Phone);
        alarmCodeChannel = (uint8_t) atoi(getValue(line, ',', 8).c_str());
        MedicineListOld = MedicineList;
        MedicineList = "";
        MedicineList += getValue(line, ',', 9);
        MedicineList += "," + getValue(line, ',', 10);
        MedicineList += "," + getValue(line, ',', 11);
        MedicineList += "," + getValue(line, ',', 12);
        MedicineList += "," + getValue(line, ',', 13);
        MedicineList += "," + getValue(line, ',', 14);
        MedicineList += "," + getValue(line, ',', 15);
        MedicineList += "," + getValue(line, ',', 16);
        if (MedicineList.equals(MedicineListOld) == false)
        {
          MedicineChangedFlag = 1;
        }
        
        DSTflag = (uint8_t) atoi(getValue(line, ',', 17).c_str());
        Serial.println(DSTflag);

        OwnerName = line2.substring(14+line2.indexOf("description"),line2.indexOf("latitude")-3);
        return 1;
      }
  }
  return 0;
}
uint8_t sendEmail(String action, String value1, String value2, String value3)
{
	uint8_t returnCode = 0;

  if (!client.connect(IFTTThost, 80))
  {
    Serial.println("connection failed");
    return 0;
  }

  String url = "/trigger/" + action + "/with/key/"; //configuration_done
  url += IFTTTapiKey;
  String params = "value1=" + value1 + "&value2=" + value2 + "&value3=" + value3;
  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + IFTTThost + "\r\n" + 
               "Content-Type: application/x-www-form-urlencoded\r\n" + 
               "Content-Length: " + String(params.length()) + "\r\n\r\n" +
               params + "\r\n");   
               
  while (client.connected())
  {
      yield();
      String line = client.readStringUntil('\n');
      Serial.println(line);
      if (line.indexOf(action) != -1)
      {
        returnCode = 1;
      }
  }
	return returnCode;
}

uint8_t sendTweet(String ToUserName, String message)
{
  uint8_t returnCode = 0;

  if (!client.connect(IFTTThost, 80))
  {
    Serial.println("connection failed");
    return 0;
  }

  String url = "/trigger/send_tweet/with/key/"; //configuration_done
  url += IFTTTapiKey;
  String params = "value1=" + ToUserName + "&value2=" + message;
  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + IFTTThost + "\r\n" + 
               "Content-Type: application/x-www-form-urlencoded\r\n" + 
               "Content-Length: " + String(params.length()) + "\r\n\r\n" +
               params + "\r\n");   
               
  while (client.connected())
  {
      yield();
      String line = client.readStringUntil('\n');
      Serial.println(line);
      if (line.indexOf("fired") != -1)
      {
        returnCode = 1;
      }
  }
  return returnCode;

}

uint8_t sendSMS(String number, String message)
{
  uint8_t returnCode = 0;

  if (!client.connect(IFTTThost, 80))
  {
    Serial.println("connection failed");
    return 0;
  }

  String url = "/trigger/send_sms/with/key/"; //configuration_done
  url += IFTTTapiKey;
  String params = "value1=" + number + "&value2=" + message;
  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + IFTTThost + "\r\n" + 
               "Content-Type: application/x-www-form-urlencoded\r\n" + 
               "Content-Length: " + String(params.length()) + "\r\n\r\n" +
               params + "\r\n");   
               
  while (client.connected())
  {
      yield();
      String line = client.readStringUntil('\n');
      Serial.println(line);
      if (line.indexOf("fired") != -1)
      {
        returnCode = 1;
      }
  }
  return returnCode;
}

time_t getNtpTime()
{
  IPAddress ntpServerIP; // NTP server's ip address

  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  // get a random server from the pool
  WiFi.hostByName(ntpServerName, ntpServerIP);
  Serial.print(ntpServerName);
  Serial.print(": ");
  Serial.println(ntpServerIP);
  sendNTPpacket(ntpServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Receive NTP Response");
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      timeSync = 1;
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
