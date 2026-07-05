#include <WiFi.h>
 
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WiFiServer server(80);

const int relayPin = 26;

void setup() {
  Serial.begin(115200);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected to WiFi");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    if (request.indexOf("/ON") != -1) {
      digitalWrite(relayPin, LOW);
    }

    if (request.indexOf("/OFF") != -1) {
      digitalWrite(relayPin, HIGH);
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();

    client.println("<!DOCTYPE html>");
    client.println("<html>");
    client.println("<head>");
    client.println("<title>Smart Home Control</title>");
    client.println("</head>");
    client.println("<body style='text-align:center;'>");
    client.println("<h1>IoT Smart Home Control</h1>");
    client.println("<p><a href='/ON'><button style='padding:15px;'>Turn ON</button></a></p>");
    client.println("<p><a href='/OFF'><button style='padding:15px;'>Turn OFF</button></a></p>");
    client.println("</body>");
    client.println("</html>");

    client.stop();
  }
}
