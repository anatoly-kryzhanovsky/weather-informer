using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Threading.Tasks;
using Flurl;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;
using WeatherStation.Proxy.Services.Weather.OpenWeathermap.Dto;

namespace WeatherStation.Proxy.Services.Weather.OpenWeathermap
{
    class OpenWeathermapWeatherProvider: IWeatherProvider
    {
        private const string Endpoint = "https://api.openweathermap.org";

        private readonly ILogger<IWeatherProvider> _logger;
        private readonly IOptions<OpenWeathermapSettings> _settings;
        private readonly IHttpClientFactory _httpFactory;
        private readonly ITranslatorFactory _translatorFactory;

        public OpenWeathermapWeatherProvider(
            ILogger<IWeatherProvider> logger,
            IOptions<OpenWeathermapSettings> settings, 
            IHttpClientFactory httpFactory,
            ITranslatorFactory translatorFactory)
        {
            _logger = logger;
            _settings = settings;
            _httpFactory = httpFactory;
            _translatorFactory = translatorFactory;
        }

        public async Task<Weather> GetCurrentWeather()
        {
            var client = _httpFactory.CreateClient();
            client.BaseAddress = new Uri(Endpoint, UriKind.Absolute);

            try
            {
                var response = await client.GetAsync(
                    "/data/2.5/weather"
                        .SetQueryParams(new
                        {
                            id = _settings.Value.CityId,
                            appId = _settings.Value.Key,
                            units = "metric"
                        }));

                if (response.IsSuccessStatusCode)
                {
                    var weather = await response.Content.ReadAsAsync<CurrentWeatherDto>();
                    return _translatorFactory
                        .GetTranslator<CurrentWeatherDto, Weather>()
                        .Translate(weather);
                }

                _logger.LogWarning("Cannot get weather from server. Response code: {ResponseCode}, Additional message: {Message}", response.StatusCode, response.ReasonPhrase);
                return null;
            }
            catch (Exception e)
            {
                _logger.LogWarning("Cannot get weather from server. Exception message: {Message}", e.Message);
                return null;
            }
        }

        public async Task<IReadOnlyCollection<Weather>> GetForecastWeather()
        {
            var client = _httpFactory.CreateClient();
            client.BaseAddress = new Uri(Endpoint, UriKind.Absolute);

            try
            {
                var response = await client.GetAsync(
                    "/data/2.5/forecast"
                        .SetQueryParams(new
                        {
                            id = _settings.Value.CityId,
                            appId = _settings.Value.Key,
                            units = "metric"
                        }));

                if (response.IsSuccessStatusCode)
                {
                    var weather = await response.Content.ReadAsAsync<ForecastedWeatherDto>();
                    var translator = _translatorFactory.GetTranslator<ForecastItemDto, Weather>();

                    return weather.Items
                        .Select(translator.Translate)
                        .ToArray();
                }

                _logger.LogWarning("Cannot get weather from server. Response code: {ResponseCode}, Additional message: {Message}", response.StatusCode, response.ReasonPhrase);
                return null;
            }
            catch (Exception e)
            {
                _logger.LogWarning("Cannot get weather from server. Exception message: {Message}", e.Message);
                return null;
            }
        }
    }
}