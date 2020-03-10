using System;

namespace WeatherStation.Proxy.Services.Weather
{
    public class Weather
    {
        public DateTime Date { get; set; }
        public WeatherType Type { get; set; }
        public int Temperature { get; set; }
        public double WindSpeed { get; set; }
        public WindDirection WindDirection { get; set; }
    }
}