/*-------------------------------------------------------------------------
TempFColor provides a color object that represents Temp values as floating
point numbers between 0.0 and 1.0

-------------------------------------------------------------------------*/

#include "Colorspace.h"
#include "RgbFColor.h"
#include "RgbwFColor.h"
#include "HslFColor.h"

inline void _clamp(float& f)
{
	if (f < 0) f = 0;
	if (f > 1) f = 1;
}

NeoGamma<NeoGammaEquationMethod> gammaConverter;

Colorspace::Colorspace(float temperatureW, float brightnessW, bool huePriority, bool gamma)
: WTemperature(temperatureW), 
  WBrightness(brightnessW), 
  whiteColor(TempFColor(temperatureW, 1.0)),
  huePriority(huePriority),
  gammaConvert(gamma)
{

}

void Colorspace::_extractWhiteChannel(RgbwFColor& color) {
  if (WBrightness == 0) return;  // No W channel, nothing to do.
  //
  // Determine how much whiteColor we can move out of color into the W channel.
  // Note that whiteColor (and color) are in D65 space, and the RGB value of
  // whiteColor is therefore the color of our WTemperature in D65 space.
  //
  // Note that during the execution of this method channel values may be > 1 but
  // that will all be fixed.
  //
  float maxFactor = 999;
  if (color.R == 0) {
    maxFactor = 0;
  } else if (whiteColor.R != 0) {
    maxFactor = fmin(maxFactor, color.R / whiteColor.R);
  }
  if (color.G == 0) {
    maxFactor = 0;
  } else if (whiteColor.G != 0) {
    maxFactor = fmin(maxFactor, color.G / whiteColor.G);
  }
  if (color.B == 0) {
    maxFactor = 0;
  } else if (whiteColor.B != 0) {
    maxFactor = fmin(maxFactor, color.B / whiteColor.B);
  }
  //
  // Convert the W channel (if there is any whiteness in it already) to RGB whiteness.
  //
  color.W = color.W / WBrightness;
  //
  // This is our white value, and we subtract the corresponding whiteness from R, G and B.
  // At this point in the code, all magnitudes are relative to 100% RGB led white.
  //
  color.W += maxFactor;
  color.R -= whiteColor.R*maxFactor;
  color.G -= whiteColor.G*maxFactor;
  color.B -= whiteColor.B*maxFactor;
  //
  // Now we adjust for the maximum available brightness (RGB + W combined).
  // Magnitudes are still relative too 100% RGB LED white.
  //
  float maxBrightness = 1.0 + WBrightness; // Maximum brightness of all LEDs
  color.R *= maxBrightness;
  color.G *= maxBrightness;
  color.B *= maxBrightness;
  color.W *= maxBrightness;
  //
  // Move excess whiteness back to the RGB channel, in so far as possible.
  // Magnitude of the W channel is still in 100% RGB white.
  //
  if (color.W > WBrightness) {
    float excessWhite = color.W - WBrightness;
    color.W = WBrightness;
    color.R += whiteColor.R * excessWhite;
    color.G += whiteColor.G * excessWhite;
    color.B += whiteColor.B * excessWhite;
  }
  //
  // Now we convert the W channel to its own 100% value.
  //
  color.W /= WBrightness;
  //
  // If we need to be hue-preserving we divide everything by the maximum value iff
  // any value is >1. This maintains the hue at the expense of not driving the LEDs
  // to the maximum attainable brightness.
  //
  float maxChannel = fmax(color.R, fmax(color.G, color.B));
  if (maxChannel > 1) {
    color.R /= maxChannel;
    color.G /= maxChannel;
    color.B /= maxChannel;
    color.W /= maxChannel/WBrightness;
  }
  //
  // We now clamp all values. For brightness-priority it is definitely needed,
  // for huePriority it will fix any values that have become slightly out-of-range
  // because of floating point rounding errors.
  //
  _clamp(color.R);
  _clamp(color.G);
  _clamp(color.B);
  _clamp(color.W);
}

void Colorspace::Convert(const RgbFColor& from, RgbColor& to) {
  if (gammaConvert) {
    to = gammaConverter.Correct(from);
  } else {
    to = from;
  }
}

void Colorspace::Convert(const RgbFColor& from, RgbwColor& to) {
  RgbwFColor wanted(from);
  _extractWhiteChannel(wanted);
  if (gammaConvert) {
    to = gammaConverter.Correct(wanted);
  } else {
    to = wanted;
  }
}

