#pragma once
#include "Engine\Color.h"

struct Constant {
	const float count;
	const float div1count;
	const float div1countSquared;

	Constant(const float c) : count(c), div1count(1.0f / c), div1countSquared(div1count * div1count) {}
};

const RGBA32 BLACK = RGBA32();
const Constant PRECISIONRAYCAP = Constant(2.0f);
const int RAYLENGTHCAP = 1000;
const int DEPTHCAP = 2;
const int THREADCOUNT = 8;
const float PI = 3.14159265359f;
const float PI2 = 6.28318530718f;
const float FOV = 50.0f;									// is converted into focallength in Raytracergame::init
const RGBA8 PRIMARYRAYCOLOR = RGBA8(255, 255, 255, 255);
const RGBA8 REFLECTRAYCOLOR = RGBA8(255, 0, 0, 255);

/*
TODO BUG FIXES
- not all shadow rays are drawn in the debugger
*/