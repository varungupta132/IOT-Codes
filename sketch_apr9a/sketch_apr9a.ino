#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
WiFiClient client;

#define ACCEPT_TYPE "text/csv" //comma seperated value
int Led_Control=2;

const char ssid[] = "varun";
const char password[] = "12345678";
const char host[] = "thingworx.scetngp.com";
const int httpPort = 80;

const char Thing[] = "varun_led";
const char get_Property[] = "switch_vg";
const char appKey[]= "907c0a96-7c02-4b22-9f92-9b3c88a01eb8";

String Get(String get_Thing, String get_Property)
{              
        HTTPClient http;
        int httpCode = -1;
        String fullRequestURL = "http://"+String(host)+":"+String(httpPort)+"/Thingworx/Things/"
                                +get_Thing+"/Properties/"+get_Property +"?appKey="+appKey;
                               
        Serial.println(fullRequestURL);
        http.begin(client, fullRequestURL);
        http.addHeader("Accept",ACCEPT_TYPE,false,false);        
        httpCode = http.GET();
        Serial.println(httpCode);
       
        String responses;
        if(httpCode > 0)        
        {            
           responses= http.getString();
             Serial.println(responses);          
        }
        else        
        {
            Serial.printf("[httpGetPropertry] failed, error: %s\n\n", http.errorToString(httpCode).c_str());
        }
        http.end();
        return responses;        
}

void setup()
{
 
Serial.begin(115200);
pinMode(Led_Control,OUTPUT);

 Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
{
    delay(500);
    Serial.print(".");
 }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(100);
}

void loop()
{
  String res = Get(Thing,get_Property);  
 //Serial.println(res); // "Switch":"1.0"/r/n
 Serial.println(res[11]);

  if(res[14] == 't')
  {
    digitalWrite(2,HIGH);
    Serial.println("relay on");
  }
  else if(res[14] == 'f')
  {
    digitalWrite(2,LOW);
    Serial.println("relay off");
  }
  delay(2000);
}