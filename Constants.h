#pragma once
#include "Engine\Color.h"

const int RAYLENGTHCAP = 1000.0f;
const int DEPTHCAP(2);
const int THREADCOUNT = 8;
const float ANTIALLIASING = 2.0f; // should be a number of x^2 where x is a whole number
const RGBA8 PRIMARYRAYCOLOR = RGBA8(255, 255, 255, 255);
const RGBA8 REFLECTRAYCOLOR = RGBA8(255, 0, 0, 255);