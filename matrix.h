#include "globals.h"
#include "drawingsForMatrix.h"
#pragma once

void updateMatrix(byte matrix[matrixSize][matrixSize] = matrix)
{
	for (int col = 0; col < matrixSize; col++)
	{
		for (int row = 0; row < matrixSize; row++)
		{
			lc.setLed(0, row, col, matrix[row][col]);
		}
	}
}

void matrixClear()
{
	if (matrixNeedClear)
		lc.clearDisplay(0);
}

void displayMatrixMenu()
{
  switch(currentMenuState)
  {
    case 0:
      updateMatrix(greetings);
      break;
    case 1:
      updateMatrix(question);
      break;
    case 2:
      updateMatrix(cup);
      break;
    case 3:
      updateMatrix(tools);
      break;
    case 4:
      updateMatrix(happyFace);
      break;    
  }
}

void displayMatrixSettings()
{
  switch(currentSettingsState)
  {
    case 0:
      updateMatrix(helloHand);
      break;
    case 1:
      updateMatrix(podium);
      break;
    case 2:
      updateMatrix(reload);
      break;
    case 3:
      updateMatrix(lantern);
      break;
    case 4:
      updateMatrix(matrixOn);
      break;
    case 5:
      updateMatrix(audio);
      break;
    case 6:
      updateMatrix(back);
      break;        
  }
}