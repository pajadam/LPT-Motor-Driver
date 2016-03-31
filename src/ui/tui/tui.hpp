#ifndef TUI_HPP
#define TUI_HPP

#include "../../driver/driver.hpp"
#include "../ui.hpp"
#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

class text_ui : public ui
{
public:
    text_ui( Driver *_driver );
    ~text_ui();
private:
    void loop();
    void setCursorPos( int x, int y );
    void clearConsole();
    void place( string text, int x, int y );

    void showMotorsInfo();
    void showMainScheme();
    void showUserInput();
    void showMainMenu();

    HANDLE consoleOutput;
};

#endif // TUI_HPP
