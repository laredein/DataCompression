#ifndef TIMER_H 
#define TIMER_H

#include <chrono>
#include <iostream>
using std::chrono::duration;
using std::chrono::milliseconds;
using std::chrono::high_resolution_clock;
using namespace std;

void resetTime();
void showTime();

#endif
