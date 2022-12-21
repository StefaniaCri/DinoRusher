#pragma once
#include "globals.h"
#define NOTE_D5  587
#define NOTE_B0  31
#define duration_note 8

void playSound()
{
	if (settings.sound)
	{
		tone(buzzerPin, 1500, 10);
		delay(10);
	}
}

void playHighscoreAchieved()
{
 if (settings.sound)
	{ int duration = 1000/ duration_note;
    tone(buzzerPin, NOTE_D5, duration);
		delay(10);
	} 
}

void playIncreaseSong()
{
   if (settings.sound)
	{ int duration = 1000/ duration_note;
    tone(buzzerPin, NOTE_B0, duration);
		delay(10);
	} 
}