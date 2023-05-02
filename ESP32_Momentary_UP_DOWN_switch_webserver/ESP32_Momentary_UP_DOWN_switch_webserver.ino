//inclue all required libraries for ESP32 and ESP8266 board

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// REPLACE WITH YOUR NETWORK CREDENTIALS
const char* ssid = "Get-A809D0";
const char* password = "TineOgGunnar";

const int LED_OUTPUT = 2;

// HTML web page
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
  <head>
    <title>ESP32-ESP8266 Momentary Webserver</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      body { font-family: Times New Roman; text-align: center; margin:0px auto; padding-top: 30px;}
      /**************************
  DEFAULT BOOTSTRAP STYLES
**************************/
.btn {
  display: inline-block;
  padding: 6px 12px;
  margin-bottom: 0;
  font-size: 14px;
  font-weight: normal;
  line-height: 1.42857143;
  text-align: center;
  white-space: nowrap;
  vertical-align: middle;
  cursor: pointer;
  -webkit-user-select: none;
     -moz-user-select: none;
      -ms-user-select: none;
          user-select: none;
  background-image: none;
  border: 1px solid transparent;
  border-radius: 4px;
  padding: 10px 16px;
}
  
.btn-lg {
  font-size: 18px;
  line-height: 1.33;
  border-radius: 6px;
}

.btn-primary {
  color: #fff;
  background-color: #428bca;
  border-color: #357ebd;
}

.btn-primary:hover,
.btn-primary:focus,
.btn-primary:active,
.btn-primary.active,
.open .dropdown-toggle.btn-primary {
  color: #fff;
  background-color: #3276b1;
  border-color: #285e8e;
}

/***********************
  ROUND BUTTONS
************************/
.round {
  border-radius: 24px;
}

/***********************
  CUSTON BTN VALUES
************************/

.btn {
  padding: 14px 24px;
  border: 0 none;
  font-weight: 700;
  letter-spacing: 1px;
  text-transform: uppercase;
}
.btn:focus, .btn:active:focus, .btn.active:focus {
  outline: 0 none;
}

