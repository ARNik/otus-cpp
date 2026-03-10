#include "ip_pool.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

// === IP ===

IP::IP(const std::string& ip_str)
{
	size_t start = 0;

	if (ip_str.length() < 6)
		throw std::invalid_argument("IP error: the string is too short");

	for (int i = 0; i < 4; i++) {
		size_t end = (i < 3) ? ip_str.find('.', start) : ip_str.length();
		int octet = std::stoi(ip_str.substr(start, end - start));
		if (octet < 0 || octet > 255)
			throw std::invalid_argument(
				"IP error: octet is not in 0..255 range");
		ip_num[i] = static_cast<uint8_t>(octet);
		start = end + 1;
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
	os << std::to_string(ip.ip_num[0]) + "." + std::to_string(ip.ip_num[1]) +
			  "." + std::to_string(ip.ip_num[2]) + "." +
			  std::to_string(ip.ip_num[3]);
	return os;
}

// === IP_Pool ===

void IP_Pool::addIP(const std::string& ip_str) { ip_pool.push_back(ip_str); }

void IP_Pool::sort()
{
	std::sort(ip_pool.begin(), ip_pool.end(), [](const auto& a, const auto& b) {
		return a.get_as_uint32() > b.get_as_uint32();
	});
}

std::ostream& operator<<(std::ostream& os, const IP_Pool& pool)
{
	for (auto& ip : pool.ip_pool) {
		os << ip << std::endl;
	}
	return os;
}
