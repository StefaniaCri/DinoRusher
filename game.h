#include "buzzer.h"
#include "globals.h"
#include "joystick.h"
#include "eeprom.h"
#include "Arduino.h"
#pragma once

void initialPlayerPosition(){
  playerHeadXPos = 6;
  playerHeadYPos = 5;
  playerBodyXPos = 7;
  playerBodyYPos = 5;
}

void lostGame()
{
  analogWrite(LCD_BRIGHTNESS_PIN, map(settings.brightness, 1, 12, 1, 255));
  buttonPressed = false;
  lc.clearDisplay(0);
  initialPlayerPosition();
  lcd.clear();
  lcd.print("You achieved:");
  lcd.print(time);
  delay(600);
  updateHighscore(time);
  buttonPressed = false;
  lcd.clear();
  while(!buttonPressed)
  {
    lcd.setCursor(0, 0);
    lcd.print("You beat");
    lcd.setCursor(1, 1);
    lcd.print(betterThanHighscore);
    if(betterThanHighscore == 0)
    {
      lcd.print(":(");
    }	
  }
  betterThanHighscore = 0;
  buttonPressed = false;
  inGame = false;
  inMenu = true;
  previousMenuState = -1;
  firstInLoop = true;
  numberOfLives = 3;
  for(int i = 0; i<chosedLength; i++)
  {
      matrix[chooseObstacle[i].X][chooseObstacle[i].Y] = 0;  
  }
  delay(10);
}

void deletePlayerPosition()
{
  matrix[playerHeadXPos][playerHeadYPos] = 0;
  matrix[playerBodyXPos][playerBodyYPos] = 0;
}

void playerJump(){
  playSound();
  matrix[playerHeadXPos][playerHeadYPos] = 0;
  matrix[playerBodyXPos][playerBodyYPos] = 0;
  playerHeadXPos -= 4;
  playerBodyXPos -= 4;
}

void playerDuck()
{
  playSound();
  matrix[playerHeadXPos][playerHeadYPos] = 0;
  playerHeadXPos += 1;
  playerHeadYPos -= 1;
}


void chooseNewObstacle(){
  int numberOfObstacles = 6;
  if(settings.difficulty == 12)
  {
    numberOfObstacles = 7;
  }

  int rand = random(1,numberOfObstacles);
 
  switch (rand) {
  case 1:
   
    for(int i = 0; i<obstacleOneLength; i++)
    {
      chooseObstacle[i].X = obstacle_one[i].X;
      chooseObstacle[i].Y = obstacle_one[i].Y;
      matrix[chooseObstacle[i].X][chooseObstacle[i].Y] = 1;  
    }
    chosedLength = obstacleOneLength;
    break;
  case 2:
  
    for(int i = 0; i<obstacleTwoLength; i++)
    {
      chooseObstacle[i].X = obstacle_two[i].X;
      chooseObstacle[i].Y = obstacle_two[i].Y;
      matrix[chooseObstacle[i].X][chooseObstacle[i].Y] = 1;  
    }
    chosedLength = obstacleTwoLength;
    break;
  case 3:
   
    for(int i = 0; i<obstacleThreeLength; i++)
    {
      chooseObstacle[i].X = obstacle_three[i].X;
      chooseObstacle[i].Y = obstacle_three[i].Y;
      matrix[chooseObstacle[i].X][chooseObstacle[i].Y] = 1;  
    }
    chosedLength = obstacleThreeLength;
    break;
  case 4:
   
    for(int i = 0; i<obstacleFourLength; i++)
    {
      chooseObstacle[i].X = obstacle_four[i].X;
      chooseObstacle[i].Y = obstacle_four[i].Y;
      matrix[chooseObstacle[i].X][chooseObstacle[i].Y] = 1;  
    }
    chosedLength = obstacleFourLength;
    break;  
  case 5:
  
    for(int i = 0; i<obstacleFiveLength; i++)
    {
      chooseObstacle[i].X = obstacle_five[i].X;
      chooseObstacle[i].Y = obstacle_five[i].Y;
      matrix[chooseObstacle[i].X][chooseObstacle[i].Y] = 1;  
    }
    chosedLength = obstacleFiveLength;
    break;    
  case 6:
  
    for(int i = 0; i<specialObstacleHardModeLength; i++)
    {
      chooseObstacle[i].X = specialObstacleHardMode[i].X;
      chooseObstacle[i].Y = specialObstacleHardMode[i].Y;
      matrix[chooseObstacle[i].X][chooseObstacle[i].Y] = 1;  
    }
    chosedLength = specialObstacleHardModeLength;
    break;    
  }
}

