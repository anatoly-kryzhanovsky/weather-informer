using System;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;
using WeatherStation.Proxy.Services.Weather.Cached;
using WeatherStation.Proxy.Services.Weather.OpenWeathermap;

namespace WeatherStation.Proxy.Services.Weather
{
    class WeatherProviderFactory : IWeatherProviderFactory
    {
        private readonly ILogger<IWeatherProviderFactory> _logger;
        private readonly IServiceProvider _serviceProvider;

        public Lazy<IWeatherProvider> Current { get; }

        public WeatherProviderFactory(
            ILogger<IWeatherProviderFactory> logger,
            IServiceProvider serviceProvider,
            IOptions<WeatherProviderSettings> settings)
        {
            _logger = logger;
            _serviceProvider = serviceProvider;

            Current = new Lazy<IWeatherProvider>(() => GetWeatherProvider(settings.Value.ProviderType));
        }

        public IWeatherProvider GetWeatherProvider(WeatherProviderType providerType)
        {
            _logger.LogTrace("Resolve provider for {Type}", providerType);

            switch (providerType)
            {
                case WeatherProviderType.OpenWeathermap:
                    return _serviceProvider.GetService<OpenWeathermapWeatherProvider>();

                case WeatherProviderType.Cached:
                    return _serviceProvider.GetService<CachedWeatherProvider>();

                default:
                    throw new NotSupportedException($"Provider {providerType} not supported");
            }
        }
    }
}