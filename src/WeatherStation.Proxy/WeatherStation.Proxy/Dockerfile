FROM mcr.microsoft.com/dotnet/core/aspnet:2.2-stretch-slim AS base
WORKDIR /app
EXPOSE 80

FROM mcr.microsoft.com/dotnet/core/sdk:2.2-stretch AS build
WORKDIR /src
COPY ["WeatherStation.Proxy/WeatherStation.Proxy.csproj", "WeatherStation.Proxy/"]
RUN dotnet restore "WeatherStation.Proxy/WeatherStation.Proxy.csproj"
COPY . .
WORKDIR "/src/WeatherStation.Proxy"
RUN dotnet build "WeatherStation.Proxy.csproj" -c Release -o /app

FROM build AS publish
RUN dotnet publish "WeatherStation.Proxy.csproj" -c Release -o /app

FROM base AS final
WORKDIR /app
COPY --from=publish /app .
ENTRYPOINT ["dotnet", "WeatherStation.Proxy.dll"]