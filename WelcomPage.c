#include <WiFi.h>
#include <WebServer.h>

// Replace with your desired credentials
const char* ssid = "ESP32-Access-Point";
const char* password = "12345678";

// Relay PIN
const int relayPin = 5;

WebServer server(80);

void setup() {
  Serial.begin(115200);
  // Set up the ESP as an Access Point
  WiFi.softAP(ssid, password);

  // Print the IP address
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP Address: ");
  Serial.println(IP);

  // Define server routes
  server.on("/", handleRoot);
  server.on("/sensor-data", handleSensorData);
  server.on("/control", handleControl);
  server.on("/toggle-relay", handleToggleRelay);

  // Start server
  server.begin();

  // Setup the relay pin as output and initialize to LOW (relay off)
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
}

void loop() {
  // Handle client requests
  server.handleClient();
}

void handleRoot() {
  String HTML = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>ESP32 Web Server</title>
<style>
  body { font-family: 'Arial', sans-serif; margin: 0; padding: 0; background-color: #f0f0f0; color: #333; }
  .container { max-width: 600px; margin: 50px auto; padding: 20px; background-color: #fff; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); }
  h1 { color: #0066ff; text-align: center; }
  ul { list-style-type: none; padding: 0; }
  li a { display: block; color: #333; background-color: #e7e7e7; padding: 10px 20px; text-decoration: none; margin: 10px 0; text-align: center; }
  li a:hover { background-color: #ddd; }
</style>
</head>
<body>
<div class="container">
  <h1>Welcome to the ESP32 Web Server</h1>
  <ul>
    <li><a href='/sensor-data'>Sensor Data</a></li>
    <li><a href='/control'>Control Panel</a></li>
  </ul>
</div>
</body>
</html>
)=====";
  server.send(200, "text/html", HTML);
}

void handleSensorData() {
  String sensorDataHTML = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Sensor Data</title>
<style>
  body { font-family: 'Arial', sans-serif; margin: 0; padding: 0; background-color: #f0f0f0; color: #333; }
  .container { max-width: 600px; margin: 50px auto; padding: 20px; background-color: #fff; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); text-align: center; }
  h1 { color: #0066ff; }
  p { margin: 20px 0; }
  a { color: #333; padding: 10px 20px; text-decoration: none; background-color: #e7e7e7; }
  a:hover { background-color: #ddd; }
</style>
</head>
<body>
<div class="container">
  <h1>Sensor Data</h1>
  <p>Temperature: --°C</p>
  <p>Humidity: --%</p>
  <p><a href='/'>Home</a></p>
</div>
</body>
</html>
)=====";
  server.send(200, "text/html", sensorDataHTML);
}

void handleControl() {
  String controlHTML = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Control Panel</title>
<style>
  body { font-family: 'Arial', sans-serif; margin: 0; padding: 0; background-color: #f0f0f0; color: #333; }
  .container { max-width: 600px; margin: 50px auto; padding: 20px; background-color: #fff; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); text-align: center; }
  h1 { color: #0066ff; }
  button { padding: 10px 20px; margin: 20px 0; background-color: #4CAF50; border: none; color: white; cursor: pointer; }
  button:hover { background-color: #45a049; }
  a { color: #333; padding: 10px 20px; text-decoration: none; background-color: #e7e7e7; }
  a:hover { background-color: #ddd; }
</style>
</head>
<body>
<div class="container">
  <h1>Control Panel</h1>
  <button onclick="location.href='/toggle-relay'">Toggle Relay</button>
  <p><a href='/'>Home</a></p>
</div>
</body>
</html>
)=====";
  server.send(200, "text/html", controlHTML);
}

void handleToggleRelay() {
  digitalWrite(relayPin, !digitalRead(relayPin)); // Toggle the relay state
  server.sendHeader("Location", "/control", true); // Redirect back to the control page
  server.send(302, "text/plain", ""); // HTTP redirect
}
