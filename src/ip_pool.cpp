#include "ip_pool.h"
#include <algorithm>

// === IP ===

IP::IP(const std::string& ip_str)
{
	size_t start = 0;

	for (int i = 0; i < 4; i++) {
		size_t end = (i < 3) ? ip_str.find('.', start) : ip_str.length();
		ip_num[i] =
			static_cast<uint8_t>(std::stoi(ip_str.substr(start, end - start)));
		start = end + 1;
	}
}

std::string IP::get_as_string() const
{
	return std::to_string(ip_num[0]) + "." + std::to_string(ip_num[1]) + "." +
		   std::to_string(ip_num[2]) + "." + std::to_string(ip_num[3]);
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
	os << ip.get_as_string();
	return os;
}


// === IP_Pool ===

void IP_Pool::addIP(const std::string& ip_str) { ip_pool.push_back(ip_str); }

std::string IP_Pool::get_as_string() const
{
	std::string res;
	for (auto& ip : ip_pool) {
		res.append(ip.get_as_string() + '\n');
	}
	return res;
}

void IP_Pool::sort()
{
	std::sort(ip_pool.begin(), ip_pool.end(), [](const auto& a, const auto& b) {
		return a.get_as_uint32() > b.get_as_uint32();
	});
}

IP_Pool IP_Pool::filter(uint8_t part) const
{
	IP_Pool res;
	for (auto& ip : ip_pool) {
		if (ip.ip_num[0] == part)
		res.ip_pool.push_back(ip);
	}
	return res;
}

IP_Pool IP_Pool::filter(uint8_t part1, uint8_t part2) const
{
	IP_Pool res;
	for (auto& ip : ip_pool) {
		if ((ip.ip_num[0] == part1) && (ip.ip_num[1] == part2))
		res.ip_pool.push_back(ip);
	}
	return res;
};

IP_Pool IP_Pool::filter_any(uint8_t part) const
{
	IP_Pool res;
	for (auto& ip : ip_pool) {
		if ((ip.ip_num[0] == part) || (ip.ip_num[1] == part) ||
		(ip.ip_num[2] == part) || (ip.ip_num[3] == part))
		res.ip_pool.push_back(ip);
	}
	return res;
};

std::ostream& operator<<(std::ostream& os, const IP_Pool& pool)
{
	os << pool.get_as_string();
	return os;
}
