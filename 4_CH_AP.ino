/*********
 This code is from Rui Santos ,i do some changes to work this code for 4 ch. relay module 
 
  Complete project details at https://randomnerdtutorials.com  
*********/
/****** This code is for esp32 for using esp8266 just replace <wifi.h> into <esp8266wifi.h> , also change the  output GPIO pins ****/
// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
// to create its own wifi network
const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
//this pins for esp32 
//change the pins for esp8266
String output12State = "off";
String output13State = "off";
String output14State = "off";
String output27State = "off";

// Assign output variables to GPIO pins
const int output12 = 12;
const int output13 = 13;
const int output14 = 14;
const int output27 = 27;
void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output12, OUTPUT);
  pinMode(output13, OUTPUT);
    pinMode(output14, OUTPUT);
  pinMode(output27, OUTPUT);
 
  // Set outputs to high because we are using active low type relay module
  digitalWrite(output12, HIGH);
  digitalWrite(output13, HIGH);
  digitalWrite(output14, HIGH);
  digitalWrite(output27, HIGH);


  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            //foe GPIO12
            if (header.indexOf("GET /12/on") >= 0) 
            {
              Serial.println("GPIO 12 on");
              output12State = "on";
              digitalWrite(output12, LOW);
            } 
            else if (header.indexOf("GET /12/off") >= 0) 
            {
              Serial.println("GPIO 12 off");
              output12State = "off";
              digitalWrite(output12, HIGH);
            }



            //for GPIO13
            else if (header.indexOf("GET /13/on") >= 0)
            {
              Serial.println("GPIO 13 on");
              output13State = "on";
              digitalWrite(output13, LOW);
            } 
            else if (header.indexOf("GET /13/off") >= 0)
            {
              Serial.println("GPIO 13 off");
              output13State = "off";
              digitalWrite(output13, HIGH);
            }
            
             
             
             //for GPIO14
             else if (header.indexOf("GET /14/on") >= 0)
            {
              Serial.println("GPIO 14 on");
              output14State = "on";
              digitalWrite(output14, LOW);
            } 
            else if (header.indexOf("GET /14/off") >= 0)
            {
              Serial.println("GPIO 14 off");
              output14State = "off";
              digitalWrite(output14, HIGH);
            }

          
            
            
            //for GPIO27
            else if (header.indexOf("GET /27/on") >= 0)
            {
              Serial.println("GPIO 27 on");
              output27State = "on";
              digitalWrite(output27, LOW);
            } 
            else if (header.indexOf("GET /27/off") >= 0)
            {
              Serial.println("GPIO 27 off");
              output27State = "off";
              digitalWrite(output27, HIGH);
            }
          
            
            
            
            
            
            
            
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            
           
            
            
            // Display current state, and ON/OFF buttons for GPIO 12  
            client.println("<p>GPIO 12 - State " + output12State + "</p>");
            // If the output12State is off, it displays the ON button       
            if (output12State=="off") {
              client.println("<p><a href=\"/12/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/12/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            
            
            
            
            
            
            // Display current state, and ON/OFF buttons for GPIO 27  
            client.println("<p>GPIO 27 - State " + output27State + "</p>");
            // If the output27State is off, it displays the ON button       
            if (output27State=="off") {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
            }


    // Display current state, and ON/OFF buttons for GPIO 13 
            client.println("<p>GPIO 13 - State " + output13State + "</p>");
            // If the output13State is off, it displays the ON button       
            if (output13State=="off") {
              client.println("<p><a href=\"/13/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/13/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

    // Display current state, and ON/OFF buttons for GPIO 14  
            client.println("<p>GPIO 14 - State " + output14State + "</p>");
            // If the output14State is off, it displays the ON button       
            if (output14State=="off") {
              client.println("<p><a href=\"/14/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/14/off\"><button class=\"button button2\">OFF</button></a></p>");
            }




          client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
