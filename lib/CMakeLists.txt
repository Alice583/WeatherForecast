add_library(lib STATIC
        JSONs.h
        city_and_weather_controller.cpp
        city_and_weather_controller.h
        terminal_controller.cpp
        terminal_controller.h
)

target_link_libraries(lib PRIVATE cpr::cpr)
target_link_libraries(lib PRIVATE nlohmann_json::nlohmann_json)

#include_directories(lib PUBLIC third-party/PDCurses-3.9/pdcurses)