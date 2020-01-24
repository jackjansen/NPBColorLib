# NPBColorLib
Color representations and operations for NeoPixelBus.

The intention (of the author, me, Jack Jansen) is that Makuna will incorporate this into NeoPixelBus. License
is LGPL.

## Description

For all color representation objects I have tried to follow the API of _NeoPixelBus_ as much as possible, with all `uint8_t` parameters replaced by `float`. This does have one significant drawback: if someone inadvertantly passes an `uint8_t` value it will result in pretty bright colors...

### RgbFColor

`RgbFColor` represents an RGB color as three floating point numbers between 0.0 and 1.0. It can be casted
to and from `RgbColor`.

### RgbwFColor

`RgbwFColor` represents an RGBW color as four floating point numbers between 0.0 and 1.0. It can be casted
to and from `RgbwColor`.

### TemperatureFColor

_(to be provided)_ `TemperatureFColor` represents a color as two floating point numbers `T` (the black body temperature, usually between 2500 and 7000) and `brightness`, a value between 0.0 and 1.0. It can be casted to `RgbFColor` and `RgbColor` (but not the reverse). This conversion assumes that the white point of the RGB values is at 6500K (also known as D65).

### RgbwSpace

_(to be provided)_ `RgbwSpace` represents an RGBW colorspace. In the constructor you provide the temperature of the White LED (usually 3000 for Warm, 4000 for Neutral and 5000 for Cool, but check the specifications of your LED strip) and the relative power of your White LED (default of 1.0 means the White LED has the same number of Lumen as the R, G and B LEDs combined. Again, check the specifications of your strip).

An `RgbwSpace` object has two methods: `ToRgbw()` converts an `RgbFColor` to an `RgbwFColor` and `FromRgbw()` does the reverse.

_(to be determined)_ Maybe `ToRgbw()` will also accept a `TemperatureFColor` without first casting it to an `RgbFColor`, so the brightness can be given precedence over the color correctness.




