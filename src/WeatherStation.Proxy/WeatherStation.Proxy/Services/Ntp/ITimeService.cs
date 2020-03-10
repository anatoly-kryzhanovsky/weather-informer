using System;
using System.Threading.Tasks;

namespace WeatherStation.Proxy.Services.Ntp
{
    public interface ITimeService
    {
        Task<DateTime> GetTime();
    }
}