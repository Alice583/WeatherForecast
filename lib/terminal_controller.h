#include "city_and_weather_controller.cpp"
#include <curses.h>

namespace terminal {
    void drawTable(int count_days);

    void drawCurrentDay();

    void drawAll();

    void writeTempIntoWin(WINDOW* win, int count);

    void makeHeader(WINDOW* win, std::string part_day);

    std::string parseWeatherCode(std::string& weather_code);
}