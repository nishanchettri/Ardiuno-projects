#include <ESP8266WiFi.h>

const char* ssid = "abcd";//put the wifi id here
const char* password = "nishan123";//password
int ledPin1 = 13; // GPIO13-D7
WiFiServer server(80);
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, LOW);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  if (request.indexOf("/LED1=ON") != -1)  {
    digitalWrite(ledPin1, HIGH);
  }
  if (request.indexOf("/LED1=OFF") != -1)  {
    digitalWrite(ledPin1, LOW);
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<br><br>");
  client.print("LED1");
  client.println("<br><br>");
  client.println("<a href=\"/LED1=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED1=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("<br><br>"); 
 client.println("</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println(""); 
}
