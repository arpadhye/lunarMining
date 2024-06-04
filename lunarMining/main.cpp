/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: arpad
 *
 * Created on May 30, 2024, 8:50 AM
 */

#include <iostream>
#include <cstdlib>

#include "lunarMining.h"
#include "truck.h"
#include "unloadStation.h"

using namespace std;

/*
 * 
 */

int truckCount; // Total number of trucks in the scenario
int stationCount; // Total number of unloading station in the scenario
const int scenarioDuration = 60*72; // Test scenario duration (72 hours) in minutes
int assignStation;  // Station to be used by the truck
int queueSize;   // Truck queue count at the station to be used by the truck

int main(int argc, char** argv) {

    cout << "Lunar Helium-3 Mining Operation" << endl;
    
    switch (argc) {
        case 1:
            // Get user inputs (truck count and unloading station count from user
            cout << "How many trucks in this case? ";
            cin  >> truckCount;
            cout << "How many unloading stations in this case? ";
            cin  >> stationCount;
            break;
        case 2:
            // Assuming truck count was given as an argument
            truckCount = atoi(argv[1]);
            cout << "How many unloading stations in this case? ";
            cin  >> stationCount;
            break;
        case 3:
            // Both truck and station counts were provided as arguments
            truckCount = atoi(argv[1]);
            stationCount = atoi(argv[2]);
            break;
        default:
            // Too many arguments provided, using only the first two
            cout << "Too many arguments were provided." << endl;
            cout << "Only first two will be used as truckCount and stationCount, respectively." << endl;
            truckCount = atoi(argv[1]);
            stationCount = atoi(argv[2]);
            break;
    }
    
    cout << endl << "There are " << truckCount << " truck(s) and "
        << stationCount << " unloading station(s)." << endl;
    cout << "Scenario duration is " << scenarioDuration << " minutes." << endl;
    
// Create user specified number of trucks and unloading stations
    truck veh[truckCount];
    unloadStation unloadStations[stationCount];
    
// Initialize random number generator
    srand(time(0));
    
    for (currentTime = 0; currentTime <= scenarioDuration; currentTime++) {
        for (int i=0; i<truckCount; i++) {
            int errorCode = 0;

            // Has the truck just arrived at the station?
            int currentTruckState = veh[i].getTruckState();
            
            if (currentTruckState == 10) {  // truckState::ARRIVED_AT_STATION = 10
                // Just arrived at the unload stations
                // Identify unload station with least wait time
                for (int i=0; i<stationCount; i++) {
                    int usTruckCount = unloadStations[i].getVehCount();
                    if (usTruckCount < queueSize) {
                        assignStation = i;
                        queueSize = usTruckCount;
                        break;
                    }
                }
                
                // Direct the truck to the station with least wait time
                veh[i].setStation(assignStation);
                veh[i].setQueueSize(queueSize);
                
                // Increment vehicle queue size for the station
                unloadStations[assignStation].incrementQueue();
                queueSize = unloadStations[assignStation].getVehCount();
            }
                
            if (errorCode = veh[i].updateTruckState() > 0) {
                // updateTruckState returned with an error
                cout << "Truck: " << i << " returned with errorCode = " << errorCode << endl;
                return errorCode;                    
            }

            // Check if truck is done unloading H3
            if (veh[i].getTruckState() == 15) {
                // Truck is departing assigned station
                int as = veh[i].getAssignedStation();
                unloadStations[as].decrementQueue();
                // Reset assigned station and queueSize of the departing truck
                veh[i].setStation(-1);
                veh[i].setQueueSize(-1);
                for (int j = 0; j<truckCount; j++) {
                    if (j != i) {
                        if (veh[j].getAssignedStation() == as) {
                            veh[j].setQueueSize(veh[j].getQueueSize() - 1);
                        }
                    }
                }
                if (int errorCode = veh[i].updateTruckState() > 0) {
                    cout << "Truck: " << i+1 << " returned with errorCode = " << errorCode << endl;
                    return errorCode;
                }
            }
        }
    }
    
    // Scenario simulation complete, generate reports
    // General performance
    
    // Performance of each truck
    for (int i=0; i<truckCount; i++) {
        cout << "Truck " << i+1 << " performance report" << endl;
        veh[i].reportPerformance();
    }
}