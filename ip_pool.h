#pragma once
#include <array>
#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

struct IP {
	IP(const std::string& ip_str);
	uint32_t get_as_uint32() const;

	std::array<uint8_t, 4> ip_num;
};

std::ostream& operator<<(std::ostream& os, const IP& ip);

class IP_Pool
{
public:
	void addIP(const std::string& ip_str);
	void sort();
	void print();

private:
	std::vector<IP> ip_pool;
};
