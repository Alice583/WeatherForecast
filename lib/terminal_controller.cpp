#include "terminal_controller.h"
#include "windows.h"


using namespace controller;


void terminal::DrawCurrentDay() {
    start_color();
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    attron(COLOR_PAIR(2));
    printw(("The weather in: " + controller::town_info.name).c_str());
    refresh();
    move(1, 0);
    printw(ParseWeatherCode(controller::weather_info.current.weather_code).c_str());
    move(2, 0);
    printw((controller::weather_info.current.temperature_2m + " " + '\370' +
            controller::weather_info.current_units.temperature_2m.substr(3, 1) + ", feels like: " +
            controller::weather_info.current.apparent_temperature + " " + '\370' +
            controller::weather_info.current_units.apparent_temperature.substr(3, 1)).c_str());
    move(3, 0);
    printw((controller::weather_info.current.wind_speed_10m + " " +
            controller::weather_info.current_units.wind_speed_10m).c_str());
    move(4, 0);
    printw((controller::weather_info.current.relative_humidity_2m + " " +
            controller::weather_info.current_units.relative_humidity_2m).c_str());
    move(5, 0);
}

void terminal::WriteTempIntoWin(WINDOW* win, int count) {
    refresh();
    box(win, 0, 0);
    mvwprintw(win, 1, 1, ParseWeatherCode(controller::weather_info.hourly.weather_code[count]).c_str());
    mvwprintw(win, 2, 2, (controller::weather_info.hourly.temperature_2m[count] + " (" +
                          controller::weather_info.hourly.apparent_temperature[5] + ") " + '\370' +
                          controller::weather_info.hourly_units.temperature_2m.substr(3, 1)).c_str());
    mvwprintw(win, 3, 2, (controller::weather_info.hourly.wind_speed_10m[count] + " " +
                          controller::weather_info.hourly_units.wind_speed_10m).c_str());
    mvwprintw(win, 4, 2, (controller::weather_info.hourly.relative_humidity_2m[count] + " " +
                          controller::weather_info.hourly_units.relative_humidity_2m).c_str());
    wrefresh(win);
}

void terminal::MakeHeader(WINDOW* win, std::string part_day) {
    refresh();
    box(win, 0, 0);
    mvwprintw(win, 1, 10, part_day.c_str());
    wrefresh(win);
}

