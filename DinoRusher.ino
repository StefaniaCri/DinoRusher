#include <LiquidCrystal.h>
#include <LedControl.h>
#include <EEPROM.h>

#include "globals.h"
#include "lcdMenu.h"
#include "drawingsForMatrix.h"
#include "drawingsForLCD.h"
#include "game.h"
#include "joystick.h"
#include "matrix.h"
#include "eeprom.h"
void setup() {
	lc.shutdown(0, false);
  initialPlayerPosition();
	lc.clearDisplay(0);	// clear screen
	randomSeed(magicSeedNumbber);

	lcd.begin(LCD_HEIGHT, LCD_WIDTH);
	lcd.createChar(0, dino);
	lcd.createChar(1, soundOn);
	lcd.createChar(2, soundOff);
	lcd.createChar(3, heart);
  lcd.createChar(4, upArrow);
	lcd.createChar(5, downArrow);
	lcd.createChar(6, leftArrow);
	lcd.createChar(7, rightArrow);
	lcd.noCursor();
	lcd.noBlink();
	lcd.noAutoscroll();
	analogWrite(LCD_BRIGHTNESS_PIN, map(settings.brightness, 1, 12, 1, 255));
	pinMode(buzzerPin, OUTPUT);

	Serial.begin(9600);
	pinMode(pinSW, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(pinSW), SWPress, FALLING);
	readFromEEPROM();
  readHighscoreEEPROM();
	lc.setIntensity(0, settings.matrixBrightness);
	lcdAtStart();
}

void loop() {
  analogWrite(LCD_BRIGHTNESS_PIN, map(settings.brightness, 1, 12, 1, 255));
 	if (inGame == true)
	{
		if (firstInLoop)
		{
			lcd.clear();
      buttonPressed = false;
      time = 0;
			firstInLoop = false;
		}

		game();
		gameLCDdisplay();
	}
	else if (inMenu == true)
	{
		MenuDisplay();
	}
	else if (inSetting == true)
	{
		SettingsDisplay();
	}
	else if (withBussiness == true)
	{
		doingBussiness();
	} 

}
