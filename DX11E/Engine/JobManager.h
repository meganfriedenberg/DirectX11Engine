#pragma once
#include <atomic>
#include <mutex>
#include <queue>

class JobManager
{
public:
	JobManager();
	~JobManager();

	void Begin(); // (Begin each of your Workers)
	void End();  // (Set the shutdown signaland End each of your Workers)
	void AddJob(class Job* pJob); // 
	void WaitForJobs(); // 
	static JobManager* Get() { return j; }
	static std::vector<class Job*>& GetJobs() { return jobs; }
	static void SetBool(bool value);
	static std::mutex jobLock;

	static std::atomic<int> numJobs;


	class Worker* a;
	class Worker* b;
	class Worker* c;
	class Worker* d;

	static JobManager* j;
	static std::vector<class Job*> jobs;
	static bool active;
private:

};

