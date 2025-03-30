#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <time.h>
#include <chrono>
#include <iostream>
#include <httplib.h>
#include <json.hpp>
#include <thread>
#include "Discord.h"

Discord* discord = new Discord();

using json = nlohmann::json;
using namespace std;

int main() {
    discord->Initialize();
    discord->Update();
    httplib::Server svr;

        svr.Post("/game", [](const httplib::Request& req, httplib::Response& res) {
            try {
                json j = json::parse(req.body);
                if (j["player"]["activity"] == "menu") {
                    discord->setStatus("On Menu");
                    discord->setName(j["player"]["name"]);
                    discord->setIcon("icon");
                    discord->setSmallicon("");
                    discord->setSmalltext("");
                    discord->setLargetext("CS:R Logo");
                    discord->setDeatils("");
                }
                else {
                    if (j["map"] != true) {
                        string status = "Playing on " + j["map"]["name"].get<string>();
                        string steamid = j["provider"]["steamid"];
                        discord->setStatus(status);
                        discord->setIcon(j["map"]["name"]);
                        if (j["player"].contains("steamid") && j["player"]["steamid"] == steamid && j["player"].contains("team")) {
                            discord->setSmallicon(j["player"]["team"]);
                            if (j["player"]["team"] == "CT") {
                                discord->setSmalltext("Counter-Terrorist");    
                            }
                            else if(j["player"]["team"] == "T"){
                                discord->setSmalltext("Terrorist");
                            }
                            int kills = j["player"]["match_stats"]["kills"];
                            int deaths = j["player"]["match_stats"]["deaths"];
                            double KD = (deaths == 0) ? static_cast<double>(kills) : (static_cast<double>(kills) / deaths);
                            KD = round(KD * 100) / 100;

                            ostringstream stream;
                            stream << fixed << setprecision(2) << KD;
                            string KD_str = stream.str();
                            discord->setLargetext("Player KD: " + KD_str);
                        }
                        else {
                            discord->setSmallicon("spectate");
                            discord->setSmalltext("Spectator");
                            discord->setLargetext("Player KD: 0.00");
                        }
                        discord->setDeatils(to_string(j["map"]["team_ct"]["score"].get<int>()) + ":" + to_string(j["map"]["team_t"]["score"].get<int>()));
                    }
                }
                res.set_content("JSON received and processed", "text/plain");
                discord->Update();
            }
            catch (const std::exception& e) {
                res.status = 400;
                res.set_content("Invalid JSON", "text/plain");
            }
        });

        svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
            string html = "<html><body> Hello, "+ discord->getName() + " its a listening server for your Discord rpc. Dont worry, its isnt take your FPS!</body></html>";
            res.set_content(html, "text/html");
            });

        cout << "Server listening at http://127.0.0.1:29279" << std::endl;
        svr.listen("127.0.0.1", 29279);

    return 0;
}
