#include "ui.hpp"

ui::~ui()
{

}

void ui::start()
{
    getMotorsInfo();
    loop();
}

void ui::loop(){}

void ui::getMotorsInfo()
{
    motor[ 0 ] = driver->getMotor( 0 );
    motor[ 1 ] = driver->getMotor( 1 );
}
