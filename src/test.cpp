#ifdef WITH_TEST
#include <Arduino.h>

#include "NPBColorLib.h"
#include "assert.h"

void setup() {
    Serial.begin(9600);

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

    cwf = cf;
    assert(cwf.CalculateBrightness() == cf.CalculateBrightness());

    HslFColor ch(0.1, 0.2, 0.3);
    RgbFColor cf3(ch);
    HslFColor ch2(cf3);
    RgbFColor cf4(ch2);
    assert(cf3.CalculateBrightness() == ch.CalculateBrightness());
    assert(ch2.CalculateBrightness() == ch.CalculateBrightness());
    assert(cf4.CalculateBrightness() == ch.CalculateBrightness());
    assert(ch == ch2);
    assert(cf3 == cf4);

    TempFColor t1(3000, 0.6);
    TempFColor t2(4000, 0.6);
    assert(t1.CalculateBrightness() == t2.CalculateBrightness());
    cf3 = t1;
    assert(t1.CalculateBrightness() == cf3.CalculateBrightness());
    cf4 = t2;
    assert(t2.CalculateBrightness() == cf4.CalculateBrightness());
    assert(t1 != t2);
    assert(cf3 != cf4);

    Serial.println("All done");
}

void loop() {

}
#endif