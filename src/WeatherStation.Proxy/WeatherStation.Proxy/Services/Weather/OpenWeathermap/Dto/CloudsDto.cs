using Newtonsoft.Json;

namespace WeatherStation.Proxy.Services.Weather.OpenWeathermap.Dto
{
    class CloudsDto
    {
        [JsonProperty("all")]
        public int All { get; set; }
    }
}