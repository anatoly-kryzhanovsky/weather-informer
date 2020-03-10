using System.Diagnostics;

namespace WeatherStation.Proxy.Services
{
    interface ITranslator<in TSource, out TDestination>
    {
        TDestination Translate(TSource source);
    }
}
