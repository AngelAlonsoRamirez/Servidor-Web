#include <ESP8266WiFi.h>

const char* ssid = "MiFibra-1F2E";
const char* password = "ArC3xdPY";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado a la wifi con esta direccion ip: ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("Servicio iniciado!");
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Conectado!");
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.println(request);
        client.flush();
        String response = "HTTP/1.1 200 OK\r\n\r\n<h1>Hola Mundo!</h1>\r\n";
        client.print(response);
        break;
      }
    }
    client.stop();
    Serial.println("Desconectado.");
  }
}
