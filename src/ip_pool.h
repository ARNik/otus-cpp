#pragma once
#include <array>
#include <cstdint>
#include <string>
#include <vector>
#include <functional>

struct IP {
	IP(const std::string& ip_str);

	std::string get_as_string() const;

	uint32_t get_as_uint32() const;

	std::array<uint8_t, 4> ip_num;
};

std::ostream& operator<<(std::ostream& os, const IP& ip);

class IP_Pool
{
public:
	void addIP(const std::string& ip_str);

	std::string get_as_string() const;

	void sort();

	IP_Pool filter(std::function<bool(const IP&)> predicate) const;

	IP_Pool filter(uint8_t part) const;
	IP_Pool filter(uint8_t part1, uint8_t part2) const;
	IP_Pool filter_any(uint8_t part) const;

private:
	std::vector<IP> ip_pool;
};

std::ostream& operator<<(std::ostream& os, const IP_Pool& ip);
