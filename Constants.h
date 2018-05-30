#pragma once
#include "Engine\Color.h"

const int RAYLENGTHCAP = 1000.0f;
const int DEPTHCAP = 2.0f;
const int THREADCOUNT = 10;
const float ANTIALLIASING = 2.0f;							// should be a number of x^2 where x is a whole number
const float PI = 3.14159265359f;
const float PI2 = 6.28318530718f;
const float FOV = 50.0f;									// is converted into focallength in Raytracergame::init
const RGBA8 PRIMARYRAYCOLOR = RGBA8(255, 255, 255, 255);
const RGBA8 REFLECTRAYCOLOR = RGBA8(255, 0, 0, 255);

/*
TODO BUG FIXES
- not all shadow rays are drawn in the debugger
*/