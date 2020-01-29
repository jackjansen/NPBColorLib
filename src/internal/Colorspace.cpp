/*-------------------------------------------------------------------------
TempFColor provides a color object that represents Temp values as floating
point numbers between 0.0 and 1.0

-------------------------------------------------------------------------*/

#include "Colorspace.h"
#include "RgbFColor.h"
#include "RgbwFColor.h"
#include "HslFColor.h"
#include "TempFColor.h"

inline void _clamp(float& f)
{
	if (f < 0) f = 0;
	if (f > 1) f = 1;
}

RgbwFColor Colorspace::toRgbwFColor(TempFColor src) {
  assert(0);
}

RgbFColor Colorspace::toRgbFColor(TempFColor src) {
  assert(0);
}

RgbwFColor Colorspace::toRgbwFColor(HslFColor src) {
  assert(0);
}

RgbFColor Colorspace::toRgbFColor(HslFColor src) {
  assert(0);
}

RgbwFColor Colorspace::toRgbwFColor(RgbFColor src) {return src; }
RgbFColor Colorspace::toRgbFColor(RgbFColor src) {return src; }

RgbwColor Colorspace::toRgbwColor(TempFColor src) {return toRgbwColor(src); }
RgbColor Colorspace::toRgbColor(TempFColor src) {return toRgbColor(src); }
RgbwColor Colorspace::toRgbwColor(HslFColor src) {return toRgbwColor(src); }
RgbColor Colorspace::toRgbColor(HslFColor src) {return toRgbColor(src); }
RgbwColor Colorspace::toRgbwColor(RgbFColor src) {return toRgbwColor(src); }
RgbColor Colorspace::toRgbColor(RgbFColor src) {return toRgbColor(src); }
