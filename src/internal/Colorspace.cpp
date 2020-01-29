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

RgbwColor Colorspace::toRgbwColor(TempFColor src) {
  return (RgbwColor)toRgbwFColor(src);
}

RgbwFColor Colorspace::toRgbwFColor(HslFColor src) {
  assert(0);
}

RgbwColor Colorspace::toRgbwColor(HslFColor src)  {
  return (RgbwColor)toRgbwFColor(src);
}

RgbwFColor Colorspace::toRgbwFColor(RgbFColor src) {
  assert(0);
}

RgbwColor Colorspace::toRgbwColor(RgbFColor src) {
  return (RgbwColor)toRgbwFColor(src);
}
