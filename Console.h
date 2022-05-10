#pragma once

#include <istream>
#include <ostream>

enum ConsoleColor {
	CONSOLE_COLOR_BLACK = 30
	, CONSOLE_COLOR_RED = 31
	, CONSOLE_COLOR_GREEN = 32
	, CONSOLE_COLOR_YELLOW = 33
	, CONSOLE_COLOR_BLUE = 34
	, CONSOLE_COLOR_MAGENTA = 35
	, CONSOLE_COLOR_CYAN = 36
	, CONSOLE_COLOR_WHITE = 37
};

class Console {
public:
	Console();
	~Console();

	std::ostream& out;
	std::istream& in;

	// Methoden zum Einstellen von Text- und Hintergrundfarbe:
	void setTextColor(ConsoleColor color);
	void setTextColorBright(ConsoleColor color);
	void setBackgroundColor(ConsoleColor color);
	void setBackgroundColorBright(ConsoleColor color);
	void resetColor();

	// Methoden zum Loeschen von Ausgabebereichen
	void clearScreen();
	void clearScreenToBottom();
	void clearScreenToTop();
	void clearLine();
	void clearLineToRight();
	void clearLineToLeft();

	// Methoden zur Manipulation der Ausgabeposition
	void getCursorPosition(int& row, int& col);
	void moveUp(int positions);
	void moveDown(int positions);
	void moveRight(int positions);
	void moveLeft(int positions);
	void moveTo(int row, int col);
	void saveCursorPosition();
	void restoreCursorPosition();
};