void generateObstacle()
{
  if(shownObstacle)
    return;
  shownObstacle = true;
  chooseNewObstacle();
}


int dificultyGeneratingObstacleTime()
{
  if(settings.difficulty == 4)
    return 150;
  if(settings.difficulty ==  8){
    if(time <= 250)
      return 170;
    if(time >= 250 && time <= 500)
      return 150;
    if(time >= 500 && time <= 750)
      return 125;
    if(time > 750)
      return 100;        
  }
  if(settings.difficulty ==  12){
    if(time <= 150)
      return 200;
    if(time >= 150 && time <= 300)
      return 170;
    if(time >= 300 && time <= 500)
      return 150;
    if(time >= 500 && time <= 650)
      return 125;
    if(time >= 650 && time <= 800)
      return 100;
    if(time >= 650 && time <= 800)
      return 90;
    if(time > 1000)
      return 80;    
  }
}
unsigned long delayTillNextObstacle = 0;
int delayed = 150;
void moveObstacle()
{
  if(millis() - lastDelayObstacle > delayed && shownObstacle)
  {
    for(int i = 0; i<chosedLength; i++)
    {
      matrix[chooseObstacle[i].X][chooseObstacle[i].Y] = 0;  
    }
    for(int i = 0; i<chosedLength; i++)
    {
      chooseObstacle[i].Y += 1; 
    }
   if(chooseObstacle[0].Y  > matrixSize)
    {
      shownObstacle = false;
      return;
    }
    for(int i = 0; i<chosedLength; i++)
    {
      matrix[chooseObstacle[i].X][chooseObstacle[i].Y] = 1;  
    }
    delayed = dificultyGeneratingObstacleTime();
    lastDelayObstacle = millis();  
  }
}
void touchObstacle()
{
  for(int i = 0; i<chosedLength; i++)
  {
    
    if((chooseObstacle[i].X == playerHeadXPos && chooseObstacle[i].Y == playerHeadYPos) || 
      (chooseObstacle[i].X == playerBodyXPos && chooseObstacle[i].Y == playerBodyYPos))
    {
      lostGame();
    }  
  }
 
}


void changeMatrix(){

	for (int col = 0; col < matrixSize; col++)
	{
		for (int row = 0; row < matrixSize; row++)
		{
			lc.setLed(0, row, col, abs(matrix[row][col]-1));
		}
	}

}

void updatePositions()
{
  int yValue = getYValue();
  if((buttonPressed || yValue == -1) && !inMotion)
  {
    playerJump();
    lastMove = millis();
    buttonPressed = false;
    inMotion = true;
  }

  if(yValue == 1 && !inMotion)
  {
    playerDuck();
    lastMove = millis();
    buttonPressed = false;
    inMotion = true;
  }
  
  if(millis() - lastMove > delayTillNextMove && inMotion)
  {
    deletePlayerPosition();
    initialPlayerPosition();
    inMotion = false;
  }
  
  matrix[playerHeadXPos][playerHeadYPos] = 1;
  matrix[playerBodyXPos][playerBodyYPos] = 1;
  if(time >= 51 && time % 350 >= 0 && time % 350 <= 50 && settings.difficulty == 12){
    changeMatrix();
  }else if(time >= 51 && time % 700 >= 0 && time % 700 <= 50 && settings.difficulty == 8){
    changeMatrix();
  }else{
    updateMatrix();
  }
}

void game() {
  generateObstacle();
  moveObstacle();
  if (millis() - lastMoved > moveInterval)
	{
		// game logic
    // update the matrix, player duck and jump 
		updatePositions();
		lastMoved = millis();
	}
  touchObstacle();
  if (millis() - numberOfsec >= 100)
	{
		time++;
		numberOfsec = millis();
	}
  // Serial.println(time);
}

