#pragma once
#include <discord_register.h> //sdk
#include <discord_rpc.h> // sdk
#include <Windows.h> //windows general header

class Discord {
    public:
        std::string status = "On Menu";
        std::string name = "";
        std::string icon = "icon";
        std::string SmallIcon = "";
        std::string deatils = "";
        std::string Smalltext = "";
        std::string Largetext = "CS:R Logo";
        void Initialize();
        void Update();
        // Сеттеры

        void setStatus(const std::string& newStatus) {
            status = newStatus;
        }

        void setIcon(const std::string& newStatus) {
            icon = newStatus;
        }

        void setName(const std::string& newName) {
            name = newName;
        }

        void setSmallicon(const std::string& newName) {
            SmallIcon = newName;
        }

        void setDeatils(const std::string& newName) {
            deatils = newName;
        }

        void setSmalltext(const std::string& newName) {
            Smalltext = newName;
        }

        void setLargetext(const std::string& newName) {
            Largetext = newName;
        }

        // Геттеры
        std::string getStatus() const {
            return status;
        }

        std::string getName() const {
            return name;
        }

        std::string getIcon() const {
            return icon;
        }

        std::string getSmallicon() const {
            return SmallIcon;
        }

        std::string getdeatils() const {
            return deatils;
        }

        std::string getSmalltext() const {
            return Smalltext;
        }

        std::string getLargetext() const {
            return Largetext;
        }
    };
