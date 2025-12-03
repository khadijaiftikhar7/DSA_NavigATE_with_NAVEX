#pragma once
#include <string>

struct WeatherInfo
{
    bool isRain = false;
    bool isStorm = false;
    bool isFlood = false;

    double rainVolume = 0.0;
    std::string condition = "Clear";
};

class WeatherManager
{
private:
    std::string apiKey;

public:
    WeatherManager(const std::string& apiKey);
    
    // Fetch real weather (JSON) and convert into WeatherInfo
    WeatherInfo fetchWeather(double lat, double lon);
};
