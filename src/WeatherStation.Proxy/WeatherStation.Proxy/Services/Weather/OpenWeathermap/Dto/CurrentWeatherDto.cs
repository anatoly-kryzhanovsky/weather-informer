using Newtonsoft.Json;

namespace WeatherStation.Proxy.Services.Weather.OpenWeathermap.Dto
{
    class CurrentWeatherDto
    {
        [JsonProperty("coord")]
        public LocationDto Location { get; set; }

        [JsonProperty("wind")]
        public WindDto Wind { get; set; }

        [JsonProperty("main")]
        public WeatherMainDto Main { get; set;}

        [JsonProperty("weather")]
        public WeatherDto[] Weather { get; set; }

        [JsonProperty("visibility")]
        public int Visibility { get; set; }

        [JsonProperty("clouds")]
        public CloudsDto Clouds { get; set; }

        [JsonProperty("dt")]
        public long Dt { get; set; }

        [JsonProperty("sys")]
        public SystemDto System { get; set; }

        [JsonProperty("id")]
        public int Id { get; set; }
        
        [JsonProperty("name")]
        public string Name { get; set; }
        
        [JsonProperty("cod")]
        public int Code { get; set; }
    }
}