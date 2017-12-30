//
// Created by tolstenko on 12/29/2017.
//
#pragma once
#include <chrono>
using namespace std::chrono;

class GameLoop
{
private:
  high_resolution_clock::time_point lastUpdateTime_{};
  duration<double> accumulatedTime_{};
  double dt_;
  double targetDeltaTime_;
public:
  explicit GameLoop(double targetDeltaTime);
  ~GameLoop();
  void Tick();
  double Dt();
  void WaitForNextFrame();
  inline double TargetDeltaTime();
};
