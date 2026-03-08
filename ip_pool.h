#pragma once
#include <array>
#include <cstdint>
#include <string>
#include <vector>

struct IP {
	IP(const std::string& ip_str);

	uint32_t get_as_uint32() const;

	void print() const;

	std::array<uint8_t, 4> ip_num;
};

std::ostream& operator<<(std::ostream& os, const IP& ip);

class IP_Pool
{
public:
	void addIP(const std::string& ip_str);

	void sort();

	IP_Pool filter(uint8_t part) const;
	IP_Pool filter(uint8_t part1, uint8_t part2) const;
	IP_Pool filter_any(uint8_t part) const;

	void print() const;

private:
	std::vector<IP> ip_pool;
};
