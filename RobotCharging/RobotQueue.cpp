#include "RobotQueue.h"

RobotQueue::RobotQueue(int qSize):
	m_qSize(qSize)
{
}

RobotQueue::~RobotQueue()
{
}

void RobotQueue::push(int id, std::function<void()> plugCallback, std::function<void()> unplugCallback, std::function<bool()> isChargedCallback)
{
	std::cout << "Queuing robot " << id << std::endl;
	QueuedRobot r(id, plugCallback, unplugCallback, isChargedCallback);
	m_mutex.lock();
	q.push(r);
	m_mutex.unlock();
}

QueuedRobot RobotQueue::pop()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	auto result = q.front();
	q.pop();
	return result;
}

bool RobotQueue::isEmpty()
{
	return q.empty();
}
