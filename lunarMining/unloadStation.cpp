/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   unloadStation.cpp
 * Author: arpad
 * 
 * Created on May 30, 2024, 9:04 AM
 */

#include <iostream>

#include "unloadStation.h"

using namespace std;

unloadStation::unloadStation() {
    vehCount = 0;
}

/*
unloadStation::unloadStation(const unloadStation& orig) {
}
*/

unloadStation::~unloadStation() {
}

int unloadStation::getVehCount() {
    return vehCount;
}

void unloadStation::incrementQueue () {
    vehCount++;
}

void unloadStation::decrementQueue () {
    vehCount--;
}
