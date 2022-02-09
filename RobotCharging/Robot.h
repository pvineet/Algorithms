#pragma once
#include <mutex>
#include <thread>
#include <iostream>
#include <chrono>
#include <atomic>
#include "RobotQueue.h"

class Robot
{
public:
	Robot(int id, 
		RobotQueue& robotQueue,
		int dischargeIntervalMs,
		int chargeIntervalMs);
	~Robot();
	void run();
	void start();
	void stop();
	bool isCharged();
private:
	void discharge();
	void charge();
	void addRobotToQueue();
	int m_chargeLevel;
	int m_id;
	std::mutex m_plugMutex;
	std::mutex m_chargeMutex;
	std::atomic<bool> m_running;
	bool m_isPlugged;
	RobotQueue& m_robotQueue;
	int m_plugThreshold;
	int m_unplugThreshold;
	int m_dischargeIntervalMs;
	int m_chargeIntervalMs;
};

