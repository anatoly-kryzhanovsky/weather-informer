using Newtonsoft.Json;

namespace WeatherStation.Proxy.Services.Weather.OpenWeathermap.Dto
{
    class WindDto
    {
        [JsonProperty("deg")]
        public double Degree { get; set;}

        [JsonProperty("speed")]
        public double Speed { get; set;}
    }
}