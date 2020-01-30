#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <NeoPixelBus.h>
#include <NPBColorLib.h>

// Fill in your SSID and password here
const char* ssid = "......";
const char* password = "......";

WebServer server(80);

// Ensure feature, pin and count match your hardware
NeoPixelBus<NeoGrbwFeature, Neo800KbpsMethod> pixelBus(10, 4);

bool pixelRefresh;

RgbFColor rgbColor(0,0,0);
HslFColor hslColor(0,0,0);
TempFColor tempColor(4000,0);
enum { rgb, hsl, temp } whichColor;
Colorspace colorspace(4000, 0, true, false);  // Default: don't use W channel, hue priority, no gamma

void handleRoot() {
  // Handle any parameters to the form
  if (server.hasArg("colorspace")) {
    float temperature = server.arg("temperature").toFloat();
    float brightness = server.arg("brightness").toFloat();
    int hue = server.arg("hue").toInt();
    int gamma = server.arg("gamma").toInt();
    colorspace = Colorspace(temperature, brightness, hue, gamma);
    pixelRefresh = true;
  }
  if (server.hasArg("rgb")) {
    float r = server.arg("r").toFloat();
    float g = server.arg("g").toFloat();
    float b = server.arg("b").toFloat();
    rgbColor = RgbFColor(r, g, b);
    whichColor = rgb;
    pixelRefresh = true;
  }
  if (server.hasArg("hsl")) {
    float h = server.arg("h").toFloat();
    float s = server.arg("s").toFloat();
    float l = server.arg("l").toFloat();
    hslColor = HslFColor(h, s, l);
    whichColor = hsl;
    pixelRefresh = true;
  }
  if (server.hasArg("temp")) {
    float temperature = server.arg("temperature").toFloat();
    float brightness = server.arg("brightness").toFloat();
    tempColor = TempFColor(temperature, brightness);
    whichColor = temp;
    pixelRefresh = true;
  }
  // Create output form
  String doc = "<html><head><title>RGBW ledstrip example</title><head><body><h1>ledstrip example</h1>";
  doc += "<p>Change color mapping parameters or color to see the effect on the led strip.</p>";
  doc += "</body></html>";

  doc += "<h2>Colorspace parameters</h2><form>";
  doc += "Color Temperature of White LED (usually 3000 for warm, 4000 for neutral or 5000 for cool white): <br><input name='temperature' value='" + String(colorspace.WTemperature) + "'><br>";
  doc += "Brightness of White LED compared to RGB White (floating point number), 0 to not use W channel:<br><input name='brightness' value='" + String(colorspace.WBrightness) + "'><br>";
  doc += "Preserve hue (1) or prioritize brightness (0):<br><input name='hue' value='" + String(colorspace.huePriority) + "'><br>";
  doc += "Gamma-correct RGBW (1) or not (0):<br><input name='gamma' value='" + String(colorspace.gammaConvert) + "'><br>";

  doc += "<input type='submit' name='colorspace' value='Set colorspace'></form>";

  doc += "<h2>RGB color</h2><form>";
  if (whichColor == rgb) doc += "Currently shown color is RGB.<br>";
  doc += "Floating point numbers between 0.0 and 1.0.<br>";
  doc += "R: <br><input name='r' value='" + String(rgbColor.R) + "'><br>";
  doc += "G: <br><input name='g' value='" + String(rgbColor.G) + "'><br>";
  doc += "B: <br><input name='b' value='" + String(rgbColor.B) + "'><br>";
  doc += "<input type='submit' name='rgb' value='Set'></form>";

  doc += "<h2>HSL color</h2><form>";
  if (whichColor == hsl) doc += "Currently shown color is HSL.<br>";
  doc += "Floating point numbers between 0.0 and 1.0.<br>";
  doc += "Hue: <br><input name='h' value='" + String(hslColor.H) + "'><br>";
  doc += "Saturation: <br><input name='s' value='" + String(hslColor.S) + "'><br>";
  doc += "Lightness: <br><input name='l' value='" + String(hslColor.L) + "'><br>";
  doc += "<input type='submit' name='hsl' value='Set'></form>";

  doc += "<h2>Temperature/Brightness color</h2><form>";
  if (whichColor == temp) doc += "Currently shown color is Temperature/Brightness.<br>";
  doc += "Color Temperature (2000 - 7000 Kelvin): <br><input name='temperature' value='" + String(tempColor.Temperature) + "'><br>";
  doc += "Brightness (0.0 - 1.0 ): <br><input name='brightness' value='" + String(tempColor.Brightness) + "'><br>";
  doc += "<input type='submit' name='temp' value='Set'></form>";

  server.send(200, "text/html", doc);
}

void handleNotFound() {
  server.send(404, "text/plain", "Not found");
}

void setup(void) {
  // Initialize serial port
  Serial.begin(115200);
  // Initialize neopixels. Flash 25% R/G/B/W for 200ms.
  pixelBus.Begin();
  pixelBus.ClearTo(RgbwColor(64,0,0,0));
  pixelBus.Show();
  delay(200);
  pixelBus.ClearTo(RgbwColor(0,64,0,0));
  pixelBus.Show();
  delay(200);
  pixelBus.ClearTo(RgbwColor(0,0,64,0));
  pixelBus.Show();
  delay(200);
  pixelBus.ClearTo(RgbwColor(0,0,0,64));
  pixelBus.Show();
  delay(200);
  pixelBus.ClearTo(RgbwColor(0,0,0,0));
  pixelBus.Show();
  // Initialize wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("ledstrip")) {
    Serial.println("MDNS responder started");
  }
  // initialize webserver
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  if (pixelRefresh) {
    RgbwColor pixelColor;
    switch(whichColor) {
      case rgb:
        pixelColor = colorspace.toRgbw(rgbColor);
        break;
      case hsl:
        pixelColor = colorspace.toRgbw(hslColor);
        break;
      case temp:
        pixelColor = colorspace.toRgbw(tempColor);
        break;
      default:
        Serial.println("unknown whichColor");
        break;
    }
    Serial.printf("set to r=%d,g=%d,b=%d,w=%d\n", pixelColor.R, pixelColor.G, pixelColor.B, pixelColor.W);
    pixelBus.ClearTo(pixelColor);
    pixelBus.Show();
    pixelRefresh = false;
  }
}
