using System;
using System.Linq;
using WeatherStation.Proxy.Services.Weather.OpenWeathermap.Dto;

namespace WeatherStation.Proxy.Services.Weather.OpenWeathermap.Translators
{
    class CurrentWeatherDtoToWeatherTranslator: ITranslator<CurrentWeatherDto, Weather>
    {
        private static readonly DateTime UnixEpoch = new DateTime(1970, 1, 1, 0, 0, 0, 0, System.DateTimeKind.Utc);

        public Weather Translate(CurrentWeatherDto dto)
        {
            return new Weather
            {
                WindSpeed = dto.Wind.Speed,
                Temperature = GetTemperature(dto.Main.Temperature),
                Date = GetDate(dto.Dt),
                WindDirection = GetWindDirection(dto.Wind.Degree),
                Type = GetWeatherType(dto.Weather.FirstOrDefault()?.Id ?? 0)
            };
        }

        private DateTime GetDate(long unixTime)
        {
            return UnixEpoch.AddSeconds(unixTime);
        }

        private int GetTemperature(double temperature)
        {
            return (int) temperature;
        }

        private WindDirection GetWindDirection(double direction)
        {
            if (direction > 22.5 && direction <= 67.5)
                return WindDirection.NorthWest;

            if (direction > 67.5 && direction <= 112.5)
                return WindDirection.West;

            if (direction > 112.5 && direction <= 157.5)
                return WindDirection.SouthWest;

            if (direction > 157.5 && direction <= 202.5)
                return WindDirection.South;

            if (direction > 202.5 && direction <= 247.5)
                return WindDirection.SouthEast;

            if (direction > 247.5 && direction <= 292.5)
                return WindDirection.East;

            if (direction > 292.5 && direction <= 337.5)
                return WindDirection.NorthEst;

            return WindDirection.North;
        }

        private WeatherType GetWeatherType(int id)
        {
            if (id == 0)
                return WeatherType.Unknown;

            if (id >= 200 && id < 300)
                return WeatherType.RainHeavy;

            if (id >= 300 && id < 400)
                return WeatherType.RainLight;

            if (id >= 500 && id < 600)
                return WeatherType.Rain;

            if (id == 615 || id == 616)
                return WeatherType.RainWithSnow;

            if (id >= 600 && id < 700)
                return WeatherType.Snow;

            if (id == 801)
                return WeatherType.CloudLight;

            if (id > 802)
                return WeatherType.Cloud;

            return WeatherType.Sun;
        }
    }
}
