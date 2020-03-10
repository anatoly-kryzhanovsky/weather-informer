using System;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using WeatherStation.Proxy.Services.Weather;

namespace WeatherStation.Proxy.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class WeatherController : ControllerBase
    {
        private readonly ILogger<WeatherController> _logger;
        private readonly IWeatherProviderFactory _weatherProviderFactory;

        public WeatherController(
            ILogger<WeatherController> logger,
            IWeatherProviderFactory weatherProviderFactory)
        {
            _logger = logger;
            _weatherProviderFactory = weatherProviderFactory;
        }

        [Route("current")]
        [HttpGet]
        public async Task<IActionResult> GetCurrentWeather()
        {
            _logger.LogTrace("Request for current weather from {ClientAddress}", Request.HttpContext.Connection.RemoteIpAddress);

            var provider = _weatherProviderFactory.Current.Value;
            var weather = await provider.GetCurrentWeather();

            return new JsonResult(weather);
        }

        [Route("forecast")]
        [HttpGet]
        public async Task<IActionResult> GetForecastedWeather([FromQuery] DateTime to)
        {
            _logger.LogTrace("Request for forecasted weather from {ClientAddress}", Request.HttpContext.Connection.RemoteIpAddress);

            var provider = _weatherProviderFactory.Current.Value;
            var weather = await provider.GetForecastWeather();

            weather = weather
                .TakeWhile(x => x.Date < to)
                .ToArray();

            return new JsonResult(weather);
        }
    }
}