void terminal::DrawTable(int count_days) {
    const int kDeltaCoordY = 8;

    int size_y = 3;
    int size_x = 15;
    int coord_x = 48;
    int coord_y = 5;

    int size_y_for_headers = 3;
    int size_x_for_headers = 28;
    int coord_y_for_headers = 6;
    int coord_x_for_headers = 2;

    int idx_days = 24 * count_days;

    noecho();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);

    WINDOW* header1 = newwin(size_y_for_headers, size_x_for_headers, coord_y_for_headers, coord_x_for_headers);
    WINDOW* header2 = newwin(size_y_for_headers, size_x_for_headers, coord_y_for_headers, coord_x_for_headers + 27);
    WINDOW* header3 = newwin(size_y_for_headers, size_x_for_headers, coord_y_for_headers, coord_x_for_headers + 27 * 2);
    WINDOW* header4 = newwin(size_y_for_headers, size_x_for_headers, coord_y_for_headers, coord_x_for_headers + 27 * 3);

    MakeHeader(header1, "Morning");
    MakeHeader(header2, "Day");
    MakeHeader(header3, "Evening");
    MakeHeader(header4, "Night");

    WINDOW* data1 = newwin(size_y, size_x, coord_y, coord_x);
    refresh();
    box(data1, 0, 0);
    wattron(data1, COLOR_PAIR(1));
    mvwprintw(data1, 1, 2, (controller::weather_info.hourly.time[idx_days].substr(1, 10)).c_str());
    wrefresh(data1);

    WINDOW* winMorning1 = newwin(6, size_x_for_headers, 8, coord_x_for_headers);
    WINDOW* winDay1 = newwin(6, size_x_for_headers, 8, coord_x_for_headers + 27);
    WINDOW* winEvening1 = newwin(6, size_x_for_headers, 8, coord_x_for_headers + 27 * 2);
    WINDOW* winNight1 = newwin(6, size_x_for_headers, 8, coord_x_for_headers + 27 * 3);

    WriteTempIntoWin(winMorning1, 6 + idx_days);
    WriteTempIntoWin(winDay1, 12 + idx_days);
    WriteTempIntoWin(winEvening1, 18 + idx_days);
    WriteTempIntoWin(winNight1, 0 + idx_days);


    WINDOW* header5 = newwin(size_y_for_headers, size_x_for_headers, coord_y_for_headers + kDeltaCoordY,
                             coord_x_for_headers);
    WINDOW* header6 = newwin(size_y_for_headers, size_x_for_headers, coord_y_for_headers + kDeltaCoordY,
                             coord_x_for_headers + 27);
    WINDOW* header7 = newwin(size_y_for_headers, size_x_for_headers, coord_y_for_headers + kDeltaCoordY,
                             coord_x_for_headers + 27 * 2);
    WINDOW* header8 = newwin(size_y_for_headers, size_x_for_headers, coord_y_for_headers + kDeltaCoordY,
                             coord_x_for_headers + 27 * 3);

    MakeHeader(header5, "Morning");
    MakeHeader(header6, "Day");
    MakeHeader(header7, "Evening");
    MakeHeader(header8, "Night");

    WINDOW* data2 = newwin(size_y, size_x, coord_y + kDeltaCoordY, coord_x);
    refresh();
    box(data2, 0, 0);
    wattron(data2, COLOR_PAIR(1));
    mvwprintw(data2, 1, 2, (controller::weather_info.hourly.time[24 + idx_days].substr(1, 10)).c_str());
    wrefresh(data2);

    WINDOW* winMorning2 = newwin(6, size_x_for_headers, 8 + kDeltaCoordY, coord_x_for_headers);
    WINDOW* winDay2 = newwin(6, size_x_for_headers, 8 + kDeltaCoordY, coord_x_for_headers + 27);
    WINDOW* winEvening2 = newwin(6, size_x_for_headers, 8 + kDeltaCoordY, coord_x_for_headers + 27 * 2);
    WINDOW* winNight2 = newwin(6, size_x_for_headers, 8 + kDeltaCoordY, coord_x_for_headers + 27 * 3);

    WriteTempIntoWin(winMorning2, 30 + idx_days);
    WriteTempIntoWin(winDay2, 36 + idx_days);
    WriteTempIntoWin(winEvening2, 42 + idx_days);
    WriteTempIntoWin(winNight2, 24 + idx_days);


    WINDOW* header9 = newwin(size_y_for_headers, size_x_for_headers, coord_y_for_headers + 2 * kDeltaCoordY,
                             coord_x_for_headers);
    WINDOW* header10 = newwin(size_y_for_headers, size_x_for_headers, coord_y_for_headers + 2 * kDeltaCoordY,
                              coord_x_for_headers + 27);
    WINDOW* header11 = newwin(size_y_for_headers, size_x_for_headers, coord_y_for_headers + 2 * kDeltaCoordY,
                              coord_x_for_headers + 27 * 2);
    WINDOW* header12 = newwin(size_y_for_headers, size_x_for_headers, coord_y_for_headers + 2 * kDeltaCoordY,
                              coord_x_for_headers + 27 * 3);

    MakeHeader(header9, "Morning");
    MakeHeader(header10, "Day");
    MakeHeader(header11, "Evening");
    MakeHeader(header12, "Night");

    WINDOW* data3 = newwin(size_y, size_x, coord_y + 2 * kDeltaCoordY, coord_x);
    refresh();
    box(data3, 0, 0);
    wattron(data3, COLOR_PAIR(1));
    mvwprintw(data3, 1, 2, (controller::weather_info.hourly.time[48 + idx_days].substr(1, 10)).c_str());
    wrefresh(data3);

    WINDOW* winMorning3 = newwin(6, size_x_for_headers, 8 + 2 * kDeltaCoordY, coord_x_for_headers);
    WINDOW* winDay3 = newwin(6, size_x_for_headers, 8 + 2 * kDeltaCoordY, coord_x_for_headers + 27);
    WINDOW* winEvening3 = newwin(6, size_x_for_headers, 8 + 2 * kDeltaCoordY, coord_x_for_headers + 27 * 2);
    WINDOW* winNight3 = newwin(6, size_x_for_headers, 8 + 2 * kDeltaCoordY, coord_x_for_headers + 27 * 3);

    WriteTempIntoWin(winMorning3, 54 + idx_days);
    WriteTempIntoWin(winDay3, 60 + idx_days);
    WriteTempIntoWin(winEvening3, 66 + idx_days);
    WriteTempIntoWin(winNight3, 48 + idx_days);
}

