/**
    Created by @pajadam
*/
#include "main.hpp"

using namespace std;

Driver *driver;

void StartThread()
{
    if( driver != nullptr )
        driver->Loop();
    else
    {
        cerr << "driver pointer: null" << endl;
        throw;
    }
}

BOOL WINAPI CtrlCHandler( DWORD )
{
    HANDLE consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo( consoleOutput, &info );

    COORD topleft = { 0, 0 };
    DWORD num;
    FillConsoleOutputCharacter(consoleOutput, ' ', info.dwSize.X * info.dwSize.Y, topleft, &num);

    SetConsoleCursorPosition( consoleOutput, topleft );

    return FALSE;
}

int main( int argc, char **argv )
{
    SetConsoleCtrlHandler(CtrlCHandler, TRUE);
    ui *_ui;

    if( argc == 1 )
    {
        ShowWindow( GetConsoleWindow(), SW_HIDE );

        driver = new Driver();
        thread tr( StartThread );

        _ui = new graphic_ui( driver );
        _ui->start();

        driver->Exit();
        tr.join();

        delete driver;
        delete _ui;

        return 0;
    }

    string parameter = argv[1];

    if( argc >= 2 )
    {
        if( parameter == "-console" && argc == 2 )
        {
            driver = new Driver();
            thread tr( StartThread );

            _ui = new text_ui( driver );
            _ui->start();

            driver->Exit();
            tr.join();
            delete driver;
            delete _ui;

            return 0;

        }else
        {
            //Pokazujemy jak korzystac
            cout << "usage: " << argv[0] << endl
                 << "or " << endl
                 << argv[0] << " -console" << endl;
            return 0;
        }
    }

    return 0;
}







