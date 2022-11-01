#include "Console.h"
#include <conio.h>

Console::Console() {


	hideCursor();
	system("title Bomberman");

	std::string str;
	str = "MODE CON COLS=" + std::to_string(plane.width) + "LINES=" + std::to_string(plane.height);
	const char* ch = str.c_str();
	system(ch);

	system("cls");

	char in;
	std::cout << "\t---Bomberman---\n\n" << "-----Press enter to play-------\n\n" << "" << "Game controls:\n\n" << "Arrow keys to move" << "\n'Spacebar' to put a bomb\n\n";
	in = _getch();
}


Console& Console::operator=(const Console&) {
	return *this;
}

Console::~Console() {}


void Console::display() {

	HANDLE handle;
	CHAR_INFO lpBuffer[1];
	COORD dwBufferSize{ 1,1 };
	COORD dwBufferCoord;

	std::string text = "";
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT lpWriteRegion = { SHORT(0), SHORT(0), SHORT(plane.width), SHORT(plane.height) };
	dwBufferCoord = { 0, 0 };

	lpBuffer[0].Char.UnicodeChar = ' ';
	lpBuffer[0].Attributes = BACKGROUND_BLUE | BACKGROUND_INTENSITY;


	// czyszczenie pola
	for (int k = 0; k < plane.height; k++) {
		for (int l = 0; l < plane.width; l++) {
			if (!(k == 0 || l == 0 || k == plane.height - 1 || l == plane.width - 1)) {
				lpBuffer[0].Attributes = BACKGROUND_RED;
				lpWriteRegion = { (SHORT)l, (SHORT)k, 1000, 1000 };
				WriteConsoleOutput(handle, lpBuffer, dwBufferSize, dwBufferCoord, &lpWriteRegion);
			}
		}
	}



	for (int i = 0; i < plane.height; i++) {
		for (int j = 0; j < plane.width; j++) {

			// granice planszy
			if (i == 0 || j == 0 || i == plane.height - 1 || j == plane.width - 1) {
				lpBuffer[0].Attributes = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
				lpWriteRegion = { (SHORT)j, (SHORT)i, 1000, 1000 };
				WriteConsoleOutput(handle, lpBuffer, dwBufferSize, dwBufferCoord, &lpWriteRegion);
			}

			// bomba bot
			if (!characters[0].bomb.getHaveBomb() && characters[0].bomb.getPosY() == i && characters[0].bomb.getPosX() == j) {
				lpBuffer[0].Attributes = BACKGROUND_GREEN;
				lpWriteRegion = { (SHORT)j, (SHORT)i, 1000, 1000 };
				WriteConsoleOutput(handle, lpBuffer, dwBufferSize, dwBufferCoord, &lpWriteRegion);
			}

			// bomba gracz
			if (!characters[1].bomb.getHaveBomb() && characters[1].bomb.getPosY() == i && characters[1].bomb.getPosX() == j) {
				lpBuffer[0].Attributes = BACKGROUND_BLUE;
				lpWriteRegion = { (SHORT)j, (SHORT)i, 1000, 1000 };
				WriteConsoleOutput(handle, lpBuffer, dwBufferSize, dwBufferCoord, &lpWriteRegion);
			}

			// promien bomby
			if (plane.surface[i][j].getDangerous() && !plane.surface[i][j].getNormal()) {
				lpBuffer[0].Attributes = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
				lpWriteRegion = { (SHORT)j, (SHORT)i, 1000, 1000 };
				WriteConsoleOutput(handle, lpBuffer, dwBufferSize, dwBufferCoord, &lpWriteRegion);
			}


			// postacie
			else {

				if (plane.surface[i][j].getNormal()) {
					lpBuffer[0].Attributes = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
					lpWriteRegion = { (SHORT)j, (SHORT)i, 1000, 1000 };
					WriteConsoleOutput(handle, lpBuffer, dwBufferSize, dwBufferCoord, &lpWriteRegion);
				}

				else if (characters[0].getPosX() == j && characters[0].getPosY() == i) {
					lpBuffer[0].Attributes = BACKGROUND_GREEN;
					lpWriteRegion = { (SHORT)j, (SHORT)i, 1000, 1000 };
					WriteConsoleOutput(handle, lpBuffer, dwBufferSize, dwBufferCoord, &lpWriteRegion);
					lpBuffer[0].Attributes = BACKGROUND_RED | BACKGROUND_INTENSITY;
				}

				else if (characters[1].getPosX() == j && characters[1].getPosY() == i) {
					lpBuffer[0].Attributes = BACKGROUND_BLUE;
					lpWriteRegion = { (SHORT)j, (SHORT)i, 1000, 1000 };
					WriteConsoleOutput(handle, lpBuffer, dwBufferSize, dwBufferCoord, &lpWriteRegion);
					lpBuffer[0].Attributes = BACKGROUND_RED | BACKGROUND_INTENSITY;
				}
			}
		}
	}

	if (!characters[0].alive || !characters[1].alive) {
		system("cls");
		if (!characters[0].alive) {
			std::cout << "------Game status: WIN!-------\n";
		}
		else
			std::cout << "------Game status: LOST!------\n";

		std::cout << "\nPress any arrow key...\n";
		//std::cout << "koniec gry, wcisnij dowolna strzalke, aby kontynuowac";
	}

}



void Console::hideCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}