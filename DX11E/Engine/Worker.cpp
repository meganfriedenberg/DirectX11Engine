#include "stdafx.h"
#include "Worker.h"
#include "Job.h"
#include "JobManager.h"

Worker::Worker()
{

}
Worker::~Worker()
{

}
void Worker::Begin()
{
	currThread = std::thread(Loop);
}
void Worker::End()
{
	active = false;
	currThread.join();
}


void Worker::Loop()
{
	while (JobManager::active) // waits on this getting set to false
	{
		JobManager::jobLock.lock();
		if (JobManager::GetJobs().size() > 0)
		{
			Job* j = JobManager::GetJobs().front();
			if(j != nullptr)
				JobManager::GetJobs().erase(JobManager::GetJobs().begin());
			JobManager::jobLock.unlock(); // make sure you unlock before you run the job
			if(j != nullptr)
				j->DoIt();
			JobManager::numJobs--;
		}
		else {
			JobManager::jobLock.unlock();
		}
	}

}
