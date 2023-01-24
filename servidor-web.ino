//Librerias
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266FtpServer.h>
#include <FS.h>
#include <map>

// Variables
const char* ssid = "Mi-Wifi";
const char* password = "MiClave";
const char* userftp = "MiUsuario";
const char* passftp = "MiContraseña";
const String errorPage = "Pagina en mantenimiento";

// Ip, mascara y puerta de enlace
IPAddress ip(192,168,1,60);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

// Iniciar FTP y abrir puerto 80
FtpServer ftpSrv;
ESP8266WebServer server(80);

// Cargar varios archivos
std::map<String, String> staticFiles = {
  {"/logo.png", "image/png"},
  {"/estilo.css", "text/css"},
  {"/script.js", "application/javascript"}
};

// Cargar archivo index
void handleRoot() {
  String html = SPIFFS.exists("/index.html") ? SPIFFS.open("/index.html", "r").readString() : errorPage;
  server.send(200, "text/html", html);
}

// Mostrar pagina en mantenimiento y error
void handleStaticFiles() {
  String path = server.uri();
  if (staticFiles.count(path) > 0) {
    String file = SPIFFS.exists(path) ? SPIFFS.open(path, "r").readString() : errorPage;
    server.send(200, staticFiles[path], file);
  } else {
    server.send(404, "text/html", errorPage);
  }
}

void setup(void) {
// Conexion a wifi  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

// Cargar servicio SPIFFS
  SPIFFS.begin();
  ftpSrv.begin(userftp, passftp);

  server.on("/", handleRoot);
  for (auto& file : staticFiles) {
    server.on(file.first, handleStaticFiles);    
}

server.begin();
}

void loop(void) {
  ftpSrv.handleFTP();
  server.handleClient();
}
