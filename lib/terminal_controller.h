#include "city_and_weather_controller.cpp"
#include <curses.h>

namespace terminal {
    void DrawTable(int count_days);

    void DrawCurrentDay();

    void DrawAndFollowTerminal();

    void WriteTempIntoWin(WINDOW * win, int count);

    void MakeHeader(WINDOW * win, std::string part_day);

    std::string ParseWeatherCode(std::string& weather_code);
}