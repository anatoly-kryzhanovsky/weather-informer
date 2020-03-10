namespace WeatherStation.Proxy.Services
{
    interface ITranslatorFactory
    {
        ITranslator<TSource, TDestination> GetTranslator<TSource, TDestination>();
    }
}