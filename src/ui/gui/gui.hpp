#ifndef GUI_HPP
#define GUI_HPP

#include "../../driver/driver.hpp"
#include "../ui.hpp"

class graphic_ui : public ui
{
public:
    graphic_ui( Driver *_driver );

private:
    void loop();
};

#endif // GUI_HPP
