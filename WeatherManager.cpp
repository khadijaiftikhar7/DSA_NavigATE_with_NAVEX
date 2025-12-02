#include "WeatherManager.h"
#include "WeatherHttp.h"

#include "include/json.hpp"
using json = nlohmann::json;

WeatherManager::WeatherManager(const std::string& key)
{
    apiKey = key;
}

WeatherInfo WeatherManager::fetchWeather(double lat, double lon)
{
    WeatherInfo info;

    std::string url =
        "https://api.openweathermap.org/data/2.5/weather?lat=" +
        std::to_string(lat) + "&lon=" + std::to_string(lon) +
        "&appid=" + apiKey + "&units=metric";

    std::string body = httpGet(url);

    if (body.empty()) return info;

    json j = json::parse(body);

    if (j.contains("weather"))
    {
        info.condition = j["weather"][0]["main"].get<std::string>();

        if (info.condition == "Rain" || info.condition == "Drizzle")
            info.isRain = true;

        if (info.condition == "Thunderstorm")
            info.isStorm = true;
    }

    if (j.contains("rain") && j["rain"].contains("1h"))
        info.rainVolume = j["rain"]["1h"].get<double>();

    // Flood rule: if rainfall in last hour > 25mm → flood-like condition
    if (info.rainVolume > 25.0)
        info.isFlood = true;

    return info;
}
