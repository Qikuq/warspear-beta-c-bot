#include "controls.h"

void pressKey(int Vkey) {
    INPUT inputs[2] = {};

    // Key down event
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = Vkey;  // Use the passed virtual-key code
    inputs[0].ki.dwFlags = 0;

    // Key up event
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = Vkey;
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

    // Send the key press
    SendInput(2, inputs, sizeof(INPUT));
}
void click(int x, int y) {
    INPUT inputs[2] = {};

    inputs[0].type = INPUT_MOUSE;
    inputs[0].mi.dx = (long)x;
    inputs[0].mi.dy = (long)y;
    inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    inputs[1].type = INPUT_MOUSE;
    inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    SendInput(2, inputs, sizeof(INPUT));
}