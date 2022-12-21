#include "HardwareSerial.h"
#include "EEPROM.h"
#include "Arduino.h"
#include "matrix.h"
#include "globals.h"
#include "eeprom.h"
#include "joystick.h"
#include "drawingsForMatrix.h"
#include "buzzer.h"
#include "game.h"
#pragma once

void updateBrigtness()
{
  analogWrite(LCD_BRIGHTNESS_PIN, map(settings.brightness, 1, 12, 1, 255));
}

void goBackToSettingsMenu()
{
	withBussiness = false;
	inSetting = true;
	buttonPressed = false;
	previousSettingState = -1;
	lcd.noCursor();
  updateMatrix();
}

void menu()
{
	lcd.clear();
	lcd.print("Menu");
	lcd.setCursor(1, 1);
	lcd.print(">");
	lcd.print(menuOptions[currentMenuState]);
  if(currentMenuState != 0)
  {
    lcd.setCursor(LCD_WIDTH - 1,0);
    lcd.write(4);
  }
  if(currentMenuState != menuSize-1)
  {
    lcd.setCursor(LCD_WIDTH - 1,1);
    lcd.write(5);
  }
}


void printIntensity(int length)
{
	lcd.clear();
	lcd.print("- ");
	lcd.setCursor(14, 0);
	lcd.print(" +");
	lcd.setCursor(2, 0);
  updateBrigtness();
	for (byte i = 2; i <= 14; i++)
	{
		if (i - 2 < length)
		{
			lcd.write(255);
		}
		else
		{
			lcd.print(" ");
		}
	}
}

void instructions()
{

  buttonPressed = false;
	lcd.clear();
	lcd.setCursor(1, 0);
	lcd.print("Press or up to jump, down to duck");
	lcd.setCursor(1, 1);
	lcd.print("Avoid obstacles at all cost");
  updateBrigtness();
	for (int positionCount = 0; positionCount < 57; positionCount++)
	{
		lcd.scrollDisplayLeft();
		delay(200);
	}
	delay(10);
	menu();
}

void lcdAtStart()
{
	lcd.clear();
	lcd.setCursor(2, 0);
	lcd.print("Dino Rusher");
	lcd.setCursor(0, 1);
	for (int i = 0; i < LCD_WIDTH; i++)
	{
		lcd.write((uint8_t) 0);
	}

	updateMatrix(greetings);
	delay(2000);
}

void gameLCDdisplay()
{
	lcd.setCursor(0, 0);
  lcd.print("Hi:");
  if(highscores[0] == time)
  {
    playHighscoreAchieved();
  }
  if(highscores[0] > time){
	lcd.print(highscores[0]);
  }else{
    lcd.print(time);
  }
	lcd.setCursor(0, 1);
	lcd.print(time);
  if(time % 100 == 0)
  {
    playIncreaseSong();
  }
}


void showHighscores()
{
  lcd.clear();
  buttonPressed = false;
  int previousY = -1;
  int y;
  while(!buttonPressed){
    y += getYValue();
    if(y < 0)
      y = 0;
    if(y > noOfHighscores-1) 
      y = noOfHighscores -1;
    // Serial.println(y);
    // Serial.println(previousY); 
    if(previousY != y){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(y + 1);
      lcd.print(".");
      lcd.print(highscoresName[y]);
      lcd.print(" scored:");
      lcd.setCursor(0,1);
      lcd.print(highscores[y]);
      updateBrigtness();
    }
    previousY = y;
  }
  delay(10);

  buttonPressed = false;
  menu();
}

void about()
{
	lcd.clear();
	lcd.setCursor(4, 0);
	lcd.print("You play DinoRusher");
	lcd.setCursor(1, 1);
	lcd.print("Find me on GitHub: StefaniaCri");
  updateBrigtness();
	for (int positionCount = 0; positionCount < 25; positionCount++)
	{
		lcd.scrollDisplayLeft();
		delay(300);
	}

	delay(10);
	menu();
}

void enterName()
{
	lcd.clear();
	lcd.setCursor(4, 0);
	lcd.print(settings.playerName);
	lcd.setCursor(4, 0);
	lcd.cursor();
  updateMatrix(helloHand);
  updateBrigtness();

	int positionInName = 0;
	char copyName[5];
	strcpy(copyName, settings.playerName) ;
	// Serial.println(copyName);
	while (!buttonPressed)
	{
		int x = getXValue();
		int y = getYValue();
		if (x != 0)
		{
			positionInName += x;
			if (positionInName > 4)
			{
				positionInName = 4;
			}

			if (positionInName < 0)
			{
				positionInName = 0;
			}

			lcd.setCursor(positionInName + 4, 0);
		}

		if (y != 0)
		{
			copyName[positionInName] += y;

			if (copyName[positionInName] == 'z' + 1)
			{
				copyName[positionInName] = 'a';
			}

			if (copyName[positionInName] == 'a' - 1)
			{
				copyName[positionInName] = 'z';
			}

			lcd.print(copyName[positionInName]);
			lcd.setCursor(positionInName + 4, 0);
		}

		delay(20);
	}

	strcpy(settings.playerName, strcat(copyName,"\0"));
	updateEEPROM();
	goBackToSettingsMenu();
}


