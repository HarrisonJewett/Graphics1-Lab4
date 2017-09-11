#pragma once
#include "RasterSurface.h"
#include "shader.h"

//testing
#include <iostream>
using namespace std;
//endTesting

void parametricAlgorithm(unsigned int startX, unsigned int startY, unsigned int finalX, unsigned int finalY, unsigned int startColor, unsigned int finalColor);
unsigned int interpColors(unsigned int sourceColor, unsigned int desColor, float ratio);
void colorToScreen(unsigned int x, unsigned int y, unsigned int color);
void clearBuffer(unsigned int color);
void drawLine(const vec4f& v1, const vec4f& v2);

void parametricAlgorithm(unsigned int startX, unsigned int startY, unsigned int finalX, unsigned int finalY, unsigned int startColor, unsigned int finalColor)
{
	int deltaX = abs((int)finalX - (int)startX);
	int deltaY = abs((int)finalY - (int)startY);
	int longest = (deltaX > deltaY) ? deltaX : deltaY;

	for (int i = 0; i < longest; i++)
	{
		float ratio = i / (float)longest;
		int currX = ((int)finalX - (int)startX) * ratio + (int)startX;
		int currY = ((int)finalY - (int)startY) * ratio + (int)startY;
		unsigned int colorToDraw = interpColors(startColor, finalColor, ratio);
		if (PixelShader)
		{
			PixelShader(colorToDraw);
		}
		colorToScreen(currX, currY, colorToDraw);
	}
}

unsigned int interpColors(unsigned int sourceColor, unsigned int desColor, float ratio)
{
	//(b - a)*r + a

	//ARGB
	int r = (sourceColor & 0x00FF0000) >> 16;
	int g = (sourceColor & 0x0000FF00) >> 8;
	int b = (sourceColor & 0x000000FF);

	int newR = (desColor & 0x00FF0000) >> 16;
	int newG = (desColor & 0x0000FF00) >> 8;
	int newB = (desColor & 0x000000FF);

	int finalR = (int)((newR - r) * (ratio)+r);
	int finalG = (int)((newG - g) * (ratio)+g);
	int finalB = (int)((newB - b) * (ratio)+b);

	return((finalR << 16) | (finalG << 8) | finalB);
}

void colorToScreen(unsigned int x, unsigned int y, unsigned int color)
{
	if (x > REZ_X || y > REZ_Y) {}
	else
		myArray[convertCoor(x, y)] = color;
}

void clearBuffer(unsigned int color)
{
	for (unsigned int i = 0; i < (REZ_X * REZ_Y); ++i)
		myArray[i] = color;
}

void drawLine(const vec4f& v1, const vec4f& v2)
{
	vec4f temp1 = v1;
	vec4f temp2 = v2;

	if (VertexShader)
	{
		VertexShader(temp1);
		VertexShader(temp2);
	}

	parametricAlgorithm(convertNDCX(temp1.x), convertNDCY(temp1.y), convertNDCX(temp2.x), convertNDCY(temp2.y), 0x0000F000, 0xFF00FF00);

}