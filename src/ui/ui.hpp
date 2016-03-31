#ifndef UI_HPP
#define UI_HPP

#include "../driver/driver.hpp"

class ui
{
public:
    virtual ~ui();
    virtual void loop();

    void start();

    void getMotorsInfo();

    Motor motor[ 2 ];
    Driver *driver;
};

#endif // UI_HPP
