/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   truck.cpp
 * Author: arpad
 * 
 * Created on May 30, 2024, 8:56 AM
 */

#include <iostream>

#include "truck.h"

using namespace std;

truck::truck() {
    tripCount = 0;
    timeAtMine = 0;
    timeLoading = timeTraveling = timeWaiting = timeUnloading = -1;
    assignedStation = -1; queueSize = -1;
    setTruckState(truckState::ARRIVED_AT_MINE);
}

/*
truck::truck(const truck& orig) {
}
*/

truck::~truck() {
}

void truck::setLoadingTime () {
    loadingTime = 60*(max(rand() % (MAX_LOADING_TIME+1),1));
    cout << "Truck loading time set to: " << loadingTime << " minutes" << endl;
}

void truck::setStation (int stationNumber) {
    assignedStation = stationNumber;
}

void truck::setQueueSize (int vehCount) {
    queueSize = vehCount;
}

int truck::getLoadingTime () {
    return loadingTime;
}

void truck::setTruckState (truckState its) {
    ts = its;
}

int truck::getTruckState () {
    return (int)ts;
}

int truck::getAssignedStation () {
    return assignedStation;
}

int truck::getQueueSize() {
    return queueSize;
}

int truck::updateTruckState () {
    int retCode = 0;
    switch (ts) {
        case truckState::HEADING_TO_MINE:
            // Have we reached the mine
            if (timeTraveling < travelTime) {
                // Still Traveling; increment time traveling
                timeTraveling++;
            }
            else {
                // Reached the mine
                timeTraveling = -1;
                setTruckState (truckState::ARRIVED_AT_MINE);
            }
            break;
        case truckState::ARRIVED_AT_MINE:
            // Generate time required for loading H3
            // Assuming the loading time is different during different trips
            setLoadingTime();
            setTruckState (truckState::LOADING_H3);
            timeLoading++;
            break;
        case truckState::LOADING_H3:
            // Are we finished loading?
            if (timeLoading < loadingTime) {
                // Still loading
                timeLoading++; timeAtMine++;
            }
            else {
                // Finished loading; start traveling to station
                timeLoading = -1;
                setTruckState (truckState::HEADING_TO_STATION);
                timeTraveling++;
            }
            break;
        case truckState::HEADING_TO_STATION:
            // Have we reached the station
            if (timeTraveling < travelTime) {
                // Still Traveling; increment trip travel time
                timeTraveling++;
            }
            else {
                // Reached the station
                timeTraveling = -1;
                setTruckState (truckState::ARRIVED_AT_STATION);
            }
            break;
        case truckState::ARRIVED_AT_STATION:
            tripCount++;
            if (queueSize == 0) {
                // There are no other trucks, start unloading
                setTruckState (truckState::UNLOADING_H3);
            }
            else {
                // There are other trucks ahead of us, wait for queue to empty
                setTruckState (truckState::WAITING_AT_STATION);
            }
            break;
        case truckState::WAITING_AT_STATION:
            // Is wait over
            if (queueSize == 0) {
                // Wait is over, start unloading
                setTruckState (truckState::UNLOADING_H3);
            }
            else {
                // The queue is not empty; wait
                waitTime++;
            }
            break;
        case truckState::UNLOADING_H3:
            // Have completed unloading
            if (timeUnloading < unloadingTime) {
                // Increment time spent unloading
                timeUnloading++;
            }
            else {
                // Process unloading completed state
                timeUnloading = -1;
                setTruckState (truckState::DEPARTING_STATION);
            }
            break;
        case truckState::DEPARTING_STATION:
            setTruckState (truckState::HEADING_TO_MINE);
            break;
        default:
            retCode = 1;
            break;
    }
    return retCode;
}

void truck::reportPerformance () {
    cout << "Number of trips completed: " << tripCount << endl;
    cout << "Time spent loading H3: " << timeAtMine << " minutes" << endl;
    cout << "Total time waited at unload stations: " << waitTime << " minutes" << endl << endl;
}