void Colorspace::Convert(const TempFColor& from, RgbColor& to) {
  RgbFColor wanted(from);
  if (!huePriority && from.Brightness > 0) {
    float brightnessCorrect = from.Brightness / wanted.CalculateBrightness();
    wanted.R *= brightnessCorrect;
    wanted.G *= brightnessCorrect;
    wanted.B *= brightnessCorrect;
    // Finally we move light between the R, G, B. This will result in incorrect
    // colors but so be it. We do this a few times in the hope it distributes everything.
    for(int i=0; i<5; i++) {
      float excessRintensity = fmax(wanted.R-1, 0);
      float excessGintensity = fmax(wanted.G-1, 0);
      float excessBintensity = fmax(wanted.B-1, 0);
      if (excessRintensity < 0.01 && excessGintensity < 0.01 && excessBintensity < 0.01) break;
      wanted.R = wanted.R - excessRintensity + (excessGintensity + excessBintensity) / 2;
      wanted.G = wanted.G - excessGintensity + (excessRintensity + excessBintensity) / 2;
      wanted.B = wanted.B - excessBintensity + (excessRintensity + excessGintensity) / 2;
    }
  }
  _clamp(wanted.R);
  _clamp(wanted.G);
  _clamp(wanted.B);
  if (gammaConvert) {
    to = gammaConverter.Correct(wanted);
  } else {
    to = wanted;
  }
}

void Colorspace::Convert(const TempFColor& from, RgbwColor& to) {
  RgbwFColor wanted(from);
  _extractWhiteChannel(wanted);
  if (!huePriority && from.Brightness > 0) {
    float actualBrightness = (wanted.W*WBrightness + (wanted.R+wanted.G+wanted.B)/3) / (WBrightness+1);
    float brightnessCorrect = from.Brightness / actualBrightness;
    wanted.R *= brightnessCorrect;
    wanted.G *= brightnessCorrect;
    wanted.B *= brightnessCorrect;
    wanted.W *= brightnessCorrect;
    // We attempt to transfer excess intensity to other channels.
    float excessRintensity = fmax(wanted.R-1, 0);
    float excessGintensity = fmax(wanted.G-1, 0);
    float excessBintensity = fmax(wanted.B-1, 0);
    if (WBrightness > 0) {
      // First we transfer all of it to the white channel
      float excessRGBintensity = excessRintensity + excessGintensity + excessBintensity ;
      wanted.W += (excessRGBintensity/3) / WBrightness;
      wanted.R -= excessRGBintensity;
      wanted.G -= excessRGBintensity;
      wanted.B -= excessRGBintensity;
      // If any RGB channel has become negative we move that to W
      if (wanted.R < 0) {
        wanted.W += (-wanted.R/3) / WBrightness;
        wanted.R = 0;
      }
      if (wanted.G < 0) {
        wanted.W += (-wanted.G/3) / WBrightness;
        wanted.G = 0;
      }
      if (wanted.B < 0) {
        wanted.W += (-wanted.B/3) / WBrightness;
        wanted.B = 0;
      }

      // Now we transfer the leftover W back to all of R, G, B
      float excessWintensity = fmax(wanted.W-1, 0)*WBrightness;
      wanted.W -= excessWintensity/WBrightness;
      wanted.R += excessWintensity;
      wanted.G += excessWintensity;
      wanted.B += excessWintensity;
    }
    // Finally we move light between the R, G, B. This will result in incorrect
    // colors but so be it. We do this a few times in the hope it distributes everything.
    for(int i=0; i<5; i++) {
      excessRintensity = fmax(wanted.R-1, 0);
      excessGintensity = fmax(wanted.G-1, 0);
      excessBintensity = fmax(wanted.B-1, 0);
      if (excessRintensity < 0.01 && excessGintensity < 0.01 && excessBintensity < 0.01) break;
      wanted.R = wanted.R - excessRintensity + (excessGintensity + excessBintensity) / 2;
      wanted.G = wanted.G - excessGintensity + (excessRintensity + excessBintensity) / 2;
      wanted.B = wanted.B - excessBintensity + (excessRintensity + excessGintensity) / 2;
    }
  }
  _clamp(wanted.R);
  _clamp(wanted.G);
  _clamp(wanted.B);
  _clamp(wanted.W);
  if (gammaConvert) {
    to = gammaConverter.Correct(wanted);
  } else {
    to = wanted;
  }
}

void Colorspace::Convert(const HslFColor& from, RgbColor& to) {
  RgbFColor wanted(from);
  if (gammaConvert) {
    to = gammaConverter.Correct(wanted);
  } else {
    to = wanted;
  }
}

void Colorspace::Convert(const HslFColor& from, RgbwColor& to) {
  RgbwFColor wanted(from);
  _extractWhiteChannel(wanted);
  if (gammaConvert) {
    to = gammaConverter.Correct(wanted);
  } else {
    to = wanted;
  }
}

RgbColor Colorspace::toRgb(const RgbFColor from) {
  RgbColor to;
  Convert(from, to);
  return to;
}

RgbwColor Colorspace::toRgbw(const RgbFColor from) {
  RgbwColor to;
  Convert(from, to);
  return to;
}

RgbColor Colorspace::toRgb(const TempFColor from) {
  RgbColor to;
  Convert(from, to);
  return to;
}

RgbwColor Colorspace::toRgbw(const TempFColor from) {
  RgbwColor to;
  Convert(from, to);
  return to;
}

RgbColor Colorspace::toRgb(const HslFColor from) {
  RgbColor to;
  Convert(from, to);
  return to;
}

RgbwColor Colorspace::toRgbw(const HslFColor from) {
  RgbwColor to;
  Convert(from, to);
  return to;
}

