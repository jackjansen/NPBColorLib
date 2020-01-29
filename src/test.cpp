#ifdef WITH_TEST
#include <Arduino.h>

#include "NPBColorLib.h"
#include "assert.h"


static void test_rgb() {
    RgbFColor cf(0.2, 0.4, 0.6);
    RgbColor c(cf);
    RgbFColor cf2(c);
    RgbColor c2(cf2);
    assert(cf == cf2);
    assert(c == c2);
    
    cf2 = cf;
    cf2.Darken(0.1);
    assert(cf2.CalculateBrightness() < cf.CalculateBrightness());
    
    cf2 = cf;
    cf2.Lighten(0.1);
    assert(cf2.CalculateBrightness() > cf.CalculateBrightness());
}

static void test_rgbw() {
    RgbwFColor cwf(0.2, 0.4, 0.6, 0.5);
    RgbwColor cw(cwf);
    RgbwFColor cwf2(cw);
    RgbwColor cw2(cwf2);
    assert(cwf == cwf2);
    assert(cw == cw2);
    
    cwf2 = cwf;
    cwf2.Darken(0.1);
    assert(cwf2.CalculateBrightness() < cwf.CalculateBrightness());
    
    cwf2 = cwf;
    cwf2.Lighten(0.1);
    assert(cwf2.CalculateBrightness() > cwf.CalculateBrightness());

    RgbFColor cf(0.2, 0.4, 0.6);
    cwf = cf;
    assert(cwf.CalculateBrightness() == cf.CalculateBrightness());
}

static void test_hsl() {
    HslFColor ch(0.1, 0.2, 0.3);
    RgbFColor cf3(ch);
    HslFColor ch2(cf3);
    RgbFColor cf4(ch2);
    assert(cf3.CalculateBrightness() == ch.CalculateBrightness());
    assert(ch2.CalculateBrightness() == ch.CalculateBrightness());
    assert(cf4.CalculateBrightness() == ch.CalculateBrightness());
    assert(ch == ch2);
    assert(cf3 == cf4);
}

static void test_temp() {
    TempFColor t1(3000, 0.6);
    TempFColor t2(4000, 0.6);
    assert(t1.CalculateBrightness() == t2.CalculateBrightness());
    RgbFColor cf3 = t1;
    assert(t1.CalculateBrightness() == cf3.CalculateBrightness());
    RgbFColor cf4 = t2;
    assert(t2.CalculateBrightness() == cf4.CalculateBrightness());
    assert(t1 != t2);
    assert(cf3 != cf4);
}

static void test_colorspace() {
    Colorspace space(4000, 1.0, true, false);
    RgbColor resultRgb;
    RgbwColor resultRgbw;
    {
        RgbFColor rgbColor(0.1, 0.2, 0.3);
        resultRgb = space.toRgb(rgbColor);
        assert(resultRgb.CalculateBrightness() == int(255*rgbColor.CalculateBrightness()));
        resultRgbw = space.toRgbw(rgbColor);
        assert(resultRgbw.CalculateBrightness() == int(255*rgbColor.CalculateBrightness()));
    }
    {
        HslFColor hslColor(0.1, 0.2, 0.3);
        resultRgb = space.toRgb(hslColor);
        assert(resultRgb.CalculateBrightness() == int(255*hslColor.CalculateBrightness()));
        resultRgbw = space.toRgbw(hslColor);
        assert(resultRgbw.CalculateBrightness() == int(255*hslColor.CalculateBrightness()));
    }
    {
        TempFColor tempColor(3000, 0.3);
        resultRgb = space.toRgb(tempColor);
        assert(resultRgb.CalculateBrightness() == int(255*tempColor.CalculateBrightness()));
        resultRgbw = space.toRgbw(tempColor);
        assert(resultRgbw.CalculateBrightness() == int(255*tempColor.CalculateBrightness()));
    }
}

void setup() {
    Serial.begin(9600);
    test_rgb();
    test_rgbw();
    test_hsl();
    test_temp();
    test_colorspace();
    Serial.println("All done");
}

void loop() {

}
#endif