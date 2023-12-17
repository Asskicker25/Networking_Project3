#pragma once

#include <cmath>


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static constexpr float c1 = 1.70158;
static constexpr float c3 = c1 + 1;
static constexpr float c4 = (2 * M_PI) / 3;

static enum Ease_Mode
{
	Sine,
	Quad,
	Cubic,
	Quart,
	Quint,
	Expo,
	Circ,
	Back,
	Elastic,
	Bounce
};

static float easeOutBounce(float time)
{
	const float n1 = 7.5625;
	const float d1 = 2.75;

	if (time < 1 / d1) {
		return n1 * time * time;
	}
	else if (time < 2 / d1) {
		return n1 * (time -= 1.5 / d1) * time + 0.75;
	}
	else if (time < 2.5 / d1) {
		return n1 * (time -= 2.25 / d1) * time + 0.9375;
	}
	else {
		return n1 * (time -= 2.625 / d1) * time + 0.984375;
	}
}

static float EaseIn(Ease_Mode mode, float time)
{
	if (time < 0.0f)
	{
		time = 0;
	}
	else if (time > 1.0f)
	{
		time = 1.0f;
	}

	switch (mode)
	{
	case Sine:
		return 1 - std::cos((time * M_PI) / 2);

	case Quad:
		return time * time;

	case Cubic:
		return time * time * time;

	case Quart:
		return time * time * time * time;

	case Quint:
		return time * time * time * time * time;

	case Expo:
		return time == 0 ? 0 : std::pow(2, 10 * time - 10);

	case Circ:
		return 1 - std::sqrt(1 - std::pow(time, 2));

	case Back:
		return c3 * time * time * time - c1 * time * time;

	case Elastic:

		return time == 0
			? 0
			: time == 1
			? 1
			: -std::pow(2, 10 * time - 10) * std::sin((time * 10 - 10.75) * c4);

	case Bounce:
		return 1 - easeOutBounce(1 - time);
		break;


	default:
		break;
	}
}

static float EaseOut(Ease_Mode mode, float time)
{
	if (time < 0.0f)
	{
		time = 0;
	}
	else if (time > 1.0f)
	{
		time = 1.0f;
	}

	switch (mode)
	{
	case Sine:
		return std::sin((time * M_PI) / 2);

	case Quad:
		return 1 - (1 - time) * (1 - time);
	
	case Cubic:
		return 1 - std::pow(1 - time, 3);

	case Quart:
		return 1 - std::pow(1 - time, 4);

	case Quint:
		return 1 - std::pow(1 - time, 5);

	case Expo:
		return time == 1 ? 1 : 1 - std::pow(2, -10 * time);

	case Circ:
		return std::sqrt(1 - std::pow(time - 1, 2));

	case Back:
		return 1 + c3 * std::pow(time - 1, 3) + c1 * std::pow(time - 1, 2);

	case Elastic:
		return time == 0
			? 0
			: time == 1
			? 1
			: std::pow(2, -10 * time) * std::sin((time * 10 - 0.75) * c4) + 1;

	case Bounce:
		return easeOutBounce(time);

	default:
		break;
	}
}

static Ease_Mode GetMode(const std::string& modeString)
{
	Ease_Mode mode;

	if (modeString == "Sine")
	{
		mode = Sine;
	}
	else if (modeString == "Quad")
	{
		mode = Quad;
	}
	else if (modeString == "Quart")
	{
		mode = Quart;
	}
	else if (modeString == "Cubic")
	{
		mode = Cubic;
	}
	else if (modeString == "Quint")
	{
		mode = Quint;
	}
	else if (modeString == "Expo")
	{
		mode = Expo;
	}
	else if (modeString == "Circ")
	{
		mode = Circ;
	}
	else if (modeString == "Back")
	{
		mode = Back;
	}
	else if (modeString == "Elastic")
	{
		mode = Elastic;
	}
	else if (modeString == "Bounce")
	{
		mode = Bounce;
	}
	return mode;
}