using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using WeatherStation.Proxy.Services;
using WeatherStation.Proxy.Services.Weather;
using WeatherStation.Proxy.Services.Weather.Cached;
using WeatherStation.Proxy.Services.Weather.OpenWeathermap;

namespace WeatherStation.Proxy
{
    public class Startup
    {
        public Startup(IConfiguration configuration)
        {
            Configuration = configuration;
        }

        public IConfiguration Configuration { get; }

        public void ConfigureServices(IServiceCollection services)
        {
            services.AddMvc().SetCompatibilityVersion(CompatibilityVersion.Version_2_2);
            services.AddHttpClient();
            services.AddMemoryCache();

            services
                .AddOptions<OpenWeathermapSettings>()
                .Bind(Configuration.GetSection("OpenWeathermapSettings"));

            services
                .AddOptions<CachedWeatherProviderSettings>()
                .Bind(Configuration.GetSection("CachedWeatherProvider"));

            services
                .AddOptions<WeatherProviderSettings>()
                .Bind(Configuration.GetSection("WeatherSettings"));

            services.AddSingleton<ITranslatorFactory, TranslatorFactory>();

            services.AddSingleton<IWeatherProviderFactory, WeatherProviderFactory>();
            services.AddSingleton<OpenWeathermapWeatherProvider>();
            services.AddSingleton<CachedWeatherProvider>();

            services.AddLogging(x => x.AddConsole());
        }

        public void Configure(IApplicationBuilder app, IHostingEnvironment env)
        {
            if (env.IsDevelopment())
            {
                app.UseDeveloperExceptionPage();
            }
            
            app.UseMvc();
        }
    }
}
