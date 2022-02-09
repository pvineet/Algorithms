// RobotCharging.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Robot.h"
#include "RobotQueue.h"
#include "ChargingStation.h"


int main()
{
    std::cout << "Hello World!\n";
    int numRobots = 10;
    RobotQueue roboQ(numRobots);
    Robot r0(0, roboQ, 100, 5);
    Robot r1(1, roboQ, 50, 5);
    Robot r2(2, roboQ, 10, 5);
    Robot r3(3, roboQ, 75, 5);
    ChargingStation chargingStations(roboQ, 2);
    std::vector<Robot> robots;
    std::vector<std::thread> threads;

    std::thread stationsThread(&ChargingStation::start, &chargingStations);
    
    std::thread th0(&Robot::start, &r0);
    std::thread th1(&Robot::start, &r1);
    std::thread th2(&Robot::start, &r2);
    std::thread th3(&Robot::start, &r3);
    

    r0.stop();
    r1.stop();
    r2.stop();
    r3.stop();
    chargingStations.stop();
    th0.join();
    th1.join();
    th2.join();
    th3.join();
    stationsThread.join();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
