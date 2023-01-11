# Servidor Web + Ftp

Este servidor web está desarrollado para la placa ESP8266, para que funcióne correctamente, en el apartado donde pone "TU_SSID" y "TU_PASSWORD" escribes tu nombre de wifi y tu contraseña para que la placa pueda conectarse a la wifi.


Este código es un ejemplo de cómo crear un servidor FTP y un servidor web en un dispositivo ESP8266 o ESP32. Utiliza las librerías WiFi.h y ESP8266WebServer.h (o SPIFFS.h y ESP8266FtpServer.h en caso de ESP32).

El código comienza definiendo algunas constantes que contienen la información de la red WiFi a la que el dispositivo debe conectarse (ssid y password) y las credenciales de usuario y contraseña para el servidor FTP (user y pass).

Luego crea una instancia del servidor web y otra del servidor FTP. y una función readFile que se encarga de leer y devolver el contenido de un archivo en el sistema de archivos SPIFFS.

En la función setup, se establece una conexión WiFi y se inicializa el servidor web y FTP.

La función handleRoot es un manejador de eventos que se activa cuando se accede a la raíz ("/") del servidor web. En este caso, devuelve el contenido del archivo index.html.

Por último, en la función loop, se actualiza el servidor FTP y el servidor web y encender y apaga el led built-in en el dispositivo cada segundo.