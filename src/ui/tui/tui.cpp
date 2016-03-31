#include "tui.hpp"

text_ui::text_ui( Driver *_driver )
{
    consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    driver = _driver;
}

text_ui::~text_ui()
{
    clearConsole();
}

void text_ui::showMainScheme()
{
    place( "######################", 1, 1 );
    place( "#  LPT Motor Driver  #", 1, 2 );
    place( "#     by pajadam     #", 1, 3 );
    place( "######################", 1, 4 );
    place( "SILNIK #1", 1, 10 );
    place( "SILNIK #2", 1, 12 );
    place( "STAN", 12, 8 );
    place( "KIERUNEK", 19, 8 );
    place( "PREDKOSC", 30, 8 );
}

void text_ui::showUserInput()
{
    setCursorPos( 12, 14 );
    place( "Twoj wybor:", 1, 14 );
}

void text_ui::showMainMenu()
{
    place( "MENU", 24, 1 );
    place( "1. PREDKOSC", 24, 2 );
    place( "2. KIERUNEK", 24, 3 );
    place( "3. WLACZ", 24, 4 );
    place( "4. WYLACZ", 24, 5 );
    place( "0. WYJDZ", 24, 6 );
}

void text_ui::loop()
{
    while( 1 )
    {
        int get1, get2, get3;

        clearConsole();

        showMainScheme();
        showMotorsInfo();
        showMainMenu();

        showUserInput();
        cin >> get1;
        if( get1 == 0 )
        {
            return;
        }
        else if( get1 < 0 || get1 > 4 )
        {

        }
        else
        {
            clearConsole();
            showMainScheme();
            showMotorsInfo();

            place( "Wybierz silnik.", 24, 1 );
            place( "1. PIERWSZY", 24, 3 );
            place( "2. DRUGI", 24, 4 );
            place( "0. COFNIJ", 24, 5 );

            showUserInput();
            cin >> get2;

            if( get2 > 0 && get2 < 3 )
            {
                get2--;
                switch( get1 )
                {
                case 1:
                    clearConsole();
                    showMainScheme();
                    showMotorsInfo();
                    place( "Podaj predkosc silnika #" + to_string( get2 + 1 ) + " [ms]        ", 24, 2 );
                    showUserInput();
                    cin >> get3;
                    motor[get2].timestep = sf::milliseconds( get3 );
                    driver->setMotor( get2, motor[get2] );
                    break;
                case 2:
                    clearConsole();
                    showMainScheme();
                    showMotorsInfo();
                    place( "1. Lewo", 24, 3 );
                    place( "2. Prawo", 24, 4 );
                    place( "0. Cofnij", 24, 5 );
                    place( "Podaj kierunek obrotu silnika #" + to_string( get2 + 1 ), 24, 2 );
                    showUserInput();
                    cin >> get3;
                    if( get3 <= 0 && get3 >= 3 )
                        break;
                    motor[get2].direction = get3 - 1;
                    driver->setMotor( get2, motor[get2] );
                    break;
                case 3:
                    motor[get2].turnedOn = true;
                    driver->setMotor( get2, motor[get2] );
                    break;
                case 4:
                    motor[get2].turnedOn = false;
                    driver->setMotor( get2, motor[get2] );
                    break;
                }
            }
        }
        showMotorsInfo();
    }
}

void text_ui::showMotorsInfo()
{
    place( "                                                                             ", 11, 10 );
    place( "                                                                             ", 11, 12 );
    if( motor[0].turnedOn == true )
        place( " ON ", 11, 10 );
    else place( " OFF", 11, 10 );

    if( motor[1].turnedOn == true )
        place( " ON ", 11, 12 );
    else place( " OFF", 11, 12 );

    if( motor[0].direction == LEFT )
        place( "LEFT ", 21, 10 );
    else place( "RIGHT", 21, 10 );

    if( motor[1].direction == LEFT )
        place( "LEFT ", 21, 12 );
    else place( "RIGHT", 21, 12 );

    place( to_string( motor[0].timestep.asMilliseconds() ) + "ms     ", 31, 10 );
    place( to_string( motor[1].timestep.asMilliseconds() ) + "ms     ", 31, 12 );
}

void text_ui::clearConsole()
{
    consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo( consoleOutput, &info );

    COORD topleft = { 0, 0 };
    DWORD num;
    FillConsoleOutputCharacter(consoleOutput, ' ', info.dwSize.X * info.dwSize.Y, topleft, &num);
    setCursorPos( 0, 0 );
}

void text_ui::setCursorPos( int x, int y )
{
    consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { x, y };
    SetConsoleCursorPosition( consoleOutput, position );
}

void text_ui::place( string text, int x, int y )
{
    consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { x, y };
    DWORD num;
    for( int i = 0; i < text.size(); i++ )
    {
        FillConsoleOutputCharacter( consoleOutput, text[i], 1, position, &num );
        position.X++;
    }
}
