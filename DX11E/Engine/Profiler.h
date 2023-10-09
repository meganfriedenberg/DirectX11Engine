#pragma once
#define PROFILE_SCOPE(name) Profiler::ScopedTimer name##_scope(Profiler::Get()->GetTimer(std::string(#name)))
class Profiler
{
public:
	static Profiler* Get();

	class Timer
	{
	public:
		friend class Profiler;
		const std::string& GetName() const { return timerName; }
		void Start();
		void Stop();
		void Reset();

		double GetTime_ms() const { return frameTime; }
		double GetMax_ms() const { return longestFrameTime; }
		double GetAvg_ms() const { return totalTimeFrames / numFramesCaptured; }


	private:
		Timer(std::string name);
		~Timer();
		
		std::string timerName;
		double frameTime; //  (how long this timer has taken in this frame – in milliseconds)
		double longestFrameTime; // double (how long was this timer in the longest frame – milliseconds)
		double totalTimeFrames; // total time for this timer for all frames combined
		int numFramesCaptured; // how many frames have been captured for the timer
		std::chrono::high_resolution_clock::time_point timeStart;  // record the time when the timer is started
	};

	class ScopedTimer {
	public:
		ScopedTimer(Profiler::Timer* t);
		~ScopedTimer();
		Profiler::Timer* t;
	private:
		
	};
	friend class Timer;

	Timer* GetTimer(const std::string& name);
	void ResetAll();
	void BeginTimer(const std::string& name, uint64_t startTime);
	void EndTimer(uint64_t endTime);

private:
	Profiler(); // private constructor and destructor
	~Profiler();
	FILE* pFile;

	std::unordered_map<std::string, Timer*> timerMap;
	bool commaCheck;
};

