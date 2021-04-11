
#include <ESP8266WiFi.h>
#include <Ultrasonic.h>
 Ultrasonic ultrassom(13,12);
long distancia;
const char* ssid = "WifiDoTcc";
const char* password = "bengalaeoculos";

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  IPAddress staticIP(192, 168, 0, 191);
  IPAddress gateway(192, 168, 4, 1);
  IPAddress subnet(255, 255, 255, 0);

  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);
 
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);   
  } 
  server.begin();   
  Serial.println("Conected");
  Serial.println(WiFi.localIP());
}

void loop() {
  

  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  while (!client.available()) {
    delay(1);  
  }
  distancia = ultrassom.Ranging(CM);
  Serial.print(distancia); //imprime o valor da variável distancia
   Serial.println("cm");
   delay(100);
  String req = client.readStringUntil('\r');  
  client.flush();

  if (req.indexOf("/distancia") != -1)
  {    
    client.println("Ok");
    client.print("HTTP/1.1 200 OK\n\n");    
    client.flush();
  } 
  else {
    client.println("invalid request");
    client.stop();
    return;
  }
  client.stop();

}
