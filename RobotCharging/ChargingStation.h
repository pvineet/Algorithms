#pragma once

#include <iostream>
#include "RobotQueue.h"
#include <atomic>
#include <thread>
#include <unordered_map>

class ChargingStation
{
public:
	ChargingStation(RobotQueue& q, int numStations);
	~ChargingStation();
	void start();
	void stop();
	void run();
private:
	RobotQueue& m_robotQueue;
	std::atomic<bool> m_running;
	int m_numStations;
	std::queue<QueuedRobot> chargingPoints;
};

