using System.Collections.Generic;
using System.Threading.Tasks;
using Microsoft.Extensions.Caching.Memory;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;

namespace WeatherStation.Proxy.Services.Weather.Cached
{
    class CachedWeatherProvider: IWeatherProvider
    {
        private const string CurrentWeatherKey = "weather_current";
        private const string ForecastWeatherKey = "weather_forecast";

        private readonly ILogger<IWeatherProvider> _logger;
        private readonly IMemoryCache _memoryCache;
        private readonly IOptions<CachedWeatherProviderSettings> _settings;
        private readonly IWeatherProvider _internalProvider;

        public CachedWeatherProvider(
            ILogger<IWeatherProvider> logger,
            IWeatherProviderFactory weatherProviderFactory,
            IMemoryCache memoryCache,
            IOptions<CachedWeatherProviderSettings> settings)
        {
            _internalProvider = weatherProviderFactory.GetWeatherProvider(settings.Value.InternalType);
            _logger = logger;
            _memoryCache = memoryCache;
            _settings = settings;
        }

        public async Task<Weather> GetCurrentWeather()
        {
            if (!_memoryCache.TryGetValue(CurrentWeatherKey, out var weather))
            {
                _logger.LogTrace("Current weather missed in cache, update from underline provider...");

                weather = await _internalProvider.GetCurrentWeather();
                _memoryCache.Set(CurrentWeatherKey, weather, _settings.Value.RefreshTime);
            }

            return (Weather) weather;
        }

        public async Task<IReadOnlyCollection<Weather>> GetForecastWeather()
        {
            if (!_memoryCache.TryGetValue(ForecastWeatherKey, out var weather))
            {
                _logger.LogTrace("Forecasted weather missed in cache, update from underline provider...");

                weather = await _internalProvider.GetForecastWeather();
                _memoryCache.Set(ForecastWeatherKey, weather, _settings.Value.RefreshTime);
            }

            return (IReadOnlyCollection<Weather>)weather;
        }
    }
}
