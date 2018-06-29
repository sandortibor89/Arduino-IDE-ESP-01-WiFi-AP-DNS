#include <ESP8266WebServer.h>
#include <DNSServer.h>

const byte DNS_PORT = 53;
DNSServer dnsServer;
ESP8266WebServer webServer(80);

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP("ESP-DNS");
  
  dnsServer.setTTL(300);
  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
  
  webServer.onNotFound([]() {
    String message = "Hello DNS!";
    webServer.send(200, "text/plain", message);
  });
  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}
