#pragma once
#include <mutex>
#include <iostream>
#include <queue>
#include <functional>

struct QueuedRobot {
	QueuedRobot(int id, 
				std::function<void()> plugCallback,
				std::function<void()> unplugCallback,
				std::function<bool()> isChargedCallback)
		:id(id), 
		plugCallback(plugCallback),
		unplugCallback(unplugCallback),
		isChargedCallback(isChargedCallback){
		}

	int id;
	std::function<void()> plugCallback;
	std::function<void()> unplugCallback;
	std::function<bool()> isChargedCallback;
};

class RobotQueue
{
public:
	RobotQueue(int qSize);
	~RobotQueue();
	void push(int id,
			std::function<void()> plugCallback,
			std::function<void()> unplugCallback,
			std::function<bool()> isChargedCallback);
	QueuedRobot pop();
	bool isEmpty();
private:
	int m_qSize;
	std::mutex m_mutex;
	std::queue<QueuedRobot> q;
};

