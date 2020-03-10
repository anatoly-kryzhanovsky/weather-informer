using System;

namespace WeatherStation.Proxy.Services.Weather
{
    public interface IWeatherProviderFactory
    {
        IWeatherProvider GetWeatherProvider(WeatherProviderType providerType);

        Lazy<IWeatherProvider> Current { get; }
    }
}