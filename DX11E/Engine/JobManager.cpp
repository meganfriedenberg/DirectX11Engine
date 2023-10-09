#include "stdafx.h"
#include "JobManager.h"
#include "Worker.h"
#include "Job.h"


JobManager::JobManager()
{
	a = new Worker();
	b = new Worker();
	c = new Worker();
	d = new Worker();
	j = this;
	std::vector<Job*> mJobs;
	jobs = mJobs;
	//std::mutex mJobLock;
	//jobLock = std::mutex();
	JobManager::SetBool(true);
}
JobManager::~JobManager()
{
	delete a;
	delete b;
	delete c;
	delete d;
}
void JobManager::Begin()
{
	a->Begin();
	b->Begin();
	c->Begin();
	d->Begin();
}
void JobManager::AddJob(Job* pJob)
{
	pJob->DoIt();
	JobManager::jobLock.lock();
	JobManager::jobs.push_back(pJob);
	JobManager::numJobs++;
	JobManager::jobLock.unlock();
}

void JobManager::End() // how to tell workers to stop
{
	JobManager::SetBool(false);
	a->End();
	b->End();
	c->End();
	d->End();
}
void JobManager::WaitForJobs()
{
	if (numJobs > 0)
	{
		std::this_thread::sleep_for(std::chrono::nanoseconds(1));
	}

}
/*static*/ JobManager* JobManager::j = nullptr;
/*static*/ std::vector<Job*> JobManager::jobs;
bool JobManager::active = true;
std::mutex JobManager::jobLock;
std::atomic<int> JobManager::numJobs;
void JobManager::SetBool(bool value)
{
	active = value;
}

