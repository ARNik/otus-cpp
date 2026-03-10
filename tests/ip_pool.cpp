#include "../src/ip_pool.h"
#include <gtest/gtest.h>

// https://www.youtube.com/watch?v=aDQabfxQwfM

TEST(test_ip, CreateFromString)
{
	std::string ip_str = "192.168.0.1";
	IP ip(ip_str);
	EXPECT_EQ(ip.get_as_uint32(), 3232235521);
	EXPECT_EQ((std::stringstream() << ip).str(), ip_str);
}

TEST(test_ip_pool, CreateFromString)
{
	IP_Pool p;
	p.addIP("1.1.0.1	5	6");
	p.addIP("10.0.0.0	110 1");
	p.addIP("1.10.0.1	2	1");
	p.addIP("1.1.10.1	22	0");

	EXPECT_EQ((std::stringstream() << p).str(), "1.1.0.1\n10.0.0.0\n1.10.0.1\n1.1.10.1\n");
	p.sort();
	EXPECT_EQ((std::stringstream() << p).str(), "10.0.0.0\n1.10.0.1\n1.1.10.1\n1.1.0.1\n");
	EXPECT_EQ((std::stringstream() << p.filter(10)).str(), "10.0.0.0\n");
	EXPECT_EQ((std::stringstream() << p.filter(1, 1)).str(), "1.1.10.1\n1.1.0.1\n");
	EXPECT_EQ((std::stringstream() << p.filter_any(10)).str(),
			  "10.0.0.0\n1.10.0.1\n1.1.10.1\n");
}