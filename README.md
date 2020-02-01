# NPBColorLib
Color representations and operations for NeoPixelBus.

The intention (of the author, me, Jack Jansen) is that Makuna will incorporate this into NeoPixelBus. License
is LGPL.

_Note:_ As of this writing the _xxxFColor_ objects mimic the NeoPixelBus _xxxColor_ objects, but this is open to change. Maybe the interpolation functions and such are useless and need to go. Also, `HslFColor` is included because I have a slight preference for HSL over HSB/HSV, but it can go.

## Description

For all color representation objects I have tried to follow the API of _NeoPixelBus_ as much as possible, with all `uint8_t` parameters replaced by `float`. This does have one significant drawback: if someone inadvertantly passes an `uint8_t` value it will result in pretty bright colors...

### RgbFColor

`RgbFColor` represents an RGB color as three floating point numbers between 0.0 and 1.0. It can be casted
to and from `RgbColor`.

### RgbwFColor

`RgbwFColor` represents an RGBW color as four floating point numbers between 0.0 and 1.0. It can be casted
to and from `RgbwColor`.

### HslFColor

`HslFColor` represents a Hue, Saturation, Lightness color as 3 floats. The difference between HSL and HSV/HSB is that HSL has the 100% saturated colors at L=0.5, with L=1.0 being maximum light. HSV/HSB have 100% saturated colors at V=1.0, meaning that the total amount of light is dependent not only on L (or V or B) but also on the Hue and Saturation. HSL is more suitable for lighting applications.

### TemperatureFColor

`TemperatureFColor` represents a color as two floating point numbers `WTemperature` (the black body temperature, usually between 2500 and 7000) and `WBrightness`, a value between 0.0 and 1.0. It can be casted to `RgbFColor` and `RgbColor` (but not the reverse). This conversion assumes that the white point of the RGB values is at 6500K (also known as D65).

### Colorspace

`Colorspace` represents an RGBW colorspace, and is used to convert _xxxFColor_ objects to either _RgbColor_ or _RgbwColor_ for sending to the LED strip.

In the constructor you provide:

- the temperature of the White LED (usually 3000 for Warm, 4000 for Neutral and 5000 for Cool, but check the specifications of your LED strip)
- the relative power of your White LED (default of 1.0 means the White LED has the same number of Lumen as the R, G and B LEDs combined. Again, check the specifications of your strip),
- whether you want the conversion to maintain the hue as much as possible, or whether you prefer to maintain the brightness as much as possible,
- whether you want to gamma-correct the RGB and RGBW values (you proabbly should).

An `RgbwSpace` object has a numnber of methods:

- `toRgbw()` converts any of the _xxxFColor_ objects to `RgbwColor`
- `toRgb()` converts any of the _xxxFColor_ objects to `RgbColor` (for use with RGB strips)
- a `convert(from, to)` method with various signatures to convert in-place with as little copying as possible.



