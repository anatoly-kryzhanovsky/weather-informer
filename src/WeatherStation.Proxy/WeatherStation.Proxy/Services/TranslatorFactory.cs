using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Extensions.DependencyInjection;
using WeatherStation.Proxy.Services.Weather.OpenWeathermap.Dto;
using WeatherStation.Proxy.Services.Weather.OpenWeathermap.Translators;

namespace WeatherStation.Proxy.Services
{
    class TranslatorFactory : ITranslatorFactory
    {
        class TranslatorInfo
        {
            public Type Source { get; }
            public Type Destination { get; }
            public Type TranslatorType { get; }

            public TranslatorInfo(Type source, Type destination, Type translatorType)
            {
                Source = source;
                Destination = destination;
                TranslatorType = translatorType;
            }
        }

        private readonly List<TranslatorInfo> _translators;
        private readonly IServiceProvider _serviceProvider;

        public TranslatorFactory(IServiceProvider serviceProvider)
        {
            _serviceProvider = serviceProvider;
            _translators = new List<TranslatorInfo>();

            RegisterTranslator<CurrentWeatherDto, Weather.Weather, CurrentWeatherDtoToWeatherTranslator>();
            RegisterTranslator<ForecastItemDto, Weather.Weather, ForecastItemDtoToWeatherTranslator>();
        }

        protected void RegisterTranslator<TSource, TDestination, TTranslator>()
            where TTranslator: ITranslator<TSource, TDestination>
        {
            _translators.Add(new TranslatorInfo(typeof(TSource), typeof(TDestination), typeof(TTranslator)));
        }

        public ITranslator<TSource, TDestination> GetTranslator<TSource, TDestination>()
        {
            var translatorInfo = _translators.FirstOrDefault(x => x.Source == typeof(TSource) && x.Destination == typeof(TDestination));

            if(translatorInfo == null)
                throw new InvalidOperationException($"Cannot find translator for given type: {typeof(TSource).Name} -> {typeof(TDestination).Name}");

            var translator = ActivatorUtilities.CreateInstance(_serviceProvider, translatorInfo.TranslatorType);
            return (ITranslator<TSource, TDestination>) translator;
        }
    }
}