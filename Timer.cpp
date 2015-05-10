#include <chrono>

using namespace std;
using namespace std::chrono;

class Timer
{
    high_resolution_clock::time_point start, stop;

public:
    void Start()
    {
        start = high_resolution_clock::now();
    }
    
    void Stop()
    {
        stop = high_resolution_clock::now();
    }
    
    // TODO: Remove this "auto"
    int Duration()
    {
        auto a = start;
        auto b = stop;
        return chrono::duration_cast<chrono::microseconds>(stop - start).count();
    }
};

/*int main ()
{
  Timer t;
  t.Start();

  std::cout << "printing out 1000 stars...\n";
  for (int i=0; i<1000; ++i) std::cout << "*";
  std::cout << std::endl;

  t.Stop();

  cout << t.Duration() < "us";

  return 0;
}*/