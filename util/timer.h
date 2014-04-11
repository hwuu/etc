// $Id: timer.h 5444 2012-03-11 11:41:41Z haowu $

#ifndef _ETC_TIMER_H_
#define _ETC_TIMER_H_

//
//
//
#ifdef _WIN32
//
//
//

#ifdef _MSC_VER

#pragma comment(lib, "winmm.lib")
#include <windows.h>

class Timer
{
public:
  Timer()
  {
    Reset();
  }
  void Reset()
  {
    start_time = timeGetTime();
  }
  unsigned int GetTime()
  {
    DWORD stop_time = timeGetTime();
    return stop_time - start_time;
  }
protected:
  DWORD start_time;
};

#else

#include <ctime>
using namespace std;
class Timer
{
public:
  Timer()
  {
    Reset();
  }
  void Reset()
  {
    start_time = clock();
  }
  unsigned int GetTime()
  {
    return clock() - start_time;
  }
protected:
  clock_t start_time;
};

#endif

//
//
//
#else // if current system is linux or mac
//
//
//

#ifdef __MACH__ // if it is mac
#include <mach/clock.h>
#include <mach/mach.h>
#endif

#include <ctime>

using namespace std;

//

//

class Timer
{
public:
  //
  Timer()
  {
    Reset();
  }
  void Reset()
  {
    _GetTime(&start_time);
  }
  unsigned int GetTime()
  {
    struct timespec stop_time;
    _GetTime(&stop_time);
    return   (stop_time.tv_sec - start_time.tv_sec) * 1000
      + (stop_time.tv_nsec - start_time.tv_nsec) / 1000000;
  }
  //
protected:
  //
  struct timespec start_time;
  //
  void _GetTime(timespec* p_ts)
  {
#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    p_ts->tv_sec = mts.tv_sec;
    p_ts->tv_nsec = mts.tv_nsec;
#else
    clock_gettime(CLOCK_REALTIME, p_ts);
#endif 
  }
};

//
//
//
#endif
//
//
//

#endif
