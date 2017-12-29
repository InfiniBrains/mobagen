#include <iostream>
#include <chrono>
#include <thread>
#include "Timer.cpp"

using namespace std;

class GameLoopController
{
 	int TargetFramePeriod = 16667; // (1s/60) to microseconds
public:
    static GameLoopController& getInstance()
    {
    	static GameLoopController instance; // Guaranteed to be destroyed.                                  // Instantiated on first use.
        return instance;
    }

	~GameLoopController();

	void Init(int TargetFramePeriod)
	{
		this->TargetFramePeriod = TargetFramePeriod;
	}	
	
	void UpdateThread()
  	{
		Timer t;
  		int lastFrameTime = 0;

  		for(;;)
  		{
			t.Start();
			

			t.Stop();
			lastFrameTime = t.Duration();
			//cout <<"wating "<< 1000000 - lastFrameTime << "us" << endl;
  			this_thread::sleep_for(chrono::microseconds(TargetFramePeriod - t.Duration()));
  		}
	}
};


int main ()
{
  

  return 0;
}