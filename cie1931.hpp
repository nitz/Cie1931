#pragma once

#include <cstdint>
#include <cstddef>

#define constexpr_round(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))

// thanks http://prosepoetrycode.potterpcs.net/2015/07/a-simple-constexpr-power-function-c/
template <typename T>
constexpr T ipow(T num, unsigned int pow)
{
    return (pow >= sizeof(unsigned int)*8) ? 0 :
        pow == 0 ? 1 : num * ipow(num, pow-1);
}

template<int InputMax = 255, int OutputMax = 255, class ResultType = uint8_t>
class Cie1931
{
public:
	const size_t Length = InputMax + 1;
private:
	// one result for each of the input range, plus zero.
	ResultType lightnessCurve[InputMax+1];

	constexpr double cie1931(double input)
	{
		double L = input * 100.0;
		double result = 0;

		if (L < 8.0)
		{
			result = (L / 903.3);
		}
		else
		{
			result = ipow(((L + 16.0) / 116.0), 3);
		}

		return result;
	}

public:
	constexpr Cie1931() : lightnessCurve()
	{
		// generate a result for 0 through input max.
		for (size_t input = 0; input <= InputMax; ++input)
		{
			// scale input to a range of 0.0-1.0
			double normalizedInput = (double)input / InputMax;

			// calculate cie1931, and scale it up to the output size, round it, and store it.
			lightnessCurve[input] = constexpr_round(cie1931(normalizedInput) * OutputMax);
		}
	}

	const ResultType& operator[](size_t index) const
	{
		if (index >= Length)
		{
			return lightnessCurve[Length - 1];
		}

		return lightnessCurve[index];
	}
};
