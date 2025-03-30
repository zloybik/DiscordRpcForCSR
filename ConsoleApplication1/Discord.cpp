#define WIN32_LEAN_AND_MEAN
#include <chrono>
#include <iostream>
#include <algorithm>
#include "Discord.h"

static int64_t eptime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}

void Discord::Initialize()
{
    DiscordEventHandlers Handle;
    memset(&Handle, 0, sizeof(Handle));
    Discord_Initialize("Set your app id here", &Handle, 1, NULL); 
}

void Discord::Update()
{
    std::string state1 = getStatus();
    std::string icon = getIcon();
    std::string smallIcon = toLower(getSmallicon());
    std::string deatils = getdeatils();
    std::string largetext = getLargetext();
    std::string smalltext = getSmalltext();

    // Copy Your Api Pre-Visualize
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.state = deatils.c_str();
    discordPresence.details = state1.c_str();
    discordPresence.startTimestamp = eptime;
    discordPresence.largeImageKey = icon.c_str();
    discordPresence.smallImageKey = smallIcon.c_str();
    discordPresence.smallImageText = smalltext.c_str();
    discordPresence.largeImageText = largetext.c_str();
    Discord_UpdatePresence(&discordPresence);
}