.btn-primary {
  background: #0099cc;
  color: #ffffff;
}
.btn-primary:hover, .btn-primary:focus, .btn-primary:active, .btn-primary.active, .open > .dropdown-toggle.btn-primary {
  background: #FF0000;
}
.btn-primary:active, .btn-primary.active {
  background: #008000;
  box-shadow: none;
}
    </style>
  </head>
  <body>
    <center><h1>ESP32-ESP8266 Momentary Webserver</h1></center>
    <button class="btn btn-primary btn-lg round" onmousedown="toggleCheckbox('ONUP');" ontouchstart="toggleCheckbox('ONUP');" onmouseup="toggleCheckbox('OFFUP');" ontouchend="toggleCheckbox('OFFUP');">Momentary Switch: Press to go up</button><br>
    <button class="btn btn-primary btn-lg round" onmousedown="toggleCheckbox('ONDOWN');" ontouchstart="toggleCheckbox('ONDOWN');" onmouseup="toggleCheckbox('OFFDOWN');" ontouchend="toggleCheckbox('OFFDOWN');">
    <svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" version="1.1" width="256" height="256" viewBox="0 0 256 256" xml:space="preserve">
  <g style="stroke: none; stroke-width: 0; stroke-dasharray: none; stroke-linecap: butt; stroke-linejoin: miter; stroke-miterlimit: 10; fill: none; fill-rule: nonzero; opacity: 1;" transform="translate(1.4065934065934016 1.4065934065934016) scale(2.81 2.81)" >
	<path d="M 52.145 9.528 V 1.011 c 0 -0.552 0.448 -1 1 -1 c 0.552 0 1 0.448 1 1 v 8.518 c 0 0.552 -0.448 1 -1 1 C 52.593 10.528 52.145 10.081 52.145 9.528 z" style="stroke: none; stroke-width: 1; stroke-dasharray: none; stroke-linecap: butt; stroke-linejoin: miter; stroke-miterlimit: 10; fill: rgb(0,0,0); fill-rule: nonzero; opacity: 1;" transform=" matrix(1 0 0 1 0 0) " stroke-linecap="round" />
	<path d="M 12.823 57.883 c 0 -0.603 0.229 -1.206 0.688 -1.665 l 9.587 -9.587 c 0.92 -0.918 2.414 -0.918 3.332 0 l 9.447 9.447 l 0 -26.887 c 0 -0.552 0.447 -1 1 -1 s 1 0.448 1 1 l 0 29.301 c 0 0.404 -0.243 0.77 -0.617 0.924 c -0.374 0.155 -0.804 0.069 -1.09 -0.217 L 25.015 48.045 c -0.139 -0.139 -0.365 -0.139 -0.505 0.001 l -9.585 9.585 c -0.14 0.139 -0.139 0.365 0 0.504 l 29.781 29.78 c 0.084 0.084 0.191 0.099 0.266 0.096 c 0.15 0.003 0.257 -0.012 0.341 -0.096 l 29.781 -29.78 c 0.18 -0.181 0.184 -0.321 0 -0.504 l -9.585 -9.586 c -0.139 -0.139 -0.365 -0.139 -0.504 0 L 53.852 59.199 c -0.286 0.286 -0.716 0.372 -1.09 0.217 c -0.374 -0.154 -0.617 -0.52 -0.617 -0.924 l 0 -40.141 c 0 -0.552 0.448 -1 1 -1 s 1 0.448 1 1 l 0 37.727 l 9.447 -9.447 c 0.919 -0.918 2.414 -0.918 3.332 0 l 9.586 9.586 c 0.891 0.892 0.89 2.444 0 3.332 l -29.78 29.78 c -0.463 0.464 -1.087 0.705 -1.755 0.68 c -0.593 0.025 -1.216 -0.216 -1.68 -0.68 l -29.781 -29.78 C 13.053 59.09 12.823 58.486 12.823 57.883 z" style="stroke: none; stroke-width: 1; stroke-dasharray: none; stroke-linecap: butt; stroke-linejoin: miter; stroke-miterlimit: 10; fill: rgb(0,0,0); fill-rule: nonzero; opacity: 1;" transform=" matrix(1 0 0 1 0 0) " stroke-linecap="round" />
	<path d="M 35.877 20.873 v -8.295 c 0 -0.552 0.447 -1 1 -1 s 1 0.448 1 1 v 8.295 c 0 0.552 -0.447 1 -1 1 S 35.877 21.425 35.877 20.873 z" style="stroke: none; stroke-width: 1; stroke-dasharray: none; stroke-linecap: butt; stroke-linejoin: miter; stroke-miterlimit: 10; fill: rgb(0,0,0); fill-rule: nonzero; opacity: 1;" transform=" matrix(1 0 0 1 0 0) " stroke-linecap="round" />
	<path d="M 44.011 41.544 V 7.318 c 0 -0.552 0.448 -1 1 -1 s 1 0.448 1 1 v 34.226 c 0 0.552 -0.448 1 -1 1 S 44.011 42.096 44.011 41.544 z" style="stroke: none; stroke-width: 1; stroke-dasharray: none; stroke-linecap: butt; stroke-linejoin: miter; stroke-miterlimit: 10; fill: rgb(0,0,0); fill-rule: nonzero; opacity: 1;" transform=" matrix(1 0 0 1 0 0) " stroke-linecap="round" />
</g>
</svg>
    </button>
   <script>
   function toggleCheckbox(x) {
     var xhr = new XMLHttpRequest();
     xhr.open("GET", "/" + x, true);
     xhr.send();
   }
  </script>
  </body>
</html>)rawliteral";

bool goingDown = false;
AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  pinMode(LED_OUTPUT, OUTPUT);
  digitalWrite(LED_OUTPUT, LOW);

  // Send web page to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
  });

  // Receive an HTTP GET request
  server.on("/ONDOWN", HTTP_GET, [] (AsyncWebServerRequest * request) {
    digitalWrite(LED_OUTPUT, HIGH);
    goingDown = true;
    request->send(200, "text/plain", "OK");
  });

  // Receive an HTTP GET request
  server.on("/OFFDOWN", HTTP_GET, [] (AsyncWebServerRequest * request) {
    digitalWrite(LED_OUTPUT, LOW);
    goingDown = false;
    request->send(200, "text/plain", "OK");
  });


  server.begin();
}

void loop() {
  if (goingDown)  {
    digitalWrite(LED_OUTPUT, LOW);
    delay (100);
    digitalWrite(LED_OUTPUT, HIGH);
    delay (100);
  }
}