#pragma once
#include <thread>
class Worker
{
public:
	Worker();
	~Worker();
	void Begin();
	void End();
	static void Loop();

	std::thread currThread; // each worker operates on a thread

	bool active;
	//static bool active2;
private:

};