void terminal::DrawAndFollowTerminal() {
    int kGoodResponse = 200;
    int kDeltaDays = 3;
    int kKeyEsc = 27;
    char kKeyN = 'n';
    char kKeyP = 'p';
    char kKeyPlus = '+';
    char kKeyMinus = '-';
    nlohmann::json config_JSON;
    std::ifstream file_JSON("config.json");
    config_JSON = nlohmann::json::parse(file_JSON);

    int count_days = 0;
    int max_towns = 203;
    int max_days = 15;
    int key;

    initscr();
    noecho();
    controller::WriteDescriptionTown(index_town);
    controller::WriteDescriptionWeather();

    DrawCurrentDay();
    DrawTable(count_days);
    while (true) {
        key = getch();
        if (controller::status_code_town == kGoodResponse && controller::status_code_weather == kGoodResponse) {
            if (key == kKeyN) {
                clear();
                controller::index_town++;
                if (controller::index_town == max_towns + 1) {
                    controller::index_town = 0;
                }
                controller::WriteDescriptionTown(controller::index_town);
                controller::WriteDescriptionWeather();
                DrawCurrentDay();
                DrawTable(count_days);
            } else if (key == kKeyP) {
                clear();
                controller::index_town--;
                if (controller::index_town == -1) {
                    controller::index_town = max_towns;
                }
                controller::WriteDescriptionTown(controller::index_town);
                controller::WriteDescriptionWeather();
                DrawCurrentDay();
                DrawTable(count_days);
            } else if (key == kKeyPlus) {
                count_days += kDeltaDays;
                if (count_days == max_days) {
                    count_days = max_days - 3;
                }
                clear();
                DrawCurrentDay();
                DrawTable(count_days);
            } else if (key == kKeyMinus) {
                count_days -= kDeltaDays;
                if (count_days == -3) {
                    count_days = 0;
                }
                clear();
                DrawCurrentDay();
                DrawTable(count_days);
            } else if (key == kKeyEsc) {
                endwin();
                exit(0);
            }
        } else {
            while (controller::status_code_town != kGoodResponse && controller::status_code_weather != kGoodResponse) {
                controller::WriteDescriptionTown(index_town);
                controller::WriteDescriptionWeather();
                if (key == kKeyEsc) {
                    endwin();
                    exit(0);
                }
                Sleep(config_JSON["updateFrequency"]);
            }
            clear();
            DrawCurrentDay();
            DrawTable(count_days);
        }
    }
}

std::string terminal::ParseWeatherCode(std::string& weather_code) {
    nlohmann::json weather_code_JSON;
    std::ifstream file_JSON("WeatherParser.json");
    weather_code_JSON = nlohmann::json::parse(file_JSON);
    return weather_code_JSON[weather_code];
}

