/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [2024] Media Design School
File Name : Main.cpp
Description : Main function for console window 
Author : Angus Parsons
Mail : Angus.parsons@mds.ac.nz
**************************************************************************/


#include <iostream>
#include "C_Ship.h"
#include <Windows.h>

//clear the screen
void ClearScreen()
{
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);
}

//prints desired grid to screen
void ShowGrid(char _Grid[10][10])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (_Grid[j][i] == '^')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
			}
			if (_Grid[j][i] == '~')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			}
			if (_Grid[j][i] == 'X')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			}
			std::cout << _Grid[j][i] << " ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

//use arrow keys / WASD to select a location on grid
void SelectLocation(char _Grid[10][10], int* _PCurrentX, int* _PCurrentY, C_Ship _Object[5], int id, char _PlayerGrid[10][10])
{
	char Cursor = '*';
	if (_Object[id].GetName() != "GameShip")
	{
		Cursor = '>';
	}
	int X = 0;
	int Y = 0;
	while (true) //TF: Iteration Structure
	{
		if (_Grid[X][Y] != '~' and X < 9) //TF: Logical Operator
		{
			X++; //TF: Arithmetic Operator
		}
		else if (_Grid[X][Y] != '~') //TF: Relational Operator
		{
			X = 0;
			Y++;
		}
		else
		{
			break;
		}
	}

	char Current = _Grid[X][Y];
	char Previous = _Grid[X][Y];
	_Grid[X][Y] = Cursor;
	bool RotationState = true; //TF: Default Parameter

	std::string Message = "";
	if (_Object[id].GetName() != "GameShip") //TF: Conditional Statement
	{
		Message = "Rotation is Horizontal";
	}

	ClearScreen();
	std::cout << Message << std::endl;
	ShowGrid(_Grid);
	ShowGrid(_PlayerGrid);

	while (!GetAsyncKeyState(VK_SPACE))
	{
		if (GetAsyncKeyState(VK_SHIFT) and _Object[id].GetName() != "GameShip")
		{
			Sleep(100);
			if (RotationState == false)
			{
				RotationState = true;
				Message = "Rotation is Horizontal";
				Cursor = '>';
			}
			else
			{
				RotationState = false;
				Message = "Rotation is Vertical";
				Cursor = 'v';
			}
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (_Grid[j][i] == '>' or _Grid[j][i] == 'v')
					{
						_Grid[j][i] = Cursor;
					}
				}
			}
			ClearScreen();
			_Object[id].SetRotation(RotationState);
			std::cout << Message << std::endl;
			ShowGrid(_Grid);
			ShowGrid(_PlayerGrid);
		}
		if ((GetAsyncKeyState(VK_RIGHT) or GetAsyncKeyState(0x44)) and X < 9) //right or D
		{
			if (_Grid[X + 1][Y] != '0' and _Grid[X + 1][Y] != 'O')
			{
				Previous = Current;
				Current = _Grid[X + 1][Y];
				X++;
				_Grid[X][Y] = Cursor;
				_Grid[X - 1][Y] = Previous;
			}
			else if (_Grid[X + 2][Y] != '0' and _Grid[X + 2][Y] != 'O' and X < 8)
			{
				Previous = Current;
				Current = _Grid[X + 2][Y];
				X = X + 2;
				_Grid[X][Y] = Cursor;
				_Grid[X - 2][Y] = Previous;
			}
			ClearScreen();
			std::cout << Message << std::endl;
			ShowGrid(_Grid);
			ShowGrid(_PlayerGrid);
		}
		else if ((GetAsyncKeyState(VK_LEFT) or GetAsyncKeyState(0x41)) and X > 0) //left or A
		{
			if (_Grid[X - 1][Y] != '0' and _Grid[X - 1][Y] != 'O')
			{
				Previous = Current;
				Current = _Grid[X - 1][Y];
				X--;
				_Grid[X][Y] = Cursor;
				_Grid[X + 1][Y] = Previous;
			}
			else if (_Grid[X - 2][Y] != '0' and _Grid[X - 2][Y] != 'O' and X > 1)
			{
				Previous = Current;
				Current = _Grid[X - 2][Y];
				X = X - 2;
				_Grid[X][Y] = Cursor;
				_Grid[X + 2][Y] = Previous;
			}
			ClearScreen();
			std::cout << Message << std::endl;
			ShowGrid(_Grid);
			ShowGrid(_PlayerGrid);
		}
		else if ((GetAsyncKeyState(VK_UP) or GetAsyncKeyState(0x57)) and Y > 0) //up or W
		{
			if (_Grid[X][Y - 1] != '0' and _Grid[X][Y - 1] != 'O')
			{
				Previous = Current;
				Current = _Grid[X][Y - 1];
				Y--;
				_Grid[X][Y] = Cursor;
				_Grid[X][Y + 1] = Previous;
			}
			else if (Y > 1 and _Grid[X][Y - 2] != '0' and _Grid[X][Y - 2] != 'O')
			{
				Previous = Current;
				Current = _Grid[X][Y - 2];
				Y = Y - 2;
				_Grid[X][Y] = Cursor;
				_Grid[X][Y + 2] = Previous;
			}
			ClearScreen();
			std::cout << Message << std::endl;
			ShowGrid(_Grid);
			ShowGrid(_PlayerGrid);
		}
		else if ((GetAsyncKeyState(VK_DOWN) or GetAsyncKeyState(0x53)) and Y < 9) //down or S
		{
			if (_Grid[X][Y + 1] != '0' and _Grid[X][Y + 1] != 'O')
			{
				Previous = Current;
				Current = _Grid[X][Y + 1];
				Y++;
				_Grid[X][Y] = Cursor;
				_Grid[X][Y - 1] = Previous;
			}
			else if (_Grid[X][Y + 2] != '0' and _Grid[X][Y + 2] != 'O' and Y < 8)
			{
				Previous = Current;
				Current = _Grid[X][Y + 2];
				Y = Y + 2;
				_Grid[X][Y] = Cursor;
				_Grid[X][Y - 2] = Previous;
			}
			ClearScreen();
			std::cout << Message << std::endl;
			ShowGrid(_Grid);
			ShowGrid(_PlayerGrid);
		}
		Sleep(100);
	}
	Sleep(150); //jank but works (waits a bit so that the escape key is no longer pressed so inputs dont get added multiple times
	*_PCurrentX = X;
	*_PCurrentY = Y;
	_Grid[X][Y] = Current;
}

