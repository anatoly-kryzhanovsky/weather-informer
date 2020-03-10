using System.Collections.Generic;
using System.Threading.Tasks;

namespace WeatherStation.Proxy.Services.Weather
{
    public interface IWeatherProvider
    {
        Task<Weather> GetCurrentWeather();
        Task<IReadOnlyCollection<Weather>> GetForecastWeather();
    }
}
