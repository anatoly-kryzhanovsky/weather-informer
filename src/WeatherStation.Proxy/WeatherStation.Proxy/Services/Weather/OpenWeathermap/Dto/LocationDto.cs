using Newtonsoft.Json;

namespace WeatherStation.Proxy.Services.Weather.OpenWeathermap.Dto
{
    class LocationDto
    {
        [JsonProperty("lat")]
        public double Latitude { get; set; }

        [JsonProperty("lon")]
        public double Longitude { get; set; }
    }
}