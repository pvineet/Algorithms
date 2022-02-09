#include "ChargingStation.h"

ChargingStation::ChargingStation(RobotQueue& q, int numStations)
	:m_robotQueue(q),
	m_numStations(numStations)
{
}

ChargingStation::~ChargingStation()
{
}

void ChargingStation::start()
{
	m_running = true;
	// std::thread th(&ChargingStation::run, this);
	// th.join();
	run();
}

void ChargingStation::stop()
{
	m_running = false;
}

void ChargingStation::run()
{
	while (m_running) {
		
		if (!m_robotQueue.isEmpty() && chargingPoints.size() < m_numStations) {
			auto robot = m_robotQueue.pop();
			robot.plugCallback();
			chargingPoints.push(robot);
		}
		
		if (!chargingPoints.empty()) {
			auto robot = chargingPoints.front();
			if (robot.isChargedCallback()) {
				chargingPoints.front().unplugCallback();
				chargingPoints.pop();
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}
