#ifdef _WIN32
#define  _CRT_SECURE_NO_WARNINGS 1
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#include <iostream>
#include "Console.h"

#include <cstdio>
#include <cstdlib>

enum ConsoleClear {
	CONSOLE_CLEAR_FROM_CURSOR_TO_END = 0
	, CONSOLE_CLEAR_FROM_CURSOR_TO_BEGIN = 1
	, CONSOLE_CLEAR_ALL = 2
};

static int instances = 0;
static bool visible_input = true;

void instance_check() {
	if (instances != 0) {
		std::cerr << "Only one instance of Console allowed, sorry...\n";
		exit(1);
	}
	++instances;
}

void reset_input_mode();
void set_invisible_input_mode();

#ifdef _WIN32
// Some old MinGW/CYGWIN distributions don't define this:
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#endif

static HANDLE stdoutHandle = []() {
	HANDLE stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (stdoutHandle == INVALID_HANDLE_VALUE) {
		exit(GetLastError());
	}
	return stdoutHandle;
}();

static HANDLE stdinHandle = []() {
	stdinHandle = GetStdHandle(STD_INPUT_HANDLE);
	if (stdinHandle == INVALID_HANDLE_VALUE) {
		exit(GetLastError());
	}
	return stdinHandle;
}();

static DWORD outModeInit = []() {
	DWORD outMode;
	if (!GetConsoleMode(stdoutHandle, &outMode)) {
		exit(GetLastError());
	}
	DWORD outModeInit = outMode;
	// Enable ANSI escape codes
	outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(stdoutHandle, outMode)) {
		exit(GetLastError());
	}
	return outModeInit;
}();

static DWORD inModeInit = []() {
	DWORD inMode;
	if (!GetConsoleMode(stdinHandle, &inMode)) {
		exit(GetLastError());
	}
	return inMode;
}();

void reset_input_mode() {
	if (!SetConsoleMode(stdinHandle, inModeInit)) {
		exit(GetLastError());
	}
}
void set_invisible_input_mode() {
	DWORD inMode = inModeInit;
	// Set stdin as no echo and unbuffered
	inMode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
	if (!SetConsoleMode(stdinHandle, inMode)) {
		exit(GetLastError());
	}
}
void reset_output_mode() {
	if (!SetConsoleMode(stdoutHandle, outModeInit)) {
		exit(GetLastError());
	}
}

Console::Console()
	: out(std::cout)
	, in(std::cin)
{
	instance_check();
}

Console::~Console() {
	resetColor();
	// Reset console mode
	reset_output_mode();
	reset_input_mode();
	--instances;
}
#else

static termios orig_term;

void reset_input_mode() {
	tcsetattr(STDIN_FILENO, TCSANOW, &orig_term);
}
void set_invisible_input_mode() {
	termios new_term = orig_term;
	new_term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

Console::Console()
	: out(std::cout)
	, in(std::cin)
{
	instance_check();
	tcgetattr(STDIN_FILENO, &orig_term);
}

Console::~Console() {
	resetColor();
	// Reset console mode
	reset_input_mode();
	--instances;
}
#endif

void Console::getCursorPosition(int& row, int& col) {
	set_invisible_input_mode();
	std::cout << "\x1b[6n";
	std::cout.flush();

	char buff[128];
	int indx = 0;
	for (;;) {
		int cc = getchar();
		buff[indx] = (char)cc;
		++indx;
		if (cc == 'R') {
			buff[indx + 1] = '\0';
			break;
		}
	}
	//enable input vis
	sscanf_s(buff, "\x1b[%d;%dR", &row, &col);
	fseek(stdin, 0, SEEK_END);
	reset_input_mode();
}

void Console::setTextColor(ConsoleColor color) {
	out << "\x1b[" << (int)color << 'm';
}

void Console::setTextColorBright(ConsoleColor color) {
	out << "\x1b[" << (int)color << ";1m";
}

void Console::setBackgroundColor(ConsoleColor color) {
	out << "\x1b[" << ((int)color + 10) << 'm';
}

void Console::setBackgroundColorBright(ConsoleColor color) {
	out << "\x1b[" << ((int)color + 10) << ";1m";
}

void Console::resetColor() {
	out << "\x1b[0m";
}

void Console::clearScreen() {
	out << "\x1b[" << CONSOLE_CLEAR_ALL << 'J';
}

void Console::clearScreenToBottom() {
	out << "\x1b[" << CONSOLE_CLEAR_FROM_CURSOR_TO_END << 'J';
}

void Console::clearScreenToTop() {
	out << "\x1b[" << CONSOLE_CLEAR_FROM_CURSOR_TO_BEGIN << 'J';
}

void Console::clearLine() {
	out << "\x1b[" << CONSOLE_CLEAR_ALL << 'K';
}

void Console::clearLineToRight() {
	out << "\x1b[" << CONSOLE_CLEAR_FROM_CURSOR_TO_END << 'K';
}

void Console::clearLineToLeft() {
	out << "\x1b[" << CONSOLE_CLEAR_FROM_CURSOR_TO_BEGIN << 'K';
}

void Console::moveUp(int positions) {
	out << "\x1b[" << positions << 'A';
}

void Console::moveDown(int positions) {
	out << "\x1b[" << positions << 'B';
}

void Console::moveRight(int positions) {
	out << "\x1b[" << positions << 'C';
}

void Console::moveLeft(int positions) {
	out << "\x1b[" << positions << 'D';
}

void Console::moveTo(int row, int col) {
	out << "\x1b[" << row << ';' << col << 'f';
}

void Console::saveCursorPosition() {
	out << "\x1b" << 7;
}

void Console::restoreCursorPosition() {
	out << "\x1b" << 8;
}