using Newtonsoft.Json;

namespace WeatherStation.Proxy.Services.Weather.OpenWeathermap.Dto
{
    class ForecastItemDto
    {
        [JsonProperty("dt")]
        public long Date { get; set; }

        [JsonProperty("main")]
        public WeatherMainDto Main { get; set; }

        [JsonProperty("weather")]
        public WeatherDto[] Weather { get; set; }

        [JsonProperty("clouds")]
        public CloudsDto Clouds { get; set; }

        [JsonProperty("wind")]
        public WindDto Wind { get; set; }

    }
}