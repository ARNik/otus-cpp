#include <iostream>
#include <string>

#include "../lib/cxxopts.hpp"
#include "version.h"

// https://otusmetodist.yonote.ru/share/2cb07ace-75b1-48fe-b6fd-259b39f6025a/doc/3-allocator-3hUxCcAj0a

int main(int argc, char const* argv[])
{
	try {
		// clang-format off
		cxxopts::Options options("allocator", "Homework #3");
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
			std::cout << "allocator" << std::endl;
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

	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
