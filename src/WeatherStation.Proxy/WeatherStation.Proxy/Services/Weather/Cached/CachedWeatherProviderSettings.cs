using System;

namespace WeatherStation.Proxy.Services.Weather.Cached
{
    class CachedWeatherProviderSettings
    {
        public TimeSpan RefreshTime { get; set; }
        public WeatherProviderType InternalType { get; set; }
    }
}