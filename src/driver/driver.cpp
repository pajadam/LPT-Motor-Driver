#include "driver.hpp"

Driver::Driver()
{
    hLib = LoadLibrary("data/inpout32.dll");
    if (hLib == NULL)
    {
        cout << "Failed to load 'inpout32.dll'" << endl;
        cin.get();
        throw;
    }

    in = (inpfuncPtr) GetProcAddress(hLib, "Inp32");

    if (in == NULL)
    {
        cout << "GetProcAddress for Inp32 Failed.\n";
        cin.get();
        throw;
    }

    out = (oupfuncPtr) GetProcAddress(hLib, "Out32");

    if (out == NULL)
    {
        cout << "GetProcAddress for Oup32 Failed.\n";
        cin.get();
        throw;
    }

    if (in(0xFF))
    {
        out(port,0x00);
    }

    motor[ FIRST  ].direction = DEFAULT_DIRECTION;
    motor[ FIRST  ].timestep =  sf::milliseconds( DEFAULT_TIMESTEP );
    motor[ FIRST  ].turnedOn =  DEFAULT_STATE;

    motor[ SECOND ].direction = DEFAULT_DIRECTION;
    motor[ SECOND ].timestep =  sf::milliseconds( DEFAULT_TIMESTEP );
    motor[ SECOND ].turnedOn =  DEFAULT_STATE;
}

Driver::~Driver()
{
    out(port,0x00);
}

void Driver::process()
{
    if( motor[FIRST].turnedOn && motor[SECOND].turnedOn )
    {
        out(port,0x00+steps[ driver_step[ FIRST ] ] + steps[ driver_step[ SECOND ] + 8 ] );
    }else
    if( motor[FIRST].turnedOn )
    {
        out(port,0x00+steps[ driver_step[ FIRST ] ] );
    }else
    {
        out(port,0x00+steps[ driver_step[ SECOND ] + 8 ] );
    }
}

void Driver::Loop()
{
    //TODO: DWA OBROTY W LEWO, I DWA W PRAWO :D

    while( !exit )
    {
        sf::Time elapsed = clock.restart();

        timeSinceLastUpdate[FIRST] += elapsed;
        timeSinceLastUpdate[SECOND] += elapsed;

        if( timeSinceLastUpdate[FIRST] >= motor[FIRST].timestep )
        {
            timeSinceLastUpdate[FIRST] = sf::seconds( 0 );
            driver_mutex.lock();
            if( motor[FIRST].turnedOn == true )
            {
                if( motor[FIRST].direction == LEFT )
                {
                    if( driver_step[FIRST] == 7 )
                        driver_step[FIRST] = 0;
                    else
                        driver_step[FIRST]++;
                }else
                {
                    if( driver_step[FIRST] == 0 )
                        driver_step[FIRST] = 7;
                    else
                        driver_step[FIRST]--;
                }
            }
            driver_mutex.unlock();
            update = true;
        }

        if( timeSinceLastUpdate[SECOND] >= motor[SECOND].timestep )
        {
            timeSinceLastUpdate[SECOND] = sf::seconds( 0 );
            driver_mutex.lock();
            if( motor[SECOND].turnedOn == true )
            {
                if( motor[SECOND].direction == LEFT )
                {
                    if( driver_step[SECOND] == 7 )
                        driver_step[SECOND] = 0;
                    else
                        driver_step[SECOND]++;
                }else
                {
                    if( driver_step[SECOND] == 0 )
                        driver_step[SECOND] = 7;
                    else
                        driver_step[SECOND]--;
                }
            }
            driver_mutex.unlock();
            update = true;
        }

        if( update == true )
        {
            process();
            update = false;
        }

        Sleep( 0 );
    }
}
