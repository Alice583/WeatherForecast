#include "JSONs.h"

using namespace JSONs;

namespace controller {
    int index_town = 0;
    long status_code_town;
    long status_code_weather;
    const std::string url_town = "https://api.api-ninjas.com/v1/city";
    std::string my_header;
    const std::string url_weather = "https://api.open-meteo.com/v1/forecast";
    int Hours_of_day = 24;
    JSONs::TownJSON town_json;
    JSONs::WeatherJSON weather_json;

    void writeDescriptionTown(int index_town);

    void writeDescriptionWeather();

    void clearJSON();
}