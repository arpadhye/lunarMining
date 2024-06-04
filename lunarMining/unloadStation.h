/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   unloadStation.h
 * Author: arpad
 *
 * Created on May 30, 2024, 9:04 AM
 */

#ifndef UNLOADSTATION_H
#define UNLOADSTATION_H

class unloadStation {
public:
    unloadStation();
//    unloadStation(const unloadStation& orig);
    virtual ~unloadStation();
    
    int getVehCount();
    void incrementQueue();
    void decrementQueue();
    
private:
    int vehCount;

};

#endif /* UNLOADSTATION_H */

