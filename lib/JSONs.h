#include <iostream>
#include <vector>
#include <string>

namespace privateZone {
    struct CurrentUnits {
        std::string time;
        std::string interval;
        std::string temperature_2m;
        std::string relative_humidity_2m;
        std::string apparent_temperature;
        std::string is_day;
        std::string weather_code;
        std::string wind_speed_10m;
    };

    struct Current {
        std::string time;
        std::string interval;
        std::string temperature_2m;
        std::string relative_humidity_2m;
        std::string apparent_temperature;
        std::string is_day;
        std::string weather_code;
        std::string wind_speed_10m;
    };

    struct HourlyUnits {
        std::string time;
        std::string temperature_2m;
        std::string relative_humidity_2m;
        std::string apparent_temperature;
        std::string weather_code;
        std::string wind_speed_10m;
    };

    struct Hourly {
        std::vector<std::string> time;
        std::vector<std::string> temperature_2m;
        std::vector<std::string> relative_humidity_2m;
        std::vector<std::string> apparent_temperature;
        std::vector<std::string> weather_code;
        std::vector<std::string> wind_speed_10m;
    };

}

namespace JSONs {
    struct TownInfo {
        std::string name;
        std::string latitude;
        std::string longitude;
        std::string country;
        std::string population;
        std::string is_capital;
    };

    struct WeatherInfo {
        std::string latitude;
        std::string longitude;
        std::string generationtime_ms;
        std::string utc_offset_seconds;
        std::string timezone;
        std::string timezone_abbreviation;
        std::string elevation;
        privateZone::CurrentUnits current_units;
        privateZone::Current current;
        privateZone::HourlyUnits hourly_units;
        privateZone::Hourly hourly;
    };

}