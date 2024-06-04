/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   truck.h
 * Author: arpad
 *
 * Created on May 30, 2024, 8:56 AM
 */

#ifndef TRUCK_H
#define TRUCK_H

#include "lunarMining.h"

class truck {
public:
    truck();
//    truck(const truck& orig);
    virtual ~truck();

    void setLoadingTime ();
    void setStation (int);
    void setQueueSize (int);
    int updateTruckState ();

    int getLoadingTime ();
    int getTruckState ();
    int getAssignedStation ();
    int getQueueSize();
    
    void reportPerformance ();
private:
    
    // Truck state at any given time
    enum class truckState : unsigned int {
        HEADING_TO_MINE,
        ARRIVED_AT_MINE,
        LOADING_H3,
        HEADING_TO_STATION,
        ARRIVED_AT_STATION = 10,
        WAITING_AT_STATION,
        UNLOADING_H3,
        DEPARTING_STATION = 15
    };
    
    enum class truckErrorCode : unsigned int {
        NONE,
        INCORRECT_TRAVEL_DIRECTION,
        
    };

    // Truck travel time between mining site and unloading station, default 30 minutes
    const int travelTime = 1800;
    // Time to unload H3 at unloading station, default 5 minutes
    const int unloadingTime = 300;
    
    truckState ts;
    truckErrorCode te;
    int assignedStation, queueSize;
    int loadingTime;
    int timeLoading, timeTraveling, timeWaiting, timeUnloading;
    
    // Performance data
    int tripCount;  //Total number of trips during the scenario
    // timeAtMine: total time spent at the mine to load H3
    // waitTime: total time spent waiting at the unload station
    
    int timeAtMine, waitTime = 0;
    
    void setTruckState (truckState its);

};

#endif /* TRUCK_H */

