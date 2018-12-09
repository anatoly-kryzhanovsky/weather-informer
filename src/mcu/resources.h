#pragma once

class Resources
{
public:
    static unsigned char IconSun[];
    static unsigned char IconCloud[];
    static unsigned char IconRainLight[];
    static unsigned char IconRainHeavy[];
    static unsigned char IconCloudLight[];
    static unsigned char IconSnowLight[];
    static unsigned char IconSnowHeavy[];
    static unsigned char IconRainAndSnow[];
    static unsigned char IconThunderstorm[];  
    static unsigned char IconUnknow[];

public:
    static unsigned char* getIcon(int weatherCode);
};
