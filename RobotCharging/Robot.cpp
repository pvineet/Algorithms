#include "Robot.h"

Robot::Robot(int id, RobotQueue& robotQueue, int dischargeIntervalMs, int chargeIntervalMs):
	m_chargeLevel(100),
	m_id(id),
	m_running(false),
	m_isPlugged(false),
	m_robotQueue(robotQueue),
	m_plugThreshold(30),
	m_unplugThreshold(90),
	m_chargeIntervalMs(chargeIntervalMs),
	m_dischargeIntervalMs(dischargeIntervalMs)
{
	std::cout << "Robot " << m_id << " created." << std::endl;
}

Robot::~Robot()
{
}

void Robot::run()
{
	bool isQueued = false;
	std::cout << "Running Robot " << m_id << std::endl;
	while (m_running) {
		m_plugMutex.lock();
		bool isPlugged = m_isPlugged;
		m_plugMutex.unlock();
		if (!isPlugged) {
			discharge();
			if (!isQueued && m_chargeLevel < m_plugThreshold) {
				addRobotToQueue();
				isQueued = true;
			}
			
			if(m_chargeLevel%10 == 0 && !isQueued)
				std::cout << "Robot " << m_id << " charge " << m_chargeLevel<<std::endl;
		}
		else {
			isQueued = false;
			charge();
		}
		if (!isPlugged)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(m_dischargeIntervalMs));
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(m_chargeIntervalMs));
		}		
	}
}

void Robot::start()
{
	m_running = true;
	run();
}

void Robot::stop()
{
	m_running = false;
}

bool Robot::isCharged()
{
	std::lock_guard<std::mutex> lock(m_chargeMutex);
	return m_chargeLevel > m_unplugThreshold;
}

void Robot::discharge()
{ 
	std::lock_guard<std::mutex> lock(m_chargeMutex);
	if (m_chargeLevel > 0)
		m_chargeLevel--;
}

void Robot::charge() 
{
	std::lock_guard<std::mutex> lock(m_chargeMutex);
	if (m_chargeLevel < 100)
		m_chargeLevel++;
}

void Robot::addRobotToQueue()
{
	m_robotQueue.push(m_id,
		[this]() {
			std::cout << "Robot " << m_id << " plugged in."<<std::endl;
			std::lock_guard<std::mutex> lock(m_plugMutex);
			m_isPlugged = true;
		},
		[this]() {
			std::cout << "Robot " << m_id << " unplugged."<<std::endl;
			std::lock_guard<std::mutex> lock(m_plugMutex);
			m_isPlugged = false;
		},
		std::bind(&Robot::isCharged, this));
}
