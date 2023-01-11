#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#elif defined ESP32
#include <WiFi.h>
#include "SPIFFS.h"
#endif

#include <ESP8266FtpServer.h>

const char* ssid = "TU_SSID";
const char* password = "TU_SSID_PASSWORD";

const char* user = "TU_CUENTA";
const char* pass = "TU_PASSWORD.";


FtpServer ftpSrv;
ESP8266WebServer server(80);

String readFile(const char* path) {
  String content;
  File file = SPIFFS.open(path, "r");
  if (!file) {
    return "Archivo no encontrado";
  }
  while (file.available()) {
    content += char(file.read());
  }
  file.close();
  return content;
}

void handleRoot() {
  String html = readFile("/index.html");
  server.send(200, "text/html", html);
}

void setup(void) {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado a ");
  Serial.println(ssid);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

#ifdef ESP32
  if (SPIFFS.begin(true)) {
#elif defined ESP8266
  if (SPIFFS.begin()) {
#endif
      Serial.println("SPIFFS abierto!");
      ftpSrv.begin(user,pass);
  }    

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("¡WiFi conectada");

  server.on("/", handleRoot);

  server.begin();
  Serial.println("Servidor iniciado");
}

void loop(void){
  ftpSrv.handleFTP();
  server.handleClient();
}