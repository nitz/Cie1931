#include "cie1931.hpp"

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

void loop() {
	// restart our step if we go past the length
	if (pwmStep >= cie1931.Length) {
		pwmStep = 0;
	}
	
	// step through each value in the generated curve
	uint8_t pwmVal = cie1931[pwmStep++];

	// set our PWM DC
	analogWrite(PWM_PIN, pwmVal);
	
	// a short pause before moving to the next value
	delay(50);
}