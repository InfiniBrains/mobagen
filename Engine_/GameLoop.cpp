#include "GameLoop.h"
#include <thread>
#include <cfloat>

using namespace std;

GameLoop::GameLoop(const double targetDeltaTime)
{
  accumulatedTime_ = duration<double>(duration_values<double>::zero());
  lastUpdateTime_ = high_resolution_clock::now();
  dt_ = 0;
  targetDeltaTime_ = targetDeltaTime;
}

GameLoop::~GameLoop() = default;

// todo: check pausable status, and physics steps
void GameLoop::Tick()
{
  const auto now = high_resolution_clock::now();
  auto deltaTime = duration_cast<duration<double>>(now - lastUpdateTime_);
  if (deltaTime.count() < FLT_MIN) {
    deltaTime = duration<double>(TargetDeltaTime());
  }
  else
    accumulatedTime_ += deltaTime;

  dt_ = deltaTime.count();

  lastUpdateTime_ = now;
}

double GameLoop::TargetDeltaTime()
{
  return targetDeltaTime_;
}

double GameLoop::Dt()
{
  return dt_;
}

void GameLoop::WaitForNextFrame()
{
  auto delta = duration<double>(TargetDeltaTime())- (high_resolution_clock::now() - lastUpdateTime_);
  if (delta.count() > 0)
    this_thread::sleep_for(delta);
}
