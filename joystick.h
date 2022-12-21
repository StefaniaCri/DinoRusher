#pragma once
#include "buzzer.h"

int getValue(int pin, bool &joyMoved){
	int val = analogRead(pin);

	if (val >= maxThreshold && joyMoved == false)
	{
		joyMoved = true;
		return 1;
	}

	if (val <= minThreshold && joyMoved == false)
	{
		joyMoved = true;
		return -1;
	}

	if (val < maxThreshold && val > minThreshold)
		joyMoved = false;
	return 0;
}

int getXValue(){
	return getValue(pinX, joyMovedX);
}

int getYValue(){
	return getValue(pinY, joyMovedY);
}

void SWPress()
{
	if (millis() - lastDebounceTime >= debounceDelay)
	{
		buttonPressed = true;
		lastDebounceTime = millis();
	}

	playSound();
}
