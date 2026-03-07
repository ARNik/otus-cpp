#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

// https://otusmetodist.yonote.ru/share/2cb07ace-75b1-48fe-b6fd-259b39f6025a/doc/2-filtraciya-ip-adresov-s8zT8mUKCH

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string& str, char d)
{
	std::vector<std::string> r;

	std::string::size_type start = 0;
	std::string::size_type stop = str.find_first_of(d);
	while (stop != std::string::npos) {
		r.push_back(str.substr(start, stop - start));

		start = stop + 1;
		stop = str.find_first_of(d, start);
	}

	r.push_back(str.substr(start));

	return r;
}

int main(int argc, char const* argv[])
{
	try {
		std::vector<std::vector<std::string>> ip_pool;

		for (std::string line; std::getline(std::cin, line);) {
			std::vector<std::string> v = split(line, '\t');
			ip_pool.push_back(split(v.at(0), '.'));
		}

		// TODO reverse lexicographically sort

		// Convert ips to digits
		std::vector<std::array<uint8_t, 4>> ip_num_vec;
		for (auto& ip : ip_pool) {
			std::array<uint8_t, 4> ip_num;
			for (int i = 0; i < 4; ++i) {
				ip_num.at(i) = std::stoi(ip.at(i));
			}
			ip_num_vec.push_back(ip_num);
		}

		// std::sort()

		// Print ips from digits
		for (auto& ip_num : ip_num_vec) {
			bool dot = false;
			for (auto& ip_part : ip_num) {
				if (dot) {
					std::cout << '.';
				}
				std::cout << std::to_string(ip_part);
				dot = true;
			}
			std::cout << std::endl;
		}

		std::cout << "=======" << std::endl;

		for (std::vector<std::vector<std::string>>::const_iterator ip =
				 ip_pool.cbegin();
			 ip != ip_pool.cend(); ++ip) {
			for (std::vector<std::string>::const_iterator ip_part =
					 ip->cbegin();
				 ip_part != ip->cend(); ++ip_part) {
				if (ip_part != ip->cbegin()) {
					std::cout << ".";
				}
				std::cout << *ip_part;
			}
			std::cout << std::endl;
		}

		// 222.173.235.246
		// 222.130.177.64
		// 222.82.198.61
		// ...
		// 1.70.44.170
		// 1.29.168.152
		// 1.1.234.8

		// TODO filter by first byte and output
		// ip = filter(1)

		// 1.231.69.33
		// 1.87.203.225
		// 1.70.44.170
		// 1.29.168.152
		// 1.1.234.8

		// TODO filter by first and second bytes and output
		// ip = filter(46, 70)

		// 46.70.225.39
		// 46.70.147.26
		// 46.70.113.73
		// 46.70.29.76

		// TODO filter by any byte and output
		// ip = filter_any(46)

		// 186.204.34.46
		// 186.46.222.194
		// 185.46.87.231
		// 185.46.86.132
		// 185.46.86.131
		// 185.46.86.131
		// 185.46.86.22
		// 185.46.85.204
		// 185.46.85.78
		// 68.46.218.208
		// 46.251.197.23
		// 46.223.254.56
		// 46.223.254.56
		// 46.182.19.219
		// 46.161.63.66
		// 46.161.61.51
		// 46.161.60.92
		// 46.161.60.35
		// 46.161.58.202
		// 46.161.56.241
		// 46.161.56.203
		// 46.161.56.174
		// 46.161.56.106
		// 46.161.56.106
		// 46.101.163.119
		// 46.101.127.145
		// 46.70.225.39
		// 46.70.147.26
		// 46.70.113.73
		// 46.70.29.76
		// 46.55.46.98
		// 46.49.43.85
		// 39.46.86.85
		// 5.189.203.46
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
