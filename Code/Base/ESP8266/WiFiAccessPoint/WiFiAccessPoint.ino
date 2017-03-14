#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
extern "C" {
#include "user_interface.h"
}
// Device ID
uint32_t DeviceID = 12345678;
String host = "api.thingspeak.com";
WiFiClient client;
StaticJsonBuffer<300> jsonBuffer;

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
#define EEPROM_TS_ID 226

#define EEPROM_VALID_KEY 110

#define LED_POWER 12
#define LED_RADIO 13
#define LED_WIFI 14
#define SW_RESET 11
 
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

ESP8266WebServer server(80);

uint8_t sendEmail(String action, String value1, String value2, String value3);
uint8_t sendTweet(String ToUserName, String message);
unsigned long webUnixTime (WiFiClient &client);

os_timer_t ledWifiTimer;
os_timer_t ledPowerTimer;
os_timer_t ledRadioTimer;

void ledWiFiHandler(void *pArg)
{
    if (WiFiState == SCAN || WiFiState == SETUP_SERVER || WiFiState == CONFIGURED)
    {
      digitalWrite(LED_WIFI, LOW);
    }
    else
    {
      digitalWrite(LED_WIFI, !digitalRead(LED_WIFI));
    }
}

void ledPowerHandler(void *pArg)
{
    if (PowerState == INITIALIZING)
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
    
    Page.replace("AAAAAA", TS_Channel_ID);
    server.send(200, "text/html", Page);
}

