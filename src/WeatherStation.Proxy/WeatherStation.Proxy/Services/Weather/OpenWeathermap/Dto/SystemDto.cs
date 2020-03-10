using Newtonsoft.Json;

namespace WeatherStation.Proxy.Services.Weather.OpenWeathermap.Dto
{
    class SystemDto
    {
        [JsonProperty("type")]
        public int Type { get; set; }
            
        [JsonProperty("id")]
        public int Id { get; set; }
            
        [JsonProperty("message")]
        public double Message { get; set; }

        [JsonProperty("country")]
        public string Country { get; set; }
        
        [JsonProperty("sunrise")]
        public long Sunrise { get; set; }
        
        [JsonProperty("sunset")]
        public long Sunset { get; set; }
    }
}