void changeBrightness()
{
  //updateMatrix(lantern);
	printIntensity(settings.brightness);
	while (!buttonPressed)
	{
		int xValue = getXValue();
		if (xValue != 0)
		{
			settings.brightness += xValue;
			if (settings.brightness > 12)
			{
				settings.brightness = 12;
			}

			if (settings.brightness < 1)
			{
				settings.brightness = 1;
			}

			printIntensity(settings.brightness);
			analogWrite(LCD_BRIGHTNESS_PIN, map(settings.brightness, 1, 12, 1, 255));
		}
	}
	updateEEPROM();
	analogWrite(LCD_BRIGHTNESS_PIN, map(settings.brightness, 1, 12, 1, 255));
	goBackToSettingsMenu();
	delay(30);
};

void changeDifficulty()
{
  updateMatrix(podium);
	printIntensity(settings.difficulty);
	while (!buttonPressed)
	{
		int xValue = getXValue();
		if (xValue != 0)
		{
			settings.difficulty += xValue * 4;
			if (settings.difficulty > 12)
			{
				settings.difficulty = 12;
			}

			if (settings.difficulty < 4)
			{
				settings.difficulty = 4;
			}

			printIntensity(settings.difficulty);
		}
	}

	updateEEPROM();
	goBackToSettingsMenu();
	delay(30);
};

void changeMatrixBright()
{
	updateMatrix(matrixOn);
	printIntensity(settings.matrixBrightness);
	while (!buttonPressed)
	{
		int xValue = getXValue();
		if (xValue != 0)
		{
			settings.matrixBrightness += xValue;
			if (settings.matrixBrightness > 12)
			{
				settings.matrixBrightness = 12;
			}

			if (settings.matrixBrightness < 1)
			{
				settings.matrixBrightness = 1;
			}

			printIntensity(settings.matrixBrightness);
			lc.setIntensity(0, settings.matrixBrightness);
		}
	}

	updateEEPROM();
	matrixNeedClear = true;
	goBackToSettingsMenu();
	delay(30);
};

void soundON()
{
	lcd.clear();
	lcd.setCursor(1, 0);
	lcd.print("Sound");
  updateBrigtness();
	while (!buttonPressed)
	{
		lcd.setCursor(7, 0);
		int x = getXValue();
		if (x == 1)
			settings.sound = true;
		if (x == -1)
			settings.sound = false;
		if (settings.sound)
			lcd.write(1);
		else lcd.write(2);
    updateBrigtness();
	}

  updateEEPROM(); 
	goBackToSettingsMenu();
	delay(30);
}


void MenuDisplay()
{
  displayMatrixMenu();
	currentMenuState += getYValue();
	if(currentMenuState < 0)
  {
    currentMenuState = 0;
  }
  if(currentMenuState > menuSize-1)
  {
    currentMenuState = menuSize - 1;
  }
	if (currentMenuState != previousMenuState)
	{
		menu();
		playSound();
	}

	if (buttonPressed)
	{
		switch (currentMenuState)
		{
			case 0:
				inMenu = false;
				inGame = true;
				break;
			case 1:
				instructions();
				break;
			case 2:
				showHighscores();
				break;
			case 3:
				inSetting = true;
				inMenu = false;
				break;
			case 4:
				about();
				break;
		}

		buttonPressed = false;
	}

	previousMenuState = currentMenuState;

}

void settingsMenu()
{
  // displayMatrixSettings();
	lcd.clear();
	lcd.print("Settings");
	lcd.setCursor(1, 1);
	lcd.print(">");
	lcd.print(settingsOptions[currentSettingsState]);
   if(currentSettingsState != 0)
  {
    lcd.setCursor(LCD_WIDTH - 1,0);
    lcd.write(4);
  }
  if(currentSettingsState != settingsSize-1)
  {
    lcd.setCursor(LCD_WIDTH - 1,1);
    lcd.write(5);
  }
}


void SettingsDisplay()
{
 
	currentSettingsState += getYValue();
	if(currentSettingsState < 0)
  {
    currentSettingsState = 0;
  }
  if(currentSettingsState > settingsSize-1)
  {
    currentSettingsState = settingsSize - 1;
  }
	if (currentSettingsState != previousSettingState)
	{
		playSound();
		settingsMenu();
	}

	if (buttonPressed)
	{
		withBussiness = true;
		inSetting = false;
		buttonPressed = false;
	}

	previousSettingState = currentSettingsState;

}

void doingBussiness()
{
	switch (currentSettingsState)
	  {
		  case 0:
			  enterName();
			  break;
		  case 1:
			  changeDifficulty();
			  break;
		  case 2:
        Serial.println("pending");
        restartHighscore();
        Serial.println("IM DONE");
        goBackToSettingsMenu();
			  break;
		  case 3:
			  changeBrightness();
			  break;
		  case 4:
			  changeMatrixBright();
			  break;
		  case 5:
			  soundON();
			  break;
		  case 6:
			  inMenu = true;
			  withBussiness = false;
			  previousMenuState = -1;
			  currentSettingsState = 0;
		  	break;
    }   
}
