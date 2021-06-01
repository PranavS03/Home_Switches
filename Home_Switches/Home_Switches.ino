// Load Wi-Fi library
#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid = "home2.4ghz"; // Input your wifi network name
const char* password = "Smkp@5858"; // Input your wifi password

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String relay1State = "off";
String relay2State = "off";
String relay3State = "off";
String relay4State = "off";
String relay5State = "off";
String relay6State = "off";

// Assign output variables to GPIO pins
const int relay1 = 16; // GPIO5 D1
const int relay2 = 5; // GPIO4 D2
const int relay3 = 4; // GPIO0 D3
const int relay4 = 12; // GPIO2 D4
const int relay5 = 14; // GPIO2 D5
const int relay6 = 1; // GPIO2 D6

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT); 
  pinMode(relay6, OUTPUT);  
  // Set outputs to HIGH. relay active LOW
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  digitalWrite(relay5, HIGH);
  digitalWrite(relay6, HIGH);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
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
            if (header.indexOf("GET /16/on") >= 0)
            {
              
              relay1State = "on";
              digitalWrite(relay1, LOW);
            }
            else if (header.indexOf("GET /16/off") >= 0)
            {
              
              relay1State = "off";
              digitalWrite(relay1, HIGH);
            }
            else if (header.indexOf("GET /5/on") >= 0) {
              
              relay2State = "on";
              digitalWrite(relay2, LOW);
            }
            else if (header.indexOf("GET /5/off") >= 0) {
              
              relay2State = "off";
              digitalWrite(relay2, HIGH);
            }
            else if (header.indexOf("GET /4/on") >= 0)
            {
              
              relay3State = "on";
              digitalWrite(relay3, LOW);
            }
            else if (header.indexOf("GET /4/off") >= 0)
            {
              
              relay3State = "off";
              digitalWrite(relay3, HIGH);
            }
            else if (header.indexOf("GET /12/on") >= 0)
            {
              
              relay4State = "on";
              digitalWrite(relay4, LOW);
            }
            else if (header.indexOf("GET /12/off") >= 0)
            {
              
              relay4State = "off";
              digitalWrite(relay4, HIGH);
            }
            else if (header.indexOf("GET /14/on") >= 0)
            {
              
              relay5State = "on";
              digitalWrite(relay5, LOW);
            }
            else if (header.indexOf("GET /14/off") >= 0)
            {
              
              relay5State = "off";
              digitalWrite(relay5, HIGH);
            }
            else if (header.indexOf("GET /1/on") >= 0) {
              
              relay6State = "on";
              digitalWrite(relay6, LOW);
            }
            else if (header.indexOf("GET /1/off") >= 0) {
              
              relay6State = "off";
              digitalWrite(relay6, HIGH);
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 12px 24px;");
            client.println("text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");

            // Web Page Heading
            client.println("<body><h1>Home Switches</h1>");

            // Display current state, and ON/OFF buttons for GPIO 16
            client.println("<p>Fan 1 is " + relay1State + "</p>");
            // If the relay1State is off, it displays the ON button
            if (relay1State == "off") {
              client.println("<p><a href=\"/16/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/16/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for GPIO 5
            client.println("<p>Light 1 is " + relay2State + "</p>");
            // If the relay2State is off, it displays the ON button
            if (relay2State == "off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for GPIO 4
            client.println("<p>Light 2 is " + relay3State + "</p>");
            // If the relay1State is off, it displays the ON button
            if (relay3State == "off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for GPIO 12
            client.println("<p>Fan 2 is " + relay4State + "</p>");
            // If the relay2State is off, it displays the ON button
            if (relay4State == "off") {
              client.println("<p><a href=\"/12/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/12/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            
            // Display current state, and ON/OFF buttons for GPIO 14
            client.println("<p>Light 3 is " + relay4State + "</p>");
            // If the relay2State is off, it displays the ON button
            if (relay5State == "off") {
              client.println("<p><a href=\"/14/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/14/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            
            // Display current state, and ON/OFF buttons for GPIO 1
            client.println("<p>Light 4 is " + relay4State + "</p>");
            // If the relay2State is off, it displays the ON button
            if (relay6
            State == "off") {
              client.println("<p><a href=\"/1/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/1/off\"><button class=\"button button2\">OFF</button></a></p>");
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
