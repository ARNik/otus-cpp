#pragma once
#include <array>
#include <cstdint>
#include <string>
#include <vector>

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

	template <typename... Args> IP_Pool filter(Args... args)
	{
		std::array<uint8_t, sizeof...(args)> octets = {
			static_cast<uint8_t>(args)...};

		IP_Pool res;
		for (auto& ip : ip_pool) {
			bool match = true;
			for (size_t i = 0; i < octets.size(); ++i) {
				if (ip.ip_num[i] != octets[i]) {
					match = false;
					break;
				}
			}
			if (match)
				res.ip_pool.push_back(ip);
		}
		return res;
	}

	template <typename... Args> IP_Pool filter_any(Args... args)
	{
		std::array<uint8_t, sizeof...(args)> octets = {
			static_cast<uint8_t>(args)...};

		IP_Pool res;
		for (auto& ip : ip_pool) {
			bool match = false;
			for (auto& octet :octets)
			{
				for (int i = 0; i<4; ++i)
				{
					if (ip.ip_num[i] == octet)
					{
						match = true;
						break;
					}
				}
			}
			if (match)
				res.ip_pool.push_back(ip);
		}
		return res;
	}

private:
	std::vector<IP> ip_pool;
};

std::ostream& operator<<(std::ostream& os, const IP_Pool& ip);
