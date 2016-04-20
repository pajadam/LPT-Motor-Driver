#ifndef MAIN_HPP
#define MAIN_HPP

#if       _WIN32_WINNT < 0x0500
  #undef  _WIN32_WINNT
  #define _WIN32_WINNT   0x0500
#endif
#include <windows.h>

#include <iostream>
#include <thread>

#include "driver/driver.hpp"
#include "ui/gui/gui.hpp"
#include "ui/tui/tui.hpp"
#include "ui/ui.hpp"

void StartThread();

#endif // MAIN_HPP
