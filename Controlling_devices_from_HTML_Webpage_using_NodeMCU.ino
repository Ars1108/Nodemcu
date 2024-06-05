#include <ESP8266WiFi.h>

WiFiClient client;
WiFiServer server(80);

#define led D5
#define led2 D6

void setup() 
{
  Serial.begin(9600);
  WiFi.begin("aditya", "adityasharma");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  server.begin();
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() 
{
  client = server.available();
  if (client)
  {  
    String request = client.readStringUntil('\n');
    Serial.println(request);
    request.trim();
    if (request.indexOf("GET /led1on") >= 0) {
      digitalWrite(led, HIGH);
    }
    if (request.indexOf("GET /led1off") >= 0) {
      digitalWrite(led, LOW);
    }
    if (request.indexOf("GET /led2on") >= 0) {
      digitalWrite(led2, HIGH);
    }
    if (request.indexOf("GET /led2off") >= 0) {
      digitalWrite(led2, LOW);
    }
    
    client.flush();  // Clear the client's buffer

    // Send the HTTP response headers and body
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");  // Connection closed after response
    client.println();  // Empty line to separate headers from the body

    // HTML content
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<h1>Welcome to the Webpage!</h1>");
    client.println("<h3>LED Controls</h3>");
    client.println("<br>");
    client.println("<a href=\"/led1on\"><button>LED 1 ON</button></a>");
    client.println("<a href=\"/led1off\"><button>LED 1 OFF</button></a><br/>");
    client.println("<a href=\"/led2on\"><button>LED 2 ON</button></a>");
    client.println("<a href=\"/led2off\"><button>LED 2 OFF</button></a><br/>");
    client.println("</html>");

    delay(1);  // Brief pause before closing connection
    client.stop();  // Close the connection
  }
}
