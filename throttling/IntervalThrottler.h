#pragma once

#include <chrono>
#include <glog/logging.h>
#include <thread>
#include <cassert>
#include <unistd.h>

class IntervalThrottler
{
  typedef std::chrono::high_resolution_clock Clock;

  // time of previous call
  Clock::time_point previous;
  bool first = true;

  double desiredInterval = 0; 
  // between consecutive calls

  // cumulative diff between actual and desired
  int32_t jitterNanosec = 0; 

  // sleep if jitter exceeds desired/sleepFactor
  uint32_t sleepFactor = 5; 

  static constexpr double SecToNanosec = 1000000000;

  public:

  void setDesiredInterval(uint32_t exp)
  {
    desiredInterval = exp * SecToNanosec;
  }

  void limit()
  {
    auto now = Clock::now();

    if (!first) {

      auto actualInterval = 
        std::chrono::duration_cast<std::chrono::nanoseconds>(
          now - previous).count();

      // positive diff implies too fast
      jitterNanosec += (desiredInterval - actualInterval);
      bool greater = (jitterNanosec > (double)desiredInterval/sleepFactor);
        
      VLOG(1) 
        << " actual_interval=" << actualInterval
        << " sleep_for=" << jitterNanosec 
        << " greater=" << greater;

      // if diff is getting too big, lets reset
      if (greater)
      {
        assert(jitterNanosec > 0);
        std::this_thread::sleep_for(std::chrono::nanoseconds(jitterNanosec));
        jitterNanosec = 0;
        now = Clock::now();
      }
    } else {
      first = false;
    }
  
    previous = now;
  }
};
