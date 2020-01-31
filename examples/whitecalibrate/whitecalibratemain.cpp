#include <NeoPixelBus.h>
#include <NPBColorLib.h>

// This example is intended to help you determine the temperature (warm, cool) of your white LED
// and its relative intensity (compared to the white obtained from the RGB leds).
// This is useful if the datasheet of your LED strip (if you have it) doesn't give these values,
// or if you want to double-check.
//
// It's easier to judge things by looking at the ledstrip shining on a white surface or through a piece
// of paper. And you'll never get it absolutely right, the RGB-white will usually look "more harsh"
// than the W-white.
//
// Usage:
// - First set the right type, pin and number of LEDs in your strip.
// - Run. 
//   The LEDs will flash 1 second RGB-white, 1 second W-white.
// - Adjust WBRIGHTNESS until the two 1-second periods seem the same brightness.
// - The adjust WTEMPERATURE until the two periods have the same color.
// - Maybe repeat the whole procedure to fine-tune things, possibly
//   after picking a different INTENSITY.

// Ensure feature, pin and count match your hardware
NeoPixelBus<NeoGrbwFeature, Neo800KbpsMethod> pixelBus(10, 4);

// Relative brightness of W led (compared to RGB). Values > 1 mean W is brighter.
#define WBRIGHTNESS 1.0

// Color temperature of W led. Lower is more red, higher is more blue.
// 3000 is common for "warm", 4000 for "neutral", 5000 for "cool".
#define WTEMPERATURE 4000.0

// Intensity (on a 0..1 scale) of the white we show. Extreme values (near 0 or 1) may not work well.
#define INTENSITY 0.5

// Gamma correction should usually be true.
#define GAMMA true

// Converter used for W-led white
Colorspace colorspaceW(WTEMPERATURE, WBRIGHTNESS, true, GAMMA);  // We use hue-priority for calibration.

// Converter used for RGB-led white
Colorspace colorspaceRGB(WTEMPERATURE, 0, true, GAMMA);  // Don't use white LED at all.

// White color we display. Values are different because 1.0 (max intensity) depends on WBRIGHTNESS.
TempFColor whiteRGB(WTEMPERATURE, INTENSITY);
TempFColor whiteW(WTEMPERATURE, INTENSITY/(1.0+WBRIGHTNESS));

void setup(void) {
  // Initialize serial port
  Serial.begin(115200);
  pixelBus.Begin();
  RgbwColor color;
  while(true) {
    color = colorspaceRGB.toRgbw(whiteRGB);
    pixelBus.ClearTo(color);
    pixelBus.Show();
    Serial.println("Showing RGB-white");
    delay(1000);
    color = colorspaceW.toRgbw(whiteW);
    pixelBus.ClearTo(color);
    pixelBus.Show();
    Serial.println("Showing W-white");
    delay(1000);
  }
}

void loop(void) {
}
