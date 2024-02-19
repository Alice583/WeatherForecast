#include "terminal_controller.h"
#include "windows.h"


using namespace controller;


void terminal::drawCurrentDay() {
    start_color();
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    attron(COLOR_PAIR(2));
    printw(("The weather in: " + controller::town_json.name).c_str());
    refresh();
    move(1, 0);
    printw(parseWeatherCode(controller::weather_json.current.weather_code).c_str());
    move(2, 0);
    printw((controller::weather_json.current.temperature_2m + " " + '\370' +
            controller::weather_json.current_units.temperature_2m.substr(3, 1) + ", feels like: " +
            controller::weather_json.current.apparent_temperature + " " + '\370' +
            controller::weather_json.current_units.apparent_temperature.substr(3, 1)).c_str());
    move(3, 0);
    printw((controller::weather_json.current.wind_speed_10m + " " +
            controller::weather_json.current_units.wind_speed_10m).c_str());
    move(4, 0);
    printw((controller::weather_json.current.relative_humidity_2m + " " +
            controller::weather_json.current_units.relative_humidity_2m).c_str());
    move(5, 0);
}

void terminal::writeTempIntoWin(WINDOW* win, int count) {
    refresh();
    box(win, 0, 0);
    mvwprintw(win, 1, 1, parseWeatherCode(controller::weather_json.hourly.weather_code[count]).c_str());
    mvwprintw(win, 2, 2, (controller::weather_json.hourly.temperature_2m[count] + " (" +
                          controller::weather_json.hourly.apparent_temperature[5] + ") " + '\370' +
                          controller::weather_json.hourly_units.temperature_2m.substr(3, 1)).c_str());
    mvwprintw(win, 3, 2, (controller::weather_json.hourly.wind_speed_10m[count] + " " +
                          controller::weather_json.hourly_units.wind_speed_10m).c_str());
    mvwprintw(win, 4, 2, (controller::weather_json.hourly.relative_humidity_2m[count] + " " +
                          controller::weather_json.hourly_units.relative_humidity_2m).c_str());
    wrefresh(win);
}

void terminal::makeHeader(WINDOW* win, std::string part_day) {
    refresh();
    box(win, 0, 0);
    mvwprintw(win, 1, 10, part_day.c_str());
    wrefresh(win);
}

