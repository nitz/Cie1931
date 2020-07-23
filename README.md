# CIE1931 LED Linear Brightness Ramp

Does your LED brightness ramp like this as you increase your PWM duty cycle?

![sad led noises](https://github.com/nitz/Cie1931/blob/master/images/leds_uncorrected.png?raw=true)

But you'd rather them ramp up like this, smooth and pleasing to the eye?

![giggles in diode emmited light](https://github.com/nitz/Cie1931/blob/master/images/leds_corrected.png?raw=true)

Then do I have the tiny library for you!

## Description

Cie1931 is a small C++ library (if you can call it that!) that uses constexpr to generate a lookup table for translating a PWM duty cycle scale into a mostly linear brightness output.

## Usage

This code should run on basically any platform with a C++11 complier for it. You shouldn't even need floating point support on your target platform, because the math is all done at compile time.

Using it is easy. Declare the curve with the settings you want, and use it liek a lookup table. Here's an Arduino example:

```cpp

#include "cie1931.h"

constexpr Cie1931<> cie1931;

// Optionally you may specify via template pameters:
//  - the max duty cycle value of your PWM (InputMax)
//  - the max resultant duty cycle value (OutputMax)
//  - the lookup table variable type (ResultType)
// e.g.: Cie1931<512, 1023, uint16_t> curve;
// Would specify a curve with 512 input values
// that produces a range from 0-1023, stored
// in 16 bit unsigned integers.

size_t pwmStep = 0;
constexpr int PWM_PIN = 9;

void setup()
{
	// no need to do any setup, the curve is already ready!
}

void loop()
{
	// restart our step if we go past the length
	if (pwmStep >= cie1931.Length)
	{
		pwmStep = 0;
	}
	
	// step through each value in the generated curve
	uint8_t pwmVal = cie1931[pwmStep++];

	// set our PWM DC
	analogWrite(PWM_PIN, pwmVal);
	
	// a short pause before moving to the next value
	delay(50);
}
```

## Acknowledgments & Licenses

This project is MIT licensed. See `LICENSE` for more information.

Special thanks to [Jared Sanson](https://github.com/jorticus)'s [blog post](https://jared.geek.nz/2013/feb/linear-led-pwm) that led (pun intended) to me creating this small tool. I found their approach to the generation of a lightness curve novel, and wanted to be able to do it at compile time without needing to create source files should I change my settings. Images are also via Jared.

Please feel free to open an issue or PR if you find a bug or have a suggestion!
