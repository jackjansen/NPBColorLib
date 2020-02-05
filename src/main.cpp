//
//  main.cpp
//  npbtest
//
//  Created by Jack Jansen on 05/02/20.
//  Copyright © 2020 Jack Jansen. All rights reserved.
//

#include <iostream>
#include "NPBColorLib.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    TempFColor testColor(3000, 0.95);
    Colorspace testSpace(4000, 2.0, false);
    RgbwColor result = testSpace.toRgbw(testColor);
    std::cout << "Temp=" << testColor.Temperature << ", Brightness=" << testColor.Brightness << std::endl;
    std::cout << "R=" << int(result.R) << ", G=" << int(result.G) << ", B=" << int(result.B) << ", W=" << int(result.W) << std::endl;
    return 0;
}
