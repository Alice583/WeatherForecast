#include "city_and_weather_controller.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

void controller::writeDescriptionTown(int index_town) {

    nlohmann::json config_JSON;
    std::ifstream file_JSON("config.json");
    config_JSON = nlohmann::json::parse(file_JSON);
    cpr::Response responseTown = cpr::Get(cpr::Url{url_town}, cpr::Header{{"X-Api-Key", my_header}},
                                          cpr::Parameters{{"name", config_JSON["listTowns"][index_town]}});
    if (responseTown.status_code == 200) {
        status_code_town = responseTown.status_code;
        nlohmann::json answer_town_JSON;
        answer_town_JSON = nlohmann::json::parse(responseTown.text);
        town_json.name = answer_town_JSON[0]["name"];
        town_json.latitude = to_string(answer_town_JSON[0]["latitude"]);
        town_json.longitude = to_string(answer_town_JSON[0]["longitude"]);
        town_json.country = answer_town_JSON[0]["country"];
        town_json.population = to_string(answer_town_JSON[0]["population"]);
        town_json.is_capital = to_string(answer_town_JSON[0]["is_capital"]);
    } else {
        status_code_town = responseTown.status_code;
    }
}

void controller::writeDescriptionWeather() {
    nlohmann::json config_JSON;
    std::ifstream file_JSON("config.json");
    config_JSON = nlohmann::json::parse(file_JSON);

    cpr::Response response_weather = cpr::Get(cpr::Url{url_weather}, cpr::Parameters{{"latitude",  town_json.latitude},
                                                                                     {"longitude", town_json.longitude},
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
        weather_json.latitude = to_string(answer_weather_JSON["latitude"]);
        weather_json.longitude = to_string(answer_weather_JSON["longitude"]);
        weather_json.generationtime_ms = to_string(answer_weather_JSON["generationtime_ms"]);
        weather_json.utc_offset_seconds = to_string(answer_weather_JSON["utc_offset_seconds"]);
        weather_json.timezone = to_string(answer_weather_JSON["timezone"]);
        weather_json.timezone_abbreviation = to_string(answer_weather_JSON["timezone_abbreviation"]);
        weather_json.elevation = to_string(answer_weather_JSON["elevation"]);

        weather_json.current_units.time = to_string(answer_weather_JSON["current_units"]["time"]);
        weather_json.current_units.interval = to_string(answer_weather_JSON["current_units"]["interval"]);
        weather_json.current_units.temperature_2m = to_string(answer_weather_JSON["current_units"]["temperature_2m"]);
        weather_json.current_units.relative_humidity_2m = to_string(
                answer_weather_JSON["current_units"]["relative_humidity_2m"]);
        weather_json.current_units.apparent_temperature = to_string(
                answer_weather_JSON["current_units"]["apparent_temperature"]);
        weather_json.current_units.is_day = to_string(answer_weather_JSON["current_units"]["is_day"]);
        weather_json.current_units.weather_code = to_string(answer_weather_JSON["current_units"]["weather_code"]);
        weather_json.current_units.wind_speed_10m = to_string(answer_weather_JSON["current_units"]["wind_speed_10m"]);

        weather_json.current.time = to_string(answer_weather_JSON["current"]["time"]);
        weather_json.current.interval = to_string(answer_weather_JSON["current"]["interval"]);
        weather_json.current.temperature_2m = to_string(answer_weather_JSON["current"]["temperature_2m"]);
        weather_json.current.relative_humidity_2m = to_string(answer_weather_JSON["current"]["relative_humidity_2m"]);
        weather_json.current.apparent_temperature = to_string(answer_weather_JSON["current"]["apparent_temperature"]);
        weather_json.current.is_day = to_string(answer_weather_JSON["current"]["is_day"]);
        weather_json.current.weather_code = to_string(answer_weather_JSON["current"]["weather_code"]);
        weather_json.current.wind_speed_10m = to_string(answer_weather_JSON["current"]["wind_speed_10m"]);

        weather_json.hourly_units.time = to_string(answer_weather_JSON["hourly_units"]["time"]);
        weather_json.hourly_units.temperature_2m = to_string(answer_weather_JSON["hourly_units"]["temperature_2m"]);
        weather_json.hourly_units.relative_humidity_2m = to_string(
                answer_weather_JSON["hourly_units"]["relative_humidity_2m"]);
        weather_json.hourly_units.apparent_temperature = to_string(
                answer_weather_JSON["hourly_units"]["apparent_temperature"]);
        weather_json.hourly_units.weather_code = to_string(answer_weather_JSON["hourly_units"]["weather_code"]);
        weather_json.hourly_units.wind_speed_10m = to_string(answer_weather_JSON["hourly_units"]["wind_speed_10m"]);

        clearJSON();

        for (int i = 0; i < Hours_of_day * stoi(to_string(config_JSON["amountOfDays"])); ++i) {
            weather_json.hourly.time.push_back(to_string(answer_weather_JSON["hourly"]["time"][i]));
            weather_json.hourly.temperature_2m.push_back(to_string(answer_weather_JSON["hourly"]["temperature_2m"][i]));
            weather_json.hourly.relative_humidity_2m.push_back(
                    to_string(answer_weather_JSON["hourly"]["relative_humidity_2m"][i]));
            weather_json.hourly.apparent_temperature.push_back(
                    to_string(answer_weather_JSON["hourly"]["apparent_temperature"][i]));
            weather_json.hourly.weather_code.push_back(to_string(answer_weather_JSON["hourly"]["weather_code"][i]));
            weather_json.hourly.wind_speed_10m.push_back(to_string(answer_weather_JSON["hourly"]["wind_speed_10m"][i]));
        }
    } else {
        status_code_weather = response_weather.status_code;
    }
}

void controller::clearJSON() {
    weather_json.hourly.time.clear();
    weather_json.hourly.temperature_2m.clear();
    weather_json.hourly.relative_humidity_2m.clear();
    weather_json.hourly.apparent_temperature.clear();
    weather_json.hourly.weather_code.clear();
    weather_json.hourly.wind_speed_10m.clear();
}