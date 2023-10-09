#include "stdafx.h"
#include "Profiler.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <thread>

Profiler::Profiler()
{
	fopen_s(&pFile, "profile.json", "w");
	if (pFile != NULL)
	{
		fprintf(pFile, "%s","[");
		//for (std::unordered_map<std::string, Timer*>::iterator it = timerMap.begin(); it != timerMap.end(); ++it)
		//{
		//	std::string name = it->first;
		//	const char* cname = name.c_str();
		//	double avg = it->second->GetAvg_ms();
		//	double max = it->second->GetMax_ms();

		//	fprintf(pFile, "%s:, %f, %f\n", cname, avg, max);
		//}
	}
}
Profiler::~Profiler()
{
	FILE* iFile;
	fopen_s(&iFile,"profile.txt", "w");
	if (iFile != NULL && pFile != NULL)
	{

		fprintf(iFile, "name:, avg(ms), max(ms)");
		for (std::unordered_map<std::string, Timer*>::iterator it = timerMap.begin(); it != timerMap.end(); ++it)
		{
			std::string name = it->first;
			const char* cname = name.c_str();
			double avg = it->second->GetAvg_ms();
			double max = it->second->GetMax_ms();

			fprintf(iFile, "\n%s:, %f, %f", cname, avg, max);
		}
		fprintf(pFile, "%s", "\n]"); // Finish json opening
		fclose(pFile);
		fclose(iFile);
	}
	

}
void Profiler::ResetAll()
{
	std::unordered_map<std::string, Timer*>::iterator it;
	it = timerMap.begin();
	while(it != timerMap.end())
	{
		it->second->Reset();
		++it;
	}
}

Profiler* Profiler::Get()
{
	static Profiler p; // Return a local static variable
	return &p;
}
Profiler::Timer* Profiler::GetTimer(const std::string& name)
{
	std::unordered_map<std::string, Timer*>::iterator it;
	it = timerMap.find(name);
	if (it == timerMap.end())
	{ // not in map, create new Timer
		Profiler::Timer* t = new Profiler::Timer(name);
		timerMap[name] = t;
		return t;
	}
	return timerMap[name];
}
void Profiler::BeginTimer(const std::string& name, uint64_t startTime)
{
	if (pFile != NULL) // If the file is still open and not accidentally closed
	{
		size_t tid = std::hash<std::thread::id>{}(std::this_thread::get_id());
		if (!commaCheck)
		{
			commaCheck = true; // we have no other items printed before
			fprintf(pFile, "%s%s%s%llu%s%zu%s", "\n{\"name\": \"", name.c_str(), "\", \"ph\": \"B\", \"ts\": ", startTime, ", \"pid\": 1, \"tid\": ", tid, "}");

		}
		else 
		{
			fprintf(pFile, "%s%s%s%llu%s%zu%s", ",\n{\"name\": \"", name.c_str(), "\", \"ph\": \"B\", \"ts\": ", startTime, ", \"pid\": 1, \"tid\": ", tid, "}");
		}
	}
}
void Profiler::EndTimer(uint64_t endTime)

{
	if (pFile != NULL) // If the file is still open and not accidentally closed
	{
		size_t tid = std::hash<std::thread::id>{}(std::this_thread::get_id());
		fprintf(pFile, "%s%llu%s%zu%s", ",\n{\"ph\": \E\", \ts\": ", endTime, ", \pid\": 1, \"tid\": ", tid, "}");
	}
}

Profiler::Timer::Timer(std::string name)
{
	timerName = name;
	numFramesCaptured = 0;
	totalTimeFrames = 0;
	longestFrameTime = 0;
	frameTime = 0;

}
Profiler::Timer::~Timer()
{

}
void Profiler::Timer::Start()
{
	timeStart = std::chrono::high_resolution_clock::now(); // start the clock!
	uint64_t start = timeStart.time_since_epoch().count() / 1000;
	Profiler* p = Profiler::Get();
	p->Profiler::BeginTimer(this->GetName(), start);
}
void Profiler::Timer::Stop()
{
	std::chrono::high_resolution_clock::time_point end;
	end = std::chrono::high_resolution_clock::now();
	double currTotalTime = std::chrono::duration<double, std::milli>(end - timeStart).count();

	frameTime += currTotalTime; // add the currTotal for this frame to this frame

	uint64_t endT = end.time_since_epoch().count() / 1000;
	Profiler* p = Profiler::Get();
	p->Profiler::BeginTimer(this->GetName(), endT);

}
void Profiler::Timer::Reset()
{
	this->totalTimeFrames += frameTime; // add the length of this frame to the total amount of time spent in frames
	this->numFramesCaptured++; // increase num of frames captured
	if (frameTime > longestFrameTime)
	{
		longestFrameTime = frameTime;
	}

	this->frameTime = 0.0; // reset frame time
}

Profiler::ScopedTimer::ScopedTimer(Timer* timer)
{
	t = timer;
	t->Start();
}
Profiler::ScopedTimer::~ScopedTimer()
{
	t->Stop();
}