#pragma once

#include <iostream>

#include <sstream>

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#else
#error "Only windows is supported for now"
#endif

#include <vector>
#include <shared_mutex>
#include <thread>

#include <random>
#include <cmath>

#include <chrono>
#include <time.h>
#include <iomanip>