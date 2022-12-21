#pragma once
#include "EEPROM.h"
#include "globals.h"

void readHighscoreEEPROM()
{
	unsigned int positionInMemory = sizeof(settings);
	EEPROM.get(positionInMemory, highscores);
  positionInMemory += sizeof(highscores);
  EEPROM.get(positionInMemory + 1, highscoresName);
}



void readFromEEPROM()
{
	unsigned int positionInMemory = 0;
	EEPROM.get(positionInMemory, settings);
}

void updateEEPROM()
{
	unsigned int positionInMemory = 0;
	EEPROM.put(positionInMemory, settings);
}

void updateHighscoreEEPROM()
{
	unsigned int positionInMemory = sizeof(settings);
	EEPROM.put(positionInMemory, highscores);
  positionInMemory += sizeof(highscores);
  EEPROM.put(positionInMemory + 1, highscoresName);
  Serial.println("updating");
}

void updateHighscore(int score)
{
  if(score > highscores[0])
  {
    betterThanHighscore = 5;
    highscores[4] = highscores[3];
    strcpy(highscoresName[4], highscoresName[3]);
    highscores[3] = highscores[2];
    strcpy(highscoresName[3], highscoresName[2]);
    highscores[2] = highscores[1];
    strcpy(highscoresName[2], highscoresName[1]);
    highscores[1] = highscores[0];
    strcpy(highscoresName[1], highscoresName[0]);
    highscores[0] = score;
    strcpy(highscoresName[0], settings.playerName);
  }else if(score > highscores[1])
  {
    betterThanHighscore = 4;
    highscores[4] = highscores[3];
    strcpy(highscoresName[4], highscoresName[3]);
    highscores[3] = highscores[2];
    strcpy(highscoresName[3], highscoresName[2]);
    highscores[2] = highscores[1];
    strcpy(highscoresName[2], highscoresName[1]);
    highscores[1] = score;
    strcpy(highscoresName[1], settings.playerName);
  }else if(score > highscores[2])
  { 
    betterThanHighscore = 3;
  	highscores[4] = highscores[3];
    strcpy(highscoresName[4], highscoresName[3]);
    highscores[3] = highscores[2];
    strcpy(highscoresName[3], highscoresName[2]);
    highscores[2] = score;
    strcpy(highscoresName[2], settings.playerName);
  }else if(score > highscores[3])
  {
    betterThanHighscore = 2;
    highscores[4] = highscores[3];
    strcpy(highscoresName[4], highscoresName[3]);
    highscores[3] = score;
    strcpy(highscoresName[3], settings.playerName);
  }else if(score>highscores[4])
  {
    betterThanHighscore = 1;
    highscores[4] = score;
    strcpy(highscoresName[4], settings.playerName);
  }
  updateHighscoreEEPROM();
}

void restartHighscore()
{  
  lcd.clear();
  lcd.print("Reseting..");
  Serial.println("reset");
  highscores[0] = 0;
  highscores[1] = 0;
  highscores[2] = 0;
  highscores[3] = 0;
  highscores[4] = 0;
  strcpy(highscoresName[0], "Name\0");
  strcpy(highscoresName[1], "Name\0");
  strcpy(highscoresName[2], "Name\0");
  strcpy(highscoresName[3], "Name\0");
  strcpy(highscoresName[4], "Name\0");
  updateHighscoreEEPROM();
}