int CheckShipSunk(C_Ship _Object[5], int _X, int _Y)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (_Object[i].AllXCoords()[j] == _X and _Object[i].AllYCoords()[j] == _Y) //either all x coords are identical or all y coords so we can use j for both
			{
				_Object[i].SetHealth(_Object[i].GetHealth() - 1);
				return i;
			}
		}
	}
	return 0;
}

//checks if the given location is valid
bool CheckValidCoords(C_Ship _Object[5], int id, int _X, int _Y, char _Grid[10][10])
{
	if (_Object[id].GetRotation())
	{
		if (_Object[id].GetWidth()-1 + _X < 10)
		{
			for (int p = 0; p < (_Object[id].GetWidth()); p++)
			{
				if (_Grid[_X + p][_Y] == '0' or _Grid[_X + p][_Y] == 'O')
				{
					return false;
				}
			}
			for (int i = 0; i < (_Object[id].GetWidth()); i++)
			{
				_Grid[_X + i][_Y] = '0';
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (_Object[id].GetWidth() + _Y > 0 and _Object[id].GetWidth()-1 + _Y < 10)
		{
			for (int j = 0; j < (_Object[id].GetWidth()); j++)
			{
				if (_Grid[_X][_Y + j] == '0' or _Grid[_X][_Y + j] == 'O')
				{
					return false;
				}
			}
			for (int j = 0; j < (_Object[id].GetWidth()); j++)
			{
				_Grid[_X][_Y + j] = '0';
			}
			
		}
		else
		{
			return false;
		}
	}
	_Grid[_X][_Y] = 'O';
	_Object[id].SetCoords(_X, _Y);
	return true;
}

//prompts user to place ship using SelectLocation to choose location
void PlaceShip(C_Ship _Object[5], int id, char _Grid[10][10], int* _X, int* _Y, char _PlayerGrid[10][10])
{
	while (true)
	{
		ClearScreen();
		std::cout << "Place " << _Object[id].GetName() << " (Length: " << _Object[id].GetWidth() << "): " << std::endl;
		Sleep(2000);
		SelectLocation(_Grid, _X, _Y, _Object, id, _PlayerGrid);
		if (CheckValidCoords(_Object, id, *_X, *_Y, _Grid))
		{
			_Object[id].SetCoords(*_X, *_Y);
			break;
		}
		else
		{
			ClearScreen();
			std::cout << "Those coordinates are out of range" << std::endl;
		}
	}
}

//selects random place for AI ships
void PlaceAIShip(C_Ship _Object[5], int id, char _Grid[10][10])
{
	int Width = _Object[id].GetWidth();
	int Rotation = (rand() % 2);
	int MaxX = 0;
	int MaxY = 0;
	if (Rotation)
	{
		MaxX = 9 - Width;
		MaxY = 9;
		_Object[id].SetRotation(true);
	}
	else
	{
		MaxY = 9 - Width;
		MaxX = 9;
		_Object[id].SetRotation(false);
	}
	while (true)
	{
		int X = rand() % MaxX;
		int Y = rand() % MaxY;
		bool Valid = CheckValidCoords(_Object, id, X, Y, _Grid);
		if (Valid)
		{
			_Object[id].SetCoords(X, Y);
			break;
		}
	}
}

//uses select location to shoot at enemy ships
void Fire(C_Ship _Object[5], int GameShipID, C_Ship _EnemyObject[5], char _PlayerEnemyGrid[10][10], char _EnemyGrid[10][10], int* _X, int* _Y, int* _EnemyHealth, char _PlayerOwnGrid[10][10], char _AlreadyShot[10][10])
{
	while (true)
	{
		SelectLocation(_PlayerEnemyGrid, _X, _Y, _Object, GameShipID, _PlayerOwnGrid);
		if (_AlreadyShot[*_X][*_Y] != 'X')
		{
			if (_EnemyGrid[*_X][*_Y] == '0' or _EnemyGrid[*_X][*_Y] == 'O' or _EnemyGrid[*_X][*_Y] == 'X')
			{
				std::cout << "Hit!" << std::endl;
				_PlayerEnemyGrid[*_X][*_Y] = 'X';
				_EnemyGrid[*_X][*_Y] = 'X';
				*_EnemyHealth = *_EnemyHealth - 1;
				_AlreadyShot[*_X][*_Y] = 'X';
				int SunkShip = CheckShipSunk(_EnemyObject, *_X, *_Y);
				if (_EnemyObject[SunkShip].GetHealth() < 1)
				{
					std::cout << "Enemy " << _EnemyObject[SunkShip].GetName() << " was sunk" << std::endl;
					system("Pause");
				}
				break;
			}
			else
			{
				std::cout << "Miss!" << std::endl;
				_PlayerEnemyGrid[*_X][*_Y] = '^';
				_EnemyGrid[*_X][*_Y] = '^';
				_AlreadyShot[*_X][*_Y] = 'X';
				break;
			}
		}
	}
}

//shoots randomly at player
void FireAI(char _EnemyDebugGrid[10][10], char _PlayerGrid[10][10], int* _PlayerHealth, C_Ship _PlayerObject[5])
{
	while (true)
	{
		if (*_PlayerHealth <= 0)
		{
			break;
		}
		int X = rand() % 10; //Psuedo Random Number
		int Y = rand() % 10;
		if (_EnemyDebugGrid[X][Y] == '~')
		{
			if (_PlayerGrid[X][Y] == '0' or _PlayerGrid[X][Y] == 'O')
			{
				_EnemyDebugGrid[X][Y] = 'X';
				_PlayerGrid[X][Y] = 'X';
				*_PlayerHealth = *_PlayerHealth - 1;
				int SunkShip = CheckShipSunk(_PlayerObject, X, Y);
				std::cout << "Hit " << _PlayerObject[SunkShip].GetName() << "!" << std::endl;
				if (_PlayerObject[SunkShip].GetHealth() < 1)
				{
					std::cout << "Your " << _PlayerObject[SunkShip].GetName() << " was sunk" << std::endl;
					system("Pause");
				}
				break;
			}
			else if (_PlayerGrid[X][Y] == '~')
			{
				_EnemyDebugGrid[X][Y] = '^';
				_PlayerGrid[X][Y] = '^';
				std::cout << "Enemy Missed!" << std::endl;
				break;
			}
		}
	}
}

void ShowMenu(std::string _Grid[5], bool* _RandomShipLocations, bool* _DebugMode);

void ShowControls(std::string _Grid[5], bool* _RandomShipLocations, bool* _DebugMode)
{
	Sleep(200);
	while (!GetAsyncKeyState(VK_SPACE))
	{
		ClearScreen();
		std::cout << "Controls: " << std::endl;
		std::cout << "Move Cursor:   w" << std::endl;
		std::cout << "             a s d     (or arrow keys)" << std::endl;
		std::cout << "Confirm Position: Space" << std::endl;
		std::cout << "Rotate Ship: Shift" << std::endl;
		std::cout << std::endl;

		std::cout << "\"Randomize Ships\" Toggles if ships are placed randomly" << std::endl;
		std::cout << "\"Debug Mode\" Toggles the debug mode" << std::endl;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		std::cout << "Close" << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		Sleep(100);
	}
	ClearScreen();
	ShowMenu(_Grid, _RandomShipLocations, _DebugMode);
}

void ShowMenu(std::string _Grid[5], bool* _RandomShipLocations, bool* _DebugMode)
{
	bool Begin = false;
	while (!Begin)
	{
		Sleep(300);
		int CurrPos = 0;
		while (!GetAsyncKeyState(VK_SPACE))
		{
			if (GetAsyncKeyState(VK_UP) or GetAsyncKeyState(0x57)) //up or W
			{
				CurrPos -= 1;
			}
			else if (GetAsyncKeyState(VK_DOWN) or GetAsyncKeyState(0x53)) //down or S
			{
				CurrPos += 1;
			}

			if (CurrPos < 0)
			{
				CurrPos = 0;
			}
			else if (CurrPos > 4)
			{
				CurrPos = 4;
			}

			ClearScreen();
			for (int i = 0; i < 5; i++)
			{
				if (i == CurrPos)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
					if (CurrPos == 1 and *_RandomShipLocations)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 29);
					}	
					if (CurrPos == 2 and *_DebugMode)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 29);
					}
				}
				if (i == 1 and *_RandomShipLocations and CurrPos !=1)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
				}
				if (i == 2 and *_DebugMode and CurrPos !=2)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
				}
				std::cout << _Grid[i] << std::endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			std::cout << std::endl;
			Sleep(100);
		}
		switch (CurrPos)
		{
		case 0:
			Begin = true;
			break;
		case 1:
			*_RandomShipLocations = !*_RandomShipLocations;
			break;
		case 2:
			*_DebugMode = !*_DebugMode; //TF: Pointer Deferenced
			break;
		case 3:
			ShowControls(_Grid, _RandomShipLocations, _DebugMode);
			break;
		case 4:
			exit(0);
			break;
		}
	}
}


