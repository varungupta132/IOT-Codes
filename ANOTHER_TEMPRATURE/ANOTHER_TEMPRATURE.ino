#include <ESP8266WiFi.h>

const char* ssid = "POCO M3";
const char* password = "12345678";

float temp=A0;
int analog= 0;
WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  delay(10);

  // Connect to Wi-Fi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to Internet ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  /*-------- server started---------*/
  server.begin();
  Serial.println("Server started");

  /*------printing ip address--------*/
  Serial.print("IP Address of network: ");
  Serial.println(WiFi.localIP());
  Serial.print("Copy and paste the following URL: https://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop()
{
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }
  Serial.println("Waiting for new client");
  while(!client.available())
  {
    delay(1);
  }
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<HTML>");
  client.println("<meta http-equiv=\"refresh\" content=\10\">");

  client.println("LM35 Temperature Sensor");

  client.println("<br><br>");
  client.println("Temperature:");
  analog= analogRead(A0);
  temp = analog*0.48828125;
  client.print(temp);
  client.println(" degrees Celsius ");
  client.println("<br><br>");
  client.println("<html>");

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}