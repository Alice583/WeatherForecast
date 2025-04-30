#include "city_and_weather_controller.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

void controller::WriteDescriptionTown(int index_town) {

    nlohmann::json config_JSON;
    std::ifstream file_JSON("config.json");
    config_JSON = nlohmann::json::parse(file_JSON);
    cpr::Response responseTown = cpr::Get(cpr::Url{url_town}, cpr::Header{{"X-Api-Key", my_header}},
                                          cpr::Parameters{{"name", config_JSON["listTowns"][index_town]}});
    if (responseTown.status_code == 200) {
        status_code_town = responseTown.status_code;
        nlohmann::json answer_town_JSON;
        answer_town_JSON = nlohmann::json::parse(responseTown.text);
        town_info.name = answer_town_JSON[0]["name"];
        town_info.latitude = to_string(answer_town_JSON[0]["latitude"]);
        town_info.longitude = to_string(answer_town_JSON[0]["longitude"]);
        town_info.country = answer_town_JSON[0]["country"];
        town_info.population = to_string(answer_town_JSON[0]["population"]);
        town_info.is_capital = to_string(answer_town_JSON[0]["is_capital"]);
    } else {
        status_code_town = responseTown.status_code;
    }
}

void controller::WriteDescriptionWeather() {
    nlohmann::json config_JSON;
    std::ifstream file_JSON("config.json");
    config_JSON = nlohmann::json::parse(file_JSON);

    cpr::Response response_weather = cpr::Get(cpr::Url{url_weather}, cpr::Parameters{{"latitude",  town_info.latitude},
                                                                                     {"longitude", town_info.longitude},
                                                                                     {"current",   "temperature_2m"},
                                                                                     {"current",   "relative_humidity_2m"},
                                                                                     {"current",   "apparent_temperature"},
                                                                                     {"current",   "is_day"},
                                                                                     {"current",   "weather_code"},
                                                                                     {"current",   "wind_speed_10m"},
                                                                                     {"hourly",    "temperature_2m"},
                                                                                     {"hourly",    "relative_humidity_2m"},
                                                                                     {"hourly",    "apparent_temperature"},
                                                                                     {"hourly",    "weather_code"},
                                                                                     {"hourly",        "wind_speed_10m"},
                                                                                     {"forecast_days", to_string(
                                                                                             config_JSON["amountOfDays"])}});
    if (response_weather.status_code == 200) {
        status_code_weather = response_weather.status_code;
        nlohmann::json answer_weather_JSON;
        answer_weather_JSON = nlohmann::json::parse(response_weather.text);
        weather_info.latitude = to_string(answer_weather_JSON["latitude"]);
        weather_info.longitude = to_string(answer_weather_JSON["longitude"]);
        weather_info.generationtime_ms = to_string(answer_weather_JSON["generationtime_ms"]);
        weather_info.utc_offset_seconds = to_string(answer_weather_JSON["utc_offset_seconds"]);
        weather_info.timezone = to_string(answer_weather_JSON["timezone"]);
        weather_info.timezone_abbreviation = to_string(answer_weather_JSON["timezone_abbreviation"]);
        weather_info.elevation = to_string(answer_weather_JSON["elevation"]);

        weather_info.current_units.time = to_string(answer_weather_JSON["current_units"]["time"]);
        weather_info.current_units.interval = to_string(answer_weather_JSON["current_units"]["interval"]);
        weather_info.current_units.temperature_2m = to_string(answer_weather_JSON["current_units"]["temperature_2m"]);
        weather_info.current_units.relative_humidity_2m = to_string(
                answer_weather_JSON["current_units"]["relative_humidity_2m"]);
        weather_info.current_units.apparent_temperature = to_string(
                answer_weather_JSON["current_units"]["apparent_temperature"]);
        weather_info.current_units.is_day = to_string(answer_weather_JSON["current_units"]["is_day"]);
        weather_info.current_units.weather_code = to_string(answer_weather_JSON["current_units"]["weather_code"]);
        weather_info.current_units.wind_speed_10m = to_string(answer_weather_JSON["current_units"]["wind_speed_10m"]);

        weather_info.current.time = to_string(answer_weather_JSON["current"]["time"]);
        weather_info.current.interval = to_string(answer_weather_JSON["current"]["interval"]);
        weather_info.current.temperature_2m = to_string(answer_weather_JSON["current"]["temperature_2m"]);
        weather_info.current.relative_humidity_2m = to_string(answer_weather_JSON["current"]["relative_humidity_2m"]);
        weather_info.current.apparent_temperature = to_string(answer_weather_JSON["current"]["apparent_temperature"]);
        weather_info.current.is_day = to_string(answer_weather_JSON["current"]["is_day"]);
        weather_info.current.weather_code = to_string(answer_weather_JSON["current"]["weather_code"]);
        weather_info.current.wind_speed_10m = to_string(answer_weather_JSON["current"]["wind_speed_10m"]);

        weather_info.hourly_units.time = to_string(answer_weather_JSON["hourly_units"]["time"]);
        weather_info.hourly_units.temperature_2m = to_string(answer_weather_JSON["hourly_units"]["temperature_2m"]);
        weather_info.hourly_units.relative_humidity_2m = to_string(
                answer_weather_JSON["hourly_units"]["relative_humidity_2m"]);
        weather_info.hourly_units.apparent_temperature = to_string(
                answer_weather_JSON["hourly_units"]["apparent_temperature"]);
        weather_info.hourly_units.weather_code = to_string(answer_weather_JSON["hourly_units"]["weather_code"]);
        weather_info.hourly_units.wind_speed_10m = to_string(answer_weather_JSON["hourly_units"]["wind_speed_10m"]);

        ClearInfo();

        for (int i = 0; i < Hours_of_day * stoi(to_string(config_JSON["amountOfDays"])); ++i) {
            weather_info.hourly.time.push_back(to_string(answer_weather_JSON["hourly"]["time"][i]));
            weather_info.hourly.temperature_2m.push_back(to_string(answer_weather_JSON["hourly"]["temperature_2m"][i]));
            weather_info.hourly.relative_humidity_2m.push_back(
                    to_string(answer_weather_JSON["hourly"]["relative_humidity_2m"][i]));
            weather_info.hourly.apparent_temperature.push_back(
                    to_string(answer_weather_JSON["hourly"]["apparent_temperature"][i]));
            weather_info.hourly.weather_code.push_back(to_string(answer_weather_JSON["hourly"]["weather_code"][i]));
            weather_info.hourly.wind_speed_10m.push_back(to_string(answer_weather_JSON["hourly"]["wind_speed_10m"][i]));
        }
    } else {
        status_code_weather = response_weather.status_code;
    }
}

void controller::ClearInfo() {
    weather_info.hourly.time.clear();
    weather_info.hourly.temperature_2m.clear();
    weather_info.hourly.relative_humidity_2m.clear();
    weather_info.hourly.apparent_temperature.clear();
    weather_info.hourly.weather_code.clear();
    weather_info.hourly.wind_speed_10m.clear();
}