int main()
{
	bool Again = true;
	while (Again)
	{
		Sleep(100);
		srand((unsigned int)time(0));
		char PlayerOwnGrid[10][10] =
		{
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'}
		};
		char PlayerEnemyGrid[10][10] =   //TF: Array
		{
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'}
		};
	 
		char EnemyGrid[10][10] =
		{
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'}
		};

		char EnemyGridForDebug[10][10] =
		{
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'},
			{'~','~','~','~','~','~','~','~','~','~'}
		};

		char InvisGrid[10][10] =
		{
			{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
			{' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
		};

		char AlreadyShot[10][10];

		std::string Arr[5] = //TF: Dynamic Memory (apparently)
		{
			"Begin",
			"Randomize Ships",
			"Debug Mode",
			"Show Controls",
			"Quit"
		};
	
		//Define all player ships
		C_Ship PlayerAircraftCarrier("Aircraft Carrier"); //TF: Class Instance
		C_Ship PlayerBattleship("Battleship");
		C_Ship PlayerDestroyer("Destroyer");
		C_Ship PlayerSubmarine("Submarine");
		C_Ship PlayerPatrolBoat("Patrol Boat");

		C_Ship AllPlayerShips[5] = { PlayerAircraftCarrier,PlayerBattleship,PlayerDestroyer,PlayerSubmarine,PlayerPatrolBoat };
	
		//define all ai ships
		C_Ship AIAircraftCarrier("Aircraft Carrier");
		C_Ship AIBattleship("Battleship");
		C_Ship AIDestroyer("Destroyer");
		C_Ship AISubmarine("Submarine");
		C_Ship AIPatrolBoat("Patrol Boat");

		C_Ship AllAIShips[5] = { AIAircraftCarrier,AIBattleship,AIDestroyer,AISubmarine,AIPatrolBoat };

		//has no width for use in fire()
		C_Ship GameShip("GameShip");
		C_Ship GameShipArr[5] = { GameShip,GameShip,GameShip,GameShip,GameShip };

		//current position on boards
		int CurrentX = 0;
		int CurrentY = 0;
		int* PCurrentX = &CurrentX; //TF: Pointer Initialised
		int* PCurrentY = &CurrentY;

		bool RandomShipLocations = false;
		bool DebugMode = false;

		bool* PRandomShipLocations = &RandomShipLocations;
		bool* PDebugMode = &DebugMode;
	
		//Show Menu
		std::cout << "(Move Cursor with WASD/Arrow Keys and Space to Confirm Position)" << std::endl;
		system("Pause");
		ClearScreen();

		ShowMenu(Arr, PRandomShipLocations, PDebugMode);

		if (!RandomShipLocations)
		{
			//place own ships
			for (int i = 0; i < 5; i++)
			{
				PlaceShip(AllPlayerShips, i, PlayerOwnGrid, PCurrentX, PCurrentY, InvisGrid);
				AllPlayerShips[i].SetAllCoords();
			}
		}
		else
		{
			//Randomly place player ships
			for (int i = 0; i < 5; i++)
			{
				PlaceAIShip(AllPlayerShips, i, PlayerOwnGrid);
				AllPlayerShips[i].SetAllCoords();
			}
		}

		//place AI ships
		for (int i = 0; i < 5; i++)
		{
			PlaceAIShip(AllAIShips, i, EnemyGrid);
			AllAIShips[i].SetAllCoords();
		}


		//start game

		//initialise end condition
		int PlayerHealth = PlayerAircraftCarrier.GetHealth() + PlayerBattleship.GetHealth() + PlayerDestroyer.GetHealth() + PlayerSubmarine.GetHealth() + PlayerPatrolBoat.GetHealth();
		int AIHealth = AIAircraftCarrier.GetHealth() + AIBattleship.GetHealth() + AIDestroyer.GetHealth() + AISubmarine.GetHealth() + AIPatrolBoat.GetHealth();

		int* PPlayerHealth = &PlayerHealth;
		int* PAIHealth = &AIHealth;

		Sleep(100); //catch any inputs from menu
		while (PlayerHealth > 0 and AIHealth > 0)
		{
			if (DebugMode)
			{
				ClearScreen();
				std::cout << "Enemy Ships:" << std::endl;
				ShowGrid(EnemyGrid);
				std::cout << "Enemy Shots:" << std::endl;
				ShowGrid(EnemyGridForDebug);
				system("Pause");
			}
			//player fires
			ClearScreen();
			std::cout << "Fire: " << std::endl;
			ShowGrid(PlayerEnemyGrid);
			std::cout << "Your Ships: " << std::endl;
			ShowGrid(PlayerOwnGrid);
			system("Pause");
			Fire(GameShipArr, 0, AllAIShips, PlayerEnemyGrid, EnemyGrid, PCurrentX, PCurrentY, PAIHealth, PlayerOwnGrid, AlreadyShot);
			ClearScreen();
			ShowGrid(PlayerEnemyGrid);
			system("Pause");

			if (AIHealth < 1)
			{
				break;
			}

			//ai fires
			ClearScreen();
			std::cout << "Enemy Fires: " << std::endl;
			FireAI(EnemyGridForDebug, PlayerOwnGrid, PPlayerHealth, AllPlayerShips);
			ShowGrid(PlayerOwnGrid);
			system("Pause");
		}

		//end condition
		if (PlayerHealth < 1)
		{
			std::cout << "You lost :(" << std::endl;
		}
		else
		{
			std::cout << "You won :)" << std::endl;
		}
		system("Pause");
		ClearScreen();
		while (true)
		{
			char AgainInput;
			std::cout << "Play Again?" << std::endl;
			std::cout << "1) Yes" << std::endl << "2) No" << std::endl;
			std::cin >> AgainInput;
			if (AgainInput == '1')
			{
				Again = true;
				break;
			}
			else if (AgainInput == '2')
			{
				Again = false;
				break;
			}
			else
			{
				ClearScreen();
				std::cout << "Not a valid input, try again.";
				system("Pause");
				ClearScreen();
			}
		}
	}
	return 0;
}