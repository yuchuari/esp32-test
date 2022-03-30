
#include <SPI.h>
#include <Ethernet2.h>
#include <ArduinoJson.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 100, 105);


EthernetServer server(80);
EthernetClient client;

String header;
int contador = 0;
DynamicJsonDocument doc(1024);
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  // start the Ethernet connection and the server:
  Ethernet.init(5);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        //Serial.write(c);
        header += c;
        
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '}') {
         Serial.println(header);
         
          if(header.indexOf("GET")>= 0){
            
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");  // the connection will be closed after completion of the response
            client.println("Refresh: 5");  // refresh the page automatically every 5 sec
            client.println();
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("get-eth");
            client.println("</html>");
            break;
          
          }else if(header.indexOf("POST") >= 0){
            
            
            client.println(F("HTTP/1.0 201 OK"));
            client.println(F("Content-Type: application/json"));
            client.println("Connection: close");
            client.println();

            int indice = header.indexOf('{');
            String json = header.substring(indice, -1);
            Serial.println(json);
            //Serial.println(json);
            DeserializationError error = deserializeJson(doc, json);
            Serial.println(error.c_str());
            break;
            
          }else{
            break;
          }
         
        
          
        }
 
      
      }
    }
    header = "";
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