void terminal::drawTable(int count_days) {
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

    makeHeader(header1, "Morning");
    makeHeader(header2, "Day");
    makeHeader(header3, "Evening");
    makeHeader(header4, "Night");

    WINDOW* data1 = newwin(size_y, size_x, coord_y, coord_x);
    refresh();
    box(data1, 0, 0);
    wattron(data1, COLOR_PAIR(1));
    mvwprintw(data1, 1, 2, (controller::weather_json.hourly.time[idx_days].substr(1, 10)).c_str());
    wrefresh(data1);

    WINDOW* winMorning1 = newwin(6, size_x_for_headers, 8, coord_x_for_headers);
    WINDOW* winDay1 = newwin(6, size_x_for_headers, 8, coord_x_for_headers + 27);
    WINDOW* winEvening1 = newwin(6, size_x_for_headers, 8, coord_x_for_headers + 27 * 2);
    WINDOW* winNight1 = newwin(6, size_x_for_headers, 8, coord_x_for_headers + 27 * 3);

    writeTempIntoWin(winMorning1, 6 + idx_days);
    writeTempIntoWin(winDay1, 12 + idx_days);
    writeTempIntoWin(winEvening1, 18 + idx_days);
    writeTempIntoWin(winNight1, 0 + idx_days);


    WINDOW* header5 = newwin(size_y_for_headers, size_x_for_headers, coord_y_for_headers + kDeltaCoordY,
                             coord_x_for_headers);
    WINDOW* header6 = newwin(size_y_for_headers, size_x_for_headers, coord_y_for_headers + kDeltaCoordY,
                             coord_x_for_headers + 27);
    WINDOW* header7 = newwin(size_y_for_headers, size_x_for_headers, coord_y_for_headers + kDeltaCoordY,
                             coord_x_for_headers + 27 * 2);
    WINDOW* header8 = newwin(size_y_for_headers, size_x_for_headers, coord_y_for_headers + kDeltaCoordY,
                             coord_x_for_headers + 27 * 3);

    makeHeader(header5, "Morning");
    makeHeader(header6, "Day");
    makeHeader(header7, "Evening");
    makeHeader(header8, "Night");

    WINDOW* data2 = newwin(size_y, size_x, coord_y + kDeltaCoordY, coord_x);
    refresh();
    box(data2, 0, 0);
    wattron(data2, COLOR_PAIR(1));
    mvwprintw(data2, 1, 2, (controller::weather_json.hourly.time[24 + idx_days].substr(1, 10)).c_str());
    wrefresh(data2);

    WINDOW* winMorning2 = newwin(6, size_x_for_headers, 8 + kDeltaCoordY, coord_x_for_headers);
    WINDOW* winDay2 = newwin(6, size_x_for_headers, 8 + kDeltaCoordY, coord_x_for_headers + 27);
    WINDOW* winEvening2 = newwin(6, size_x_for_headers, 8 + kDeltaCoordY, coord_x_for_headers + 27 * 2);
    WINDOW* winNight2 = newwin(6, size_x_for_headers, 8 + kDeltaCoordY, coord_x_for_headers + 27 * 3);

    writeTempIntoWin(winMorning2, 30 + idx_days);
    writeTempIntoWin(winDay2, 36 + idx_days);
    writeTempIntoWin(winEvening2, 42 + idx_days);
    writeTempIntoWin(winNight2, 24 + idx_days);


    WINDOW* header9 = newwin(size_y_for_headers, size_x_for_headers, coord_y_for_headers + 2 * kDeltaCoordY,
                             coord_x_for_headers);
    WINDOW* header10 = newwin(size_y_for_headers, size_x_for_headers, coord_y_for_headers + 2 * kDeltaCoordY,
                              coord_x_for_headers + 27);
    WINDOW* header11 = newwin(size_y_for_headers, size_x_for_headers, coord_y_for_headers + 2 * kDeltaCoordY,
                              coord_x_for_headers + 27 * 2);
    WINDOW* header12 = newwin(size_y_for_headers, size_x_for_headers, coord_y_for_headers + 2 * kDeltaCoordY,
                              coord_x_for_headers + 27 * 3);

    makeHeader(header9, "Morning");
    makeHeader(header10, "Day");
    makeHeader(header11, "Evening");
    makeHeader(header12, "Night");

    WINDOW* data3 = newwin(size_y, size_x, coord_y + 2 * kDeltaCoordY, coord_x);
    refresh();
    box(data3, 0, 0);
    wattron(data3, COLOR_PAIR(1));
    mvwprintw(data3, 1, 2, (controller::weather_json.hourly.time[48 + idx_days].substr(1, 10)).c_str());
    wrefresh(data3);

    WINDOW* winMorning3 = newwin(6, size_x_for_headers, 8 + 2 * kDeltaCoordY, coord_x_for_headers);
    WINDOW* winDay3 = newwin(6, size_x_for_headers, 8 + 2 * kDeltaCoordY, coord_x_for_headers + 27);
    WINDOW* winEvening3 = newwin(6, size_x_for_headers, 8 + 2 * kDeltaCoordY, coord_x_for_headers + 27 * 2);
    WINDOW* winNight3 = newwin(6, size_x_for_headers, 8 + 2 * kDeltaCoordY, coord_x_for_headers + 27 * 3);

    writeTempIntoWin(winMorning3, 54 + idx_days);
    writeTempIntoWin(winDay3, 60 + idx_days);
    writeTempIntoWin(winEvening3, 66 + idx_days);
    writeTempIntoWin(winNight3, 48 + idx_days);
}

void terminal::drawAll() {
    nlohmann::json config_JSON;
    std::ifstream file_JSON("config.json");
    config_JSON = nlohmann::json::parse(file_JSON);
    int count_days = 0;
    int key;

    initscr();
    noecho();
    controller::writeDescriptionTown(index_town);
    controller::writeDescriptionWeather();

    drawCurrentDay();
    drawTable(count_days);
    while (true) {
        key = getch();
        if (controller::status_code_town == 200 && controller::status_code_weather == 200) {
            if (key == 'n') {
                clear();
                controller::index_town++;
                if (controller::index_town == 204) {
                    controller::index_town = 0;
                }
                controller::writeDescriptionTown(controller::index_town);
                controller::writeDescriptionWeather();
                drawCurrentDay();
                drawTable(count_days);
            } else if (key == 'p') {
                clear();
                controller::index_town--;
                if (controller::index_town == -1) {
                    controller::index_town = 203;
                }
                controller::writeDescriptionTown(controller::index_town);
                controller::writeDescriptionWeather();
                drawCurrentDay();
                drawTable(count_days);
            } else if (key == '+') {
                count_days += 3;
                if (count_days == 15) {
                    count_days = 12;
                }
                clear();
                drawCurrentDay();
                drawTable(count_days);
            } else if (key == '-') {
                count_days -= 3;
                if (count_days == -3) {
                    count_days = 0;
                }
                clear();
                drawCurrentDay();
                drawTable(count_days);
            } else if (key == 27) {
                endwin();
                exit(0);
            }
        } else {
            while (controller::status_code_town != 200 && controller::status_code_weather != 200) {
                controller::writeDescriptionTown(index_town);
                controller::writeDescriptionWeather();
                if (key == 27) {
                    endwin();
                    exit(0);
                }
                Sleep(config_JSON["updateFrequency"]);
            }
            clear();
            drawCurrentDay();
            drawTable(count_days);
        }
    }
}

std::string terminal::parseWeatherCode(std::string& weather_code) {
    nlohmann::json weather_code_JSON;
    std::ifstream file_JSON("WeatherParser.json");
    weather_code_JSON = nlohmann::json::parse(file_JSON);
    return weather_code_JSON[weather_code];
}

