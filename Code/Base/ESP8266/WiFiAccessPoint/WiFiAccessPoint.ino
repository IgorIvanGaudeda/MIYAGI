#include <Twitter.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

// Device ID
uint32_t DeviceID = 12345678;
String host = "api.thingspeak.com";
WiFiClient client;
StaticJsonBuffer<300> jsonBuffer;

// AccessPoint possible states
enum AP_STATES {SCAN, SETUP_SERVER, WAIT_USER, CONNECT, CONFIGURED} AP_STATES;

// Twitter client
Twitter twitter("829830887579725824-ip5kNe3Ci4AoUBi17lfmiMjvL6mbXjX");

// EEPROM Addresses 
#define EEPROM_CHECK 0
#define EEPROM_STATE 1
#define EEPROM_DEV_ID 2
#define EEPROM_SSID 10
#define EEPROM_PWD 110
#define EEPROM_TS_CHANNEL 220
#define EEPROM_TS_ID 226

#define EEPROM_VALID_KEY 212
 

// Wi-Fi Settings
const char *ssid = "SmartCare Wi-Fi";

// Pages
// Index page
const String index_page =  "<!DOCTYPE html><html><head><title>SmartCare - Configuração</title> <style>.loader{border: 16px solid #f3f3f3; border-top: 16px solid #3498db; border-radius: 50%; width: 120px; height: 120px; animation: spin 2s linear infinite; text-align:center;}@keyframes spin{0%{transform: rotate(0deg);}100%{transform: rotate(360deg);}}.title{font-family:verdana; color: rgb(52, 73, 94); text-align:center; font-size:100%;}.input{font-family:verdana; box-sizing: border-box; z-index: 21; height: 45px; width: 304px; border: 2px solid rgb(189, 195, 199); background-color: rgb(255, 255, 255); border-radius: 5px; font-size: 14px; color: rgb(52, 73, 94); padding: 0px 6px; transition: border-color 200ms ease;}.button{box-sizing: border-box; z-index: 18; height: 40px; width: 125px; padding: 0px; cursor: inherit; background: none rgb(26, 188, 156); border: none; text-align: center; font-family: verdana; font-size: 14px; color: rgb(255, 255, 255); line-height: 1; border-radius: 5px; transition: box-shadow 200ms ease, background 200ms ease; box-shadow: none;}</style></head><body style='text-align: left; width: 100%'><h1 class='title' style='font-size:300%;'>SmartCare</h1><h1 class='title' >Preencha os dados da rede Wi-Fi a qual o SmartCare será conectado.</h1> <h1 class='title' >O seu SmartCare tem o identificador: XXXXXXXX</h1> </br> <form action='/connect' method='POST'> <div align='center'> <input type='input' name='SSID' placeholder='SSID' class='input' tabindex='1'> </input> </div></br> <div align='center'> <input type='password' name='password' placeholder='Senha' class='input' tabindex='2'> </input> </div></br> <div align='center'> <input type='submit' name='SUBMIT' value='Conectar' class='button' tabindex='3'></input> </div></form> </br> <div align='center'> <h1 class='title' >Lista de redes Wi-Fi detectadas: </br> </br> AAAAAA </h1> </div></br> <h1 class='title' >Caso a conexão seja bem sucedida, a rede 'SmartCare' deverá desaparecer e os dados estarão disponíveis no aplicativo em instantes. Caso contrário, reconecte-se a rede 'SmartCare' e repita o processo.</h1> <div align='center' style='display:none'> <div align='center' id='loader' class='loader'/> </div></body> </html>";
const String connect_page = "<!DOCTYPE html><html><head><title>SmartCare - Configuração</title> <style>.loader{border: 16px solid #f3f3f3; border-top: 16px solid #3498db; border-radius: 50%; width: 120px; height: 120px; animation: spin 2s linear infinite; text-align:center;}@keyframes spin{0%{transform: rotate(0deg);}100%{transform: rotate(360deg);}}.title{font-family:verdana; color: rgb(52, 73, 94); text-align:center; font-size:100%;}.input{font-family:verdana; box-sizing: border-box; z-index: 21; height: 45px; width: 304px; border: 2px solid rgb(189, 195, 199); background-color: rgb(255, 255, 255); border-radius: 5px; font-size: 14px; color: rgb(52, 73, 94); padding: 0px 6px; transition: border-color 200ms ease;}.button{box-sizing: border-box; z-index: 18; height: 40px; width: 125px; padding: 0px; cursor: inherit; background: none rgb(26, 188, 156); border: none; text-align: center; font-family: verdana; font-size: 14px; color: rgb(255, 255, 255); line-height: 1; border-radius: 5px; transition: box-shadow 200ms ease, background 200ms ease; box-shadow: none;}</style></head><body style='text-align: left; width: 100%'><h1 class='title' style='font-size:300%;'>SmartCare</h1><h1 class='title' >A conexão com a rede AAAAAA está sendo realizada. Em caso de sucesso, a rede Wi-Fi SmartCare irá desaparecer e os dados estarão disponíveis no aplicativo.</h1> <h1 class='title' >Obrigado por usar o SmartCare!</h1> </br> <div align='center'> <div align='center' id='loader' class='loader'/> </div></body> </html>";
const String success_page = "<!DOCTYPE html><html><head><title>SmartCare - Status</title> <style>.title{font-family:verdana; color: rgb(52, 73, 94); text-align:center; font-size:100%;}</style></head><body style='text-align: left; width: 100%'><h1 class='title' style='font-size:300%;'>SmartCare</h1><h1 class='title' >Seu dispositivo já está online! Para visualizar as informações pelo seu aplicativo e configurar os alertas, use os seguintes dados na configuração do app:</h1> </br> <h1 class='title' >Canal: AAAAAA</h1> <h1 class='title' >Senha: BBBBBB</h1> </body> </html>";


