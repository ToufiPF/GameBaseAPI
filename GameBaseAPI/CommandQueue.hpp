#ifndef GAMEBASEAPI_COMMANDQUEUE_HPP
#define GAMEBASEAPI_COMMANDQUEUE_HPP

#include <queue>

#include "Command.hpp"

class CommandQueue
{
public:
	void push(const Command& cmd) { mQueue.push(cmd); };
	Command pop() {
		Command command = mQueue.front();
		mQueue.pop();
		return command;
	};
	size_t size() const { return mQueue.size(); };
	bool isEmpty() const { return mQueue.empty(); };
private:
	std::queue<Command> mQueue;
};

#endif
