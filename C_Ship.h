/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2024] Media Design School
File Name : C_Ship.h
Description : Class declaration of C_Ship class
Author : Angus Parsons
Mail : Angus.parsons@mds.ac.nz
**************************************************************************/


#pragma once
class C_Ship //TF: Class
{
public: //TF: Access Specifier
	C_Ship(std::string _name); 

	void SetRotation(bool _rotation);
	void SetCoords(int _x, int _y);
	void SetName(std::string _name);
	void SetHealth(int _health);
	void SetAllCoords();

	int GetWidth() const; //TF: Constant
	bool GetRotation() const;
	int GetXCoord() const; //TF: Variable Type
	int GetYCoord() const;
	std::string GetName() const;
	int GetHealth() const;
	int* AllXCoords() const;
	int* AllYCoords() const;

	void GetEverything() const;
private:
	int width;
	bool rotation; //true is vertical false is horizontal
	std::string name;
	int x;
	int y;
	int health; //same as length but able to be manipulated
	int allx[5];
	int ally[5];
};