void handleRoot()
{
    int i =0;
    String htmlSSIDs = "";
    String Page = index_page;
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
    
    if (server.hasArg("SSID") && server.hasArg("password"))
    {
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
      			}
      			if (server.hasArg("Person1Name"))
      			{
      				Person1Name = server.arg("Person1Name");
      			}
      			if (server.hasArg("Person2Name"))
      			{
      				Person2Name = server.arg("Person2Name");
      			}
      			if (server.hasArg("Person1Email"))
      			{
      				Person1Email = server.arg("Person1Email");
      			}
      			if (server.hasArg("Person2Email"))
      			{
      				Person2Email = server.arg("Person2Email");
      			}
      			if (server.hasArg("Person1Twitter"))
      			{
      				if (server.arg("Person1Twitter").indexOf("@") == -1)
              {
                Person1Twitter = "@" + server.arg("Person1Twitter");
              }
              else
              {
                Person1Twitter = server.arg("Person1Twitter");
              }
      			}
      			if (server.hasArg("Person2Twitter"))
      			{
              if (server.arg("Person2Twitter").indexOf("@") == -1)
              {
                Person2Twitter = "@" + server.arg("Person2Twitter");
              }
              else
              {
      				  Person2Twitter = server.arg("Person2Twitter");
              }
      			}
            if (server.hasArg("Person1Phone"))
            {
              Person1Phone = server.arg("Person1Phone");
            }
            if (server.hasArg("Person2Phone"))
            {
              Person2Phone = server.arg("Person2Phone");
            }
      			MedicineList = "0";
      			if (server.hasArg("Medicine1"))
      			{
      				MedicineList += server.arg("Medicine1") + ",";
      			}
      			if (server.hasArg("Medicine2"))
      			{
      				MedicineList += server.arg("Medicine2") + ",";
      			}
      			if (server.hasArg("Medicine3"))
      			{
      				MedicineList += server.arg("Medicine3") + ",";
      			}
      			if (server.hasArg("Medicine4"))
      			{
      				MedicineList += server.arg("Medicine4") + ",";
      			}
      			if (server.hasArg("Medicine5"))
      			{
      				MedicineList += server.arg("Medicine5") + ",";
      			}
      			if (server.hasArg("Medicine6"))
      			{
      				MedicineList += server.arg("Medicine6") + ",";
      			}
      			if (server.hasArg("Medicine7"))
      			{
      				MedicineList += server.arg("Medicine7") + ",";
      			}
      			if (server.hasArg("Medicine8"))
      			{
      				MedicineList += server.arg("Medicine8") + ",";
      			}
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
    // initialize LED Pins
    pinMode(LED_POWER, OUTPUT);
    pinMode(LED_RADIO, OUTPUT);
    pinMode(LED_WIFI, OUTPUT);
  
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(14, HIGH);

    PowerState = INITIALIZING;
    RadioState = OFF;
    
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
    Serial.begin(115200);
    Serial.println();
    Serial.println("SmartCare Access Point starting...");
    
    EEPROM.begin(512);

    if (EEPROM.read(EEPROM_CHECK) == EEPROM_VALID_KEY)
    {
        Serial.println("EEPROM is valid");
        Serial.println("State = ");
        WiFiState = EEPROM.read(EEPROM_STATE);
        Serial.print(WiFiState);
        
        char temp[100];
        for (i = 0; i < 100; i++)
        {
            temp[i] = EEPROM.read(EEPROM_SSID+i);
        }
        Serial.print("SSID = ");
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

        Serial.print("Device ID = ");
        Serial.println(DeviceID);

        if (WiFiState == CONFIGURED)
        {
            Serial.print("Connecting to ");
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
        Serial.println("State = 0, no SSID, no password, Device ID 0x12345678");
        
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
    if (WiFiState == SCAN)
    {
        Serial.println("Scanning Wi-Fi Networks available");
    
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
        Serial.print("Configuring access point...");
        WiFi.softAP(ssid);
        IPAddress myIP = WiFi.softAPIP();
        Serial.print("AP IP address: ");
        Serial.println(myIP);
        server.on("/", handleRoot);
        server.on("/connect", handleConnect);
        server.begin();
        Serial.println("HTTP server started");
        WiFiState = WAIT_USER;
    }
    else if (WiFiState == WAIT_USER)
    {
        server.handleClient();
    }
    else if (WiFiState == CONNECT)
    {
        server.stop();
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
            if (TS_Channel_Key == "" || TS_Channel_ID == "")
            {
                url = "/channels.json?api_key=" + TS_Private_Key + 
                "&description=" + OwnerName + 
                "&field1=Nível de Bateria" + 
                "&field2=Sinal do Relógio" + 
                "&field3=Temperatura Ambiente" + 
                "&field4=Batimentos"
                "&metadata=" + Person1Name + "," + Person2Name + ";" + 
				                Person1Email + "," + Person2Email + ";" + 
                                Person1Twitter + "," + Person2Twitter + ";" + 
                                Person1Phone + "," + Person2Phone + ";" +
								";0;" + MedicineList + 
                "&name=SmartCare Device " + String(DeviceID);
                
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
                
                Serial.println(TS_Channel_ID);
                Serial.println(TS_Channel_Key);
                for (i = 0; i < 16; i++)
                {
                    EEPROM.write(EEPROM_TS_CHANNEL+i, TS_Channel_ID[i]);
                    EEPROM.write(EEPROM_TS_ID+i, TS_Channel_Key[i]);
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
                
                      EEPROM.write(EEPROM_STATE, CONFIGURED);
                      EEPROM.commit();
                      Serial.println(Person2Email);
                      if (Person2Email != "")
                      {
                        sendEmail("configuration_done", Person2Email, Person2Name, TS_Channel_ID);
                      }
                      if (Person1Phone != "")
                      {
                        String fullnumber = "%2B" + Person1Phone;
                        String message = sms_config;
                        message.replace("AAAAAA", TS_Channel_ID);
                        sendSMS(fullnumber, message);
                      }
                      if (Person2Phone != "")
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

                    if (Person1Twitter != "")
                    {
                      sendTweet(Person1Twitter, "Seu SmartCare está quase configurado! Confira seu e-mail.");
                    }
                    if (Person2Twitter != "")
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
        Serial.println("CONFIGURADO");// handle device and internet connections

        Serial.println(webUnixTime(client));
        
        // read time info
        // read channel, update info
        // send updated info to watch
        // check access point status
        // 
//                      if (Person1Email != "")
//                      {
//                        sendEmail("emergency", Person1Email, AlertName, OwnerName);
//                      }
//                      if (Person2Email != "")
//                      {
//                        sendEmail("emergency", Person2Email, AlertName, OwnerName);
//                      }
//                      if (Person1Phone != "")
//                      {
//                        String fullnumber = "%2B" + Person1Phone;
//                        String message = sms_alert;
//                        message.replace("AAAAAA", AlertName);
//                        message.replace("BBBBBB", OwnerName);
//                        sendSMS(fullnumber, message);
//                      }
//                      if (Person2Phone != "")
//                      {
//                        String fullnumber = "%2B" + Person2Phone;
//                        String message = sms_alert;
//                        message.replace("AAAAAA", AlertName);
//                        message.replace("BBBBBB", OwnerName);
//                        sendSMS(fullnumber, message);
//                      }
			      //sendEmail("emergency", Person1Email, "QUEDA", "NOME DO VEIO");
            delay(500);
    }
    else
    {
        WiFiState = SCAN;
    }
    yield();
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
    Serial.println("Sending Tweet");

    if (client.connect(host.c_str(), 80))
    {
        String url = "/apps/thingtweet/1/statuses/update?api_key=" + TS_Twitter_Key + "&status=" + 
        ToUserName + " " + message;
        
        client.print(String("POST ") + url + " HTTP/1.1\r\n" +
           "Host: " + host + "\r\n" +
           "Connection: Keep-Alive\r\n\r\n");
    
        while (client.connected())
        {
            yield();
            String line = client.readStringUntil('\n');
            Serial.println(line);
            if (line.indexOf("1") != -1)
            {
              returnCode = 1;
            }
        }
    }
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


/*
 * © Francesco Potortì 2013 - GPLv3
 *
 * Send an HTTP packet and wait for the response, return the Unix time
 */

unsigned long webUnixTime (WiFiClient &client)
{
  unsigned long time = 0;

  // Just choose any reasonably busy web server, the load is really low
  if (client.connect("g.cn", 80))
    {
      // Make an HTTP 1.1 request which is missing a Host: header
      // compliant servers are required to answer with an error that includes
      // a Date: header.
      client.print(F("GET / HTTP/1.1 \r\n\r\n"));

      char buf[5];      // temporary buffer for characters
      client.setTimeout(5000);
      if (client.find((char *)"\r\nDate: ") // look for Date: header
    && client.readBytes(buf, 5) == 5) // discard
  {
    unsigned day = client.parseInt();    // day
    client.readBytes(buf, 1);    // discard
    client.readBytes(buf, 3);    // month
    int year = client.parseInt();    // year
    byte hour = client.parseInt();   // hour
    byte minute = client.parseInt(); // minute
    byte second = client.parseInt(); // second

    int daysInPrevMonths;
    switch (buf[0])
      {
      case 'F': daysInPrevMonths =  31; break; // Feb
      case 'S': daysInPrevMonths = 243; break; // Sep
      case 'O': daysInPrevMonths = 273; break; // Oct
      case 'N': daysInPrevMonths = 304; break; // Nov
      case 'D': daysInPrevMonths = 334; break; // Dec
      default:
        if (buf[0] == 'J' && buf[1] == 'a')
    daysInPrevMonths = 0;   // Jan
        else if (buf[0] == 'A' && buf[1] == 'p')
    daysInPrevMonths = 90;    // Apr
        else switch (buf[2])
         {
         case 'r': daysInPrevMonths =  59; break; // Mar
         case 'y': daysInPrevMonths = 120; break; // May
         case 'n': daysInPrevMonths = 151; break; // Jun
         case 'l': daysInPrevMonths = 181; break; // Jul
         default: // add a default label here to avoid compiler warning
         case 'g': daysInPrevMonths = 212; break; // Aug
         }
      }

    // This code will not work after February 2100
    // because it does not account for 2100 not being a leap year and because
    // we use the day variable as accumulator, which would overflow in 2149
    day += (year - 1970) * 365; // days from 1970 to the whole past year
    day += (year - 1969) >> 2;  // plus one day per leap year 
    day += daysInPrevMonths;  // plus days for previous months this year
    if (daysInPrevMonths >= 59  // if we are past February
        && ((year & 3) == 0)) // and this is a leap year
      day += 1;     // add one day
    // Remove today, add hours, minutes and seconds this month
    time = (((day-1ul) * 24 + hour) * 60 + minute) * 60 + second;
  }
    }
  yield();
  client.flush();
  client.stop();
  time = time - 10800;// (GMT-3)
  return time;
}

