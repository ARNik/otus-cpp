#include <iostream>
#include <string>

#include "../lib/cxxopts.hpp"
#include "ip_pool.h"
#include "version.h"

// https://otusmetodist.yonote.ru/share/2cb07ace-75b1-48fe-b6fd-259b39f6025a/doc/2-filtraciya-ip-adresov-s8zT8mUKCH

int main(int argc, char const* argv[])
{
	try {
		// clang-format off
		cxxopts::Options options("ip_filter", "Useful IP manipulation utility");
		options.add_options()
			("h,help", "Show this help information and exit")
			("v,version", "Show version and exit")
			;
		// clang-format on

		auto result = options.parse(argc, argv);

		if (result.count("help")) {
			std::cout << options.help() << std::endl;
			return 0;
		}

		if (result.count("version")) {
			std::cout << "ip_filter" << std::endl;
			std::cout << "App version: " << GIT_VERSION << std::endl;
			std::cout << "cxxopts version: "
					  << static_cast<int>(cxxopts::version.major) << '.'
					  << static_cast<int>(cxxopts::version.minor) << '.'
					  << static_cast<int>(cxxopts::version.patch) << std::endl;

			// TODO: добавить дату сборки
			// std::cout << "Build date: " << BUILD_DATE << std::endl;
			return 0;
		}

	} catch (const cxxopts::exceptions::exception& e) {
		std::cerr << "Error parsing options: " << e.what() << std::endl;
		return -1;
	}

	try {
		IP_Pool p;

		for (std::string line; std::getline(std::cin, line);) {
			p.addIP(line);
		}

		p.sort(); // reverse lexicographically sort for entire pool

		// print ip pool as is
		std::cout << p.get_as_string();
		// filter by first byte and output
		std::cout << p.filter(1).get_as_string();
		// filter by first and second  bytes and output
		std::cout << p.filter(46, 70).get_as_string();
		// filter by any byte and output
		std::cout << p.filter_any(46).get_as_string();

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
