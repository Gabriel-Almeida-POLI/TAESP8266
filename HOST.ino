
#include <ESP8266WiFi.h>



const char* ssid = "WifiDoTcc";
const char* password = "bengalaeoculos";
WiFiServer server(80);

void setup() {
  //preparando o server
  Serial.begin(9600); 
  
  IPAddress staticIP(192, 168, 4, 2); // IP estático
  IPAddress gateway(192, 168, 4, 1);// gateway estático
  IPAddress subnet(255, 255, 255, 0);// máscara de rede stática

  WiFi.mode(WIFI_AP);// ativando o server na porta 80

  WiFi.softAP(ssid, password, 2, 0);
  WiFi.config(staticIP, gateway, subnet);

  server.begin();

  Serial.println("Server started"); 
  Serial.println(WiFi.softAPIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Esperando o payload do client
  while (!client.available()) {
    delay(1);
  }

  String req = client.readStringUntil('\r');
  req = req.substring(req.indexOf("/") + 1, req.indexOf("HTTP") - 1);
  Serial.println(req);
  client.flush();


  if (req.indexOf("D") != -1)
  {
    client.print("Recebido seu dado D   ");
  }
  else if (req.indexOf("R") != -1)
  {
    client.print("Recebido seu dado R   ");
  }  
  else {
    client.print("Invalid Request");
    client.flush();
    client.stop();
    return;
  }

  client.print("HTTP/1.1 200 OK\n\n");
  client.flush();

}