// Global Variables
// Access point state machine
uint8_t AccessPointState = SCAN;

// SSIID After configuration (Will always reconnect until reset)
String permanentSSID;
// Password after configurarion
String pernamentPassword;
// If it is configured succesfully (Will try to reconnect always)
uint8_t isConfigured = 0;

uint8_t nWifiScanned = 0;
String SSIDScanned[32];

String TS_Private_Key = "CZBE60LSEORZKQ2H";

String TS_Channel_Key = "";
String TS_Channel_ID = "";


ESP8266WebServer server(80);

void handleSuccess()
{
    String htmlSSIDs = "";
    String Page = success_page;
    
    Page.replace("AAAAAA", TS_Channel_ID);
    Page.replace("BBBBBB", TS_Channel_Key);
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
            break;
        }
    }

    if (foundWifi == 1)
    {
        AccessPointState = CONNECT;
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
        AccessPointState = EEPROM.read(EEPROM_STATE);
        Serial.print(AccessPointState);
        
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

        if (AccessPointState == CONFIGURED)
        {
            Serial.print("Connecting to ");
            Serial.println(permanentSSID);
            
            WiFi.begin(permanentSSID.c_str(), pernamentPassword.c_str());
            
            while (WiFi.status() != WL_CONNECTED)
            {
                delay(500);
                Serial.print(".");
            }
            AccessPointState = CONFIGURED;
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
}

void loop()
{
    int i = 0;
    if (AccessPointState == SCAN)
    {
        Serial.println("Scanning Wi-Fi Networks available");
    
        // Set WiFi to station mode and disconnect from an AP if it was previously connected
        WiFi.mode(WIFI_STA);
        WiFi.disconnect();
        delay(100);
        
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
        AccessPointState = SETUP_SERVER;
    }
    else if(AccessPointState == SETUP_SERVER)
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
        AccessPointState = WAIT_USER;
    }
    else if (AccessPointState == WAIT_USER)
    {
        server.handleClient();
    }
    else if (AccessPointState == CONNECT)
    {
        server.stop();
        Serial.print("Connecting to ");
        Serial.println(permanentSSID);
        
        if (WiFi.status() != WL_CONNECTED)
        {
            WiFi.begin(permanentSSID.c_str(), pernamentPassword.c_str());
        
            while (WiFi.status() != WL_CONNECTED)
            {
                delay(500);
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

        // connect to thingspeak channel etc
       
        if (client.connect(host.c_str(), 80))
        {
            String jsonReply;
            String url;
            if (TS_Channel_Key == "" || TS_Channel_ID == "")
            {
                url = "/channels.json?api_key=" + TS_Private_Key + 
                "&description=SmartCare Device Channel" + 
                "&field1=Nível de Bateria" + 
                "&field2=Sinal do Relógio" + 
                "&field3=Temperatura Ambiente" + 
                "&field4=Batimentos" + 
                "&field5=FALL_ALARM" + 
                "&field6=BATT_ALARM" + 
                "&field7=OTHER_ALARM" + 
                "&field8=MED_LIST" + 
                "&metadata=email1,email2;twitter1,twitter2;0;0" + 
                "&name=SmartCare Device " + String(DeviceID) + ;
                
                client.print(String("POST ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Connection: Keep-Alive\r\n\r\n");

                while (client.connected())
                {
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

                url = "/update?api_key=" + TS_Channel_Key + 
                "&field1=" + String(DeviceID);
                
                client.print(String("POST ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Connection: Keep-Alive\r\n\r\n");

                while (client.connected())
                {
                    String line = client.readStringUntil('\n');
                    Serial.println(line);
                    if (line.indexOf("{\"id\":") != -1)
                    {
                        jsonReply = line;
                        break;
                    }
                }

                Serial.println(jsonReply);

                if (jsonReply.indexOf("{\"channel_id\":" + TS_Channel_ID) != 0)
                {
                    AccessPointState = CONFIGURED;
                
                    EEPROM.write(EEPROM_STATE, CONFIGURED);
                    EEPROM.commit();
                }

                if (twitter.post("Um Olá do SmartCare!"))
                {
                  int status = twitter.wait(&Serial);
                  if (status == 200) {
                    Serial.println("OK.");
                  } else {
                    Serial.print("failed : code ");
                    Serial.println(status);
                  }
                }
                else
                {
                  Serial.println("connection failed.");
                }
            }
            else
            {
                url = "/update?api_key=" + TS_Channel_Key + 
                "&field1=" + String(DeviceID);
                
                client.print(String("POST ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Connection: Keep-Alive\r\n\r\n");

                while (client.connected())
                {
                    String line = client.readStringUntil('\n');
                    Serial.println(line);
                    if (line.indexOf("{\"id\":") != -1)
                    {
                        jsonReply = line;
                        break;
                    }
                }

                Serial.println(jsonReply);

                if (jsonReply.indexOf("{\"channel_id\":" + TS_Channel_ID) == 0)
                {
                    AccessPointState = SCAN;
                
                    EEPROM.write(EEPROM_STATE, CONNECT);
                    EEPROM.commit();
                }
                else
                {
                    AccessPointState = CONFIGURED;
                
                    EEPROM.write(EEPROM_STATE, CONFIGURED);
                    EEPROM.commit();
                }

                if (twitter.post("Um Olá 2 do SmartCare!"))
                {
                  int status = twitter.wait(&Serial);
                  if (status == 200) {
                    Serial.println("OK.");
                  } else {
                    Serial.print("failed : code ");
                    Serial.println(status);
                  }
                }
                else
                {
                  Serial.println("connection failed.");
                }
            }
        }
        else
        {
            Serial.println("connection failed");
        }
    }
    else if (AccessPointState == CONFIGURED)
    {
        Serial.println("CONFIGURADO");// handle device and internet connections

        // loop serial
        while (1)
        {
            // poll access point
            // check response
            // act on channel/send tweet/email
        }
    }
    else
    {
        AccessPointState = SCAN;
    }
}
