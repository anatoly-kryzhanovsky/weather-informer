using Newtonsoft.Json;

namespace WeatherStation.Proxy.Services.Weather.OpenWeathermap.Dto
{
    class CityDto
    {
        [JsonProperty("id")]
        public int Id { get; set; }

        [JsonProperty("name")]
        public string Name { get; set; }

        [JsonProperty("coord")]
        public LocationDto Location { get; set; }

        [JsonProperty("country")]
        public string CountryCode { get; set; }

        [JsonProperty("timezone")]
        public int TimezoneOffset { get; set; }
    }
}