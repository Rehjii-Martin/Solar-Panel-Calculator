#include <iostream>
#include <string>
#include <map>
#include <cmath>

std::string mapClimateZoneToSunZone(const std::string& climateZone) {
    if (climateZone == "Northern") return "Zone 5";
    else if (climateZone == "Central") return "Zone 3";
    else if (climateZone == "Southern") return "Zone 1";
    else return "Unknown";
}

void listStatesInClimateZones() {
    std::map<std::string, std::string> statesToZones = {
        {"Northern", "Maine, New Hampshire, Vermont, New York, Wisconsin, Michigan, North Dakota, Montana, Washington, Oregon, Idaho"},
        {"Central", "Pennsylvania, Ohio, Indiana, Illinois, Iowa, Nebraska, Wyoming, Colorado, Utah, Nevada"},
        {"Southern", "California, Arizona, New Mexico, Texas, Oklahoma, Arkansas, Louisiana, Mississippi, Alabama, Georgia, Florida, South Carolina, North Carolina, Tennessee, Kentucky, Virginia, Maryland, Delaware, New Jersey"}
    };

    std::cout << "Climate Zones and Corresponding States:" << std::endl;
    for (const auto& pair : statesToZones) {
        std::cout << pair.first << " Zone: " << pair.second << std::endl << std::endl;
    }
}

int calculateSolarPanels(double powerUsage, const std::string& sunZone) {
    // Constants & Double/Float values
    const double solarPanelWattage = 300; // Average wattage per solar panel
    const double sunHoursZone1 = 6.0; // Assumed average sun hours, Zone 1 & 2
    const double sunHoursZone3 = 5.0; // Assumed average sun hours, Zone 3 & 4
    const double sunHoursZone5 = 4.0; // Assumed average sun hours, Zone 5,6,7
    double sunHours = 0.0;

    if (sunZone == "Zone 1") sunHours = sunHoursZone1;
    else if (sunZone == "Zone 3") sunHours = sunHoursZone3;
    else if (sunZone == "Zone 5") sunHours = sunHoursZone5;
    else {
        std::cerr << "Invalid sun zone." << std::endl; //Error Resolution
        return -1;
    }

    double dailyProductionPerPanel = solarPanelWattage * sunHours / 1000; // kWh
    return static_cast<int>(std::ceil(powerUsage / dailyProductionPerPanel));
}

int main() {
    std::string climateZone;
    char listStates;
    double powerUsage;

    std::cout << "Do you want to see a list of states for each climate zone? (Y/N): ";
    std::cin >> listStates;
    if (listStates == 'Y' || listStates == 'y') {
        listStatesInClimateZones();
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
    std::cout << "Enter your climate zone (Northern, Central, Southern): ";
    std::getline(std::cin, climateZone);

    std::string sunZone = mapClimateZoneToSunZone(climateZone);
    if (sunZone == "Unknown") {
        std::cerr << "Invalid climate zone entered." << std::endl;
        return 1;
    }

    std::cout << "Enter your daily power usage in kWh: ";
    std::cin >> powerUsage;
    if (std::cin.fail() || powerUsage < 0) {
        std::cerr << "Invalid power usage input." << std::endl;
        return 1;
    }

    int requiredPanels = calculateSolarPanels(powerUsage, sunZone);
    if (requiredPanels >= 0) {
        std::cout << "Based on your power usage and climate zone, you will need approximately " 
                  << requiredPanels << " solar panels." << std::endl;
    }

    return 0;
}
