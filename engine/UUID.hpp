#pragma once
#include <atomic>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

struct UUID {
public:
	static std::string UUIDGenerator();
};

std::string UUID::UUIDGenerator() {
	static std::atomic_uint64_t uid{ 0 };
	++uid;

	auto now = std::chrono::high_resolution_clock::now();
	uint64_t nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
	
	std::stringstream ss;
	ss << std::setw(16) << std::setfill('0') << std::hex << nanos;
	ss << std::setw(16) << std::setfill('0') << std::hex << uid;

	return ss.str();
}