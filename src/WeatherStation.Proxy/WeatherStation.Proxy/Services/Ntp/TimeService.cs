using System;
using System.Threading.Tasks;
using Yort.Ntp;

namespace WeatherStation.Proxy.Services.Ntp
{
    class TimeService: ITimeService
    {
        private const string NtpSource = "88.147.254.232";
        private readonly NtpClient _client;

        public TimeService()
        {
            _client = new Yort.Ntp.NtpClient(NtpSource);
        }

        public async Task<DateTime> GetTime()
        {
            var time = await _client.RequestTimeAsync();
            return time.NtpTime;
        }
    }
}
