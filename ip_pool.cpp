#include "ip_pool.h"
#include <algorithm>
#include <iostream>

IP::IP(const std::string& ip_str)
{
	std::istringstream iss(ip_str);
	std::string segment;
	int i = 0;

	while (std::getline(iss, segment, '.') && i < 4) {
		ip_num[i++] = static_cast<uint8_t>(std::stoi(segment));
	}
}

uint32_t IP::get_as_uint32() const
{
	return (static_cast<uint32_t>(ip_num[0]) << 24) |
		   (static_cast<uint32_t>(ip_num[1]) << 16) |
		   (static_cast<uint32_t>(ip_num[2]) << 8) |
		   static_cast<uint32_t>(ip_num[3]);
}

std::ostream& operator<<(std::ostream& os, const IP& ip)
{
	os << static_cast<int>(ip.ip_num[0]) << '.'
	   << static_cast<int>(ip.ip_num[1]) << '.'
	   << static_cast<int>(ip.ip_num[2]) << '.'
	   << static_cast<int>(ip.ip_num[3]);
	return os;
}

void IP_Pool::addIP(const std::string& ip_str) { ip_pool.push_back(ip_str); }

void IP_Pool::sort()
{
	std::sort(ip_pool.begin(), ip_pool.end(), [](const auto& a, const auto& b) {
		return a.get_as_uint32() > b.get_as_uint32();
	});
}

void IP_Pool::print()
{
	for (auto& ip : ip_pool) {
		std::cout << ip << std::endl;
	}
}

void IP_Pool::print_filter(uint8_t part)
{
	for (auto& ip : ip_pool) {
		if (ip.ip_num[0] == part)
			std::cout << ip << std::endl;
	}
};

void IP_Pool::print_filter(uint8_t part1, uint8_t part2) {
	for (auto& ip : ip_pool) {
		if ((ip.ip_num[0] == part1) && (ip.ip_num[1] == part2))
			std::cout << ip << std::endl;
	}
};

void IP_Pool::print_filter_any(uint8_t part) {
	for (auto& ip : ip_pool) {
		if ((ip.ip_num[0] == part) || (ip.ip_num[1] == part) || (ip.ip_num[2] == part) || (ip.ip_num[3] == part))
			std::cout << ip << std::endl;
	}
};