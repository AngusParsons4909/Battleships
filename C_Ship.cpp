/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2024] Media Design School
File Name : C_Ship.cpp
Description : Class definitions for C_Ship class
Author : Angus Parsons
Mail : Angus.parsons@mds.ac.nz
**************************************************************************/



#include "C_Ship.h"
#include <iostream>

C_Ship::C_Ship(std::string _name) //TF: Constructor
{
	name = _name;
	x = 600;
	y = 600;
	width = 0;
	health = 0;
	rotation = true;
	if (name == "Aircraft Carrier")
	{
		width = 5;
	}
	else if (name == "Battleship")
	{
		width = 4;
	}
	else if (name == "Destroyer")
	{
		width = 3;
	}
	else if (name == "Submarine")
	{
		width = 3;
	}
	else if (name == "Patrol Boat")
	{
		width = 2;
	}
	else
	{
		width = 1;
	}
	health = width;
	for (int i = 0; i < width; i++)
	{
		allx[i] = 0;
		ally[i] = 0;
	}
}


int C_Ship::GetWidth() const
{
	return width;
}

bool C_Ship::GetRotation() const
{
	return rotation;
}

int C_Ship::GetXCoord() const
{
	return x;
}

int C_Ship::GetYCoord() const
{
	return y;
}

std::string C_Ship::GetName() const
{
	return name;
}

int C_Ship::GetHealth() const
{
	return health;
}

int* C_Ship::AllXCoords() const
{
	static int x[5];
	for (int i = 0; i < 5; i++)
	{
		x[i] = allx[i];
	}
	return x;
}

int* C_Ship::AllYCoords() const
{
	static int y[5];
	for (int i = 0; i < 5; i++)
	{
		y[i] = ally[i];
	}
	return y;
}


void C_Ship::SetRotation(bool _rotation)
{
	rotation = _rotation;
}

void C_Ship::SetCoords(int _x, int _y)
{
	x = _x;
	y = _y;
}

void C_Ship::SetName(std::string _name)
{
	name = _name;
}

void C_Ship::SetHealth(int _health)
{
	health = _health;
}

void C_Ship::SetAllCoords()
{
	for (int i = 0; i < width; i++)
	{
		if (rotation)
		{
			allx[i] = x + i;
			ally[i] = y;
		}
		else
		{
			ally[i] = y + i;
			allx[i] = x;
		}
	}
}


void C_Ship::GetEverything() const
{
	std::cout << "Name: " << name << std::endl;
	std::cout << "Width: " << width << std::endl;
	std::cout << "Roatation: " << rotation << std::endl;
	std::cout << "X: " << x << std::endl;
	std::cout << "Y: " << y << std::endl;
	std::cout << "Health: " << health << std::endl;
}