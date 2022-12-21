#include "WString.h"
#pragma once
#include <LiquidCrystal.h>
#include <LedControl.h>
//constants for LCD
const int LCD_WIDTH = 16;
const int LCD_HEIGHT = 2;
const byte rs = 9;
const byte en = 8;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 5;
const byte d7 = 4;
const int LCD_BRIGHTNESS_PIN = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//constants for Matrix
const int dinPin = 12;
const int clockPin = A2;
const int loadPin = 10;
const int xPin = A0;
const int yPin = A1;
int magicSeedNumbber = 43;
LedControl lc = LedControl(dinPin, clockPin, loadPin, 1);	// DIN, CLK,LOAD, No. DRIVER
bool matrixNeedClear = false;
const byte matrixSize = 8;
const int minThreshold = 400;
const int maxThreshold = 600;

//constants for Buzzer
const int buzzerPin = 13;

//constants for Joystick
const int pinX = A0;
const int pinY = A1;
const int pinSW = 2;
bool joyMovedX = false, joyMovedY = false;

//constants for Menu
int currentMenuState = 0;
int previousMenuState = -1;
int currentSettingsState = 0;
int previousSettingState = -1;
const int menuSize = 5;
const int settingsSize = 7;
const String menuOptions[menuSize] = { "Start game", "How to play", "Highscores", "Settings", "About" };

const String settingsOptions[settingsSize] = { "Enter name", "Difficulty","Reset highscr", "LCD Brightness", "Mtrx Brightness", "Sounds","Back" };

bool inMenu = true;
bool inSetting = false;
bool inGame = false;
bool withBussiness = false;

//constants for Game
int numberOfLives = 3;
unsigned long long lastMoved = 0;
const byte moveInterval = 100;
unsigned long numberOfsec = 0;
int playerHeadXPos = 6;
int playerHeadYPos = 5;
int playerBodyXPos = 7;
int playerBodyYPos = 5;
bool inMotion = false;
unsigned long delayTillNextMove = 400;
unsigned long lastMove = 0;
bool shownObstacle = false;
int obstacleX = 7;
int obstacleY = 7;
int betterThanHighscore = 0;
struct obstaclesPosition{
  int X;
  int Y;
}obstacle_one[10] = {
  {7,0},{6,0},{7,1}
},obstacle_two[10]={
  {7,0}
},obstacle_three[10]={
  {7,0},{6,0}
},obstacle_four[10]={
  {7,0}
},obstacle_five[10]={
  {5,0}
},specialObstacleHardMode[10]={
  {6,0},{5,0},{4,0},{3,0},{2,0},{1,0},{0,0}
},chooseObstacle[10];

int obstacleOneLength = 3;
int obstacleTwoLength = 1;
int obstacleThreeLength = 2;
int obstacleFourLength = 1;
int obstacleFiveLength = 1;
int specialObstacleHardModeLength = 7;
int chosedLength;

unsigned long delayObstacle = 150;
unsigned long lastDelayObstacle = 0;
int time = 0;
//other constants
struct{
	int brightness;
	int matrixBrightness;
	int difficulty;
	int idThemeSong;
	bool sound;
	char playerName[6];
} settings;

int noOfHighscores = 5;
int highscores[6];
char highscoresName[6][6];

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
byte buttonState = HIGH;
int buttonReading;
unsigned long timer = 0;
bool buttonPressed = false;
bool firstInLoop = true;

unsigned long lastScrollToLeft = 0;
const int delayTime = 200; 
