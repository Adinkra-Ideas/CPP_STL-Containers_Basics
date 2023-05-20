/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapMain.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 21:39:42 by euyi              #+#    #+#             */
/*   Updated: 2023/02/18 23:38:13 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifdef _MAP_
# include "../map.hpp"
# include <time.h>
# include <utility>
# include <iomanip>
# include <stdio.h>

static void print(const ft::map<std::string, int>& m) {
	std::cout << '{';
	ft::map<std::string, int>::const_iterator b = m.begin();
	ft::map<std::string, int>::const_iterator e = m.end();
	while (b != e) {
		std::cout << b->first << ':' << b->second << ' ';
		b++;
	}
	std::cout << "}\n";
}
int main()
{
	clock_t g_start = clock();

	ft::map<std::string, int> mp1;
	mp1["something"] = 21;
	mp1["anything"] = 42;
	mp1["that thing"] = 84;
	mp1["whatever"] = 168;
	std::cout << "mp1: " << std::endl;
	print(mp1);

	ft::map<std::string, int> mp2(mp1.find("something"), mp1.end());
	std::cout << "mp2: " << std::endl;
	print(mp2);

	ft::map<std::string, int> mp3(mp1);
	std::cout << "mp3: " << std::endl;
	print(mp3);

	std::cout << "mp3[anything] with at: " << mp3.at("anything") << std::endl;
	std::cout << "mp3[non_existing] with []: " << mp3["non_existing"]
				<< std::endl;
	print(mp3);

	ft::map<std::string, int>::reverse_iterator rvrIt = mp3.rbegin();
	std::cout << '{';
	for (; rvrIt != mp3.rend(); rvrIt++) {
		std::cout << rvrIt->first << ':' << rvrIt->second << ' ';
	}
	std::cout << "}\n";

	std::cout << "mp3 empty: " << std::boolalpha << mp3.empty() << std::noboolalpha << std::endl;
	std::cout << "mp3 size: " << mp3.size() << std::endl;

	std::cout << "mp3 clear\n";
	mp3.clear();
	std::cout << "mp3 size: " << mp3.size() << std::endl;
	std::cout << "mp3 insert (from mp2)\n";
	mp3.insert(mp2.begin(), mp2.end());
	std::cout << "mp3 size: " << mp3.size() << std::endl;
	std::cout << "mp3: " << std::endl;
	print(mp3);

	std::cout << "erase 'that_thing'\n";
	mp3.erase(mp3.find("that thing"));
	std::cout << "erase 'non_existing'\n";
	mp3.erase("non_existing");
	std::cout << "mp3: " << std::endl;
	print(mp3);

	mp3.swap(mp2);
	std::cout << "mp3: " << std::endl;
	print(mp3);

	std::cout << "mp3 == mp2: " << std::boolalpha << (mp3 == mp2) << std::endl;
	std::cout << "mp3 < mp2: " << (mp3 < mp2) << std::endl;
	std::cout << "mp3 >= mp2: " << (mp3 >= mp2) << std::endl;

	ft::map<int, int> mp4;
	for (int i = 0, j = 100; i < 300000; i++, j++) {
		mp4.insert(ft::make_pair(i * 2, j));
	}
	std::cout << "count 41: " << mp4.count(41) << std::endl;
	std::cout << "count 50: " << mp4.count(50) << std::endl;
	std::cout << "count 300005: " << mp4.count(300005) << std::endl;
	std::cout << "find 26: " << mp4.find(26)->first << std::endl;
	std::cout << "lower bound 127: " << mp4.lower_bound(127)->first << std::endl;
	std::cout << "upper bound 244: " << mp4.upper_bound(244)->first << std::endl;

	g_start = clock() - g_start;
	printf("Execution time (ms): %.2fms\n",
			(double)g_start / CLOCKS_PER_SEC * 1000);

	return 0;
}


// # include <map>
// static void print(const std::map<std::string, int>& m) {
// 	std::cout << '{';
// 	std::map<std::string, int>::const_iterator b = m.begin();
// 	std::map<std::string, int>::const_iterator e = m.end();
// 	while (b != e) {
// 		std::cout << b->first << ':' << b->second << ' ';
// 		b++;
// 	}
// 	std::cout << "}\n";
// }
// int main()
// {
// 	clock_t g_start = clock();

// 	std::map<std::string, int> mp1;
// 	mp1["something"] = 21;
// 	mp1["anything"] = 42;
// 	mp1["that thing"] = 84;
// 	mp1["whatever"] = 168;
// 	std::cout << "mp1: " << std::endl;
// 	print(mp1);

// 	std::map<std::string, int> mp2(mp1.find("something"), mp1.end());
// 	std::cout << "mp2: " << std::endl;
// 	print(mp2);

// 	std::map<std::string, int> mp3(mp1);
// 	std::cout << "mp3: " << std::endl;
// 	print(mp3);

// 	std::cout << "mp3[anything] with at: " << mp3.at("anything") << std::endl;
// 	std::cout << "mp3[non_existing] with []: " << mp3["non_existing"]
// 				<< std::endl;
// 	print(mp3);

// 	std::map<std::string, int>::reverse_iterator rvrIt = mp3.rbegin();
// 	std::cout << '{';
// 	for (; rvrIt != mp3.rend(); rvrIt++) {
// 		std::cout << rvrIt->first << ':' << rvrIt->second << ' ';
// 	}
// 	std::cout << "}\n";

// 	std::cout << "mp3 empty: " << std::boolalpha << mp3.empty() << std::noboolalpha << std::endl;
// 	std::cout << "mp3 size: " << mp3.size() << std::endl;

// 	std::cout << "mp3 clear\n";
// 	mp3.clear();
// 	std::cout << "mp3 size: " << mp3.size() << std::endl;
// 	std::cout << "mp3 insert (from mp2)\n";
// 	mp3.insert(mp2.begin(), mp2.end());
// 	std::cout << "mp3 size: " << mp3.size() << std::endl;
// 	std::cout << "mp3: " << std::endl;
// 	print(mp3);

// 	std::cout << "erase 'that_thing'\n";
// 	mp3.erase(mp3.find("that thing"));
// 	std::cout << "erase 'non_existing'\n";
// 	mp3.erase("non_existing");
// 	std::cout << "mp3: " << std::endl;
// 	print(mp3);

// 	mp3.swap(mp2);
// 	std::cout << "mp3: " << std::endl;
// 	print(mp3);

// 	std::cout << "mp3 == mp2: " << std::boolalpha << (mp3 == mp2) << std::endl;
// 	std::cout << "mp3 < mp2: " << (mp3 < mp2) << std::endl;
// 	std::cout << "mp3 >= mp2: " << (mp3 >= mp2) << std::endl;

// 	std::map<int, int> mp4;
// 	for (int i = 0, j = 100; i < 300000; i++, j++) {
// 		mp4.insert(std::make_pair(i * 2, j));
// 	}
// 	std::cout << "count 41: " << mp4.count(41) << std::endl;
// 	std::cout << "count 50: " << mp4.count(50) << std::endl;
// 	std::cout << "count 300005: " << mp4.count(300005) << std::endl;
// 	std::cout << "find 26: " << mp4.find(26)->first << std::endl;
// 	std::cout << "lower bound 127: " << mp4.lower_bound(127)->first << std::endl;
// 	std::cout << "upper bound 244: " << mp4.upper_bound(244)->first << std::endl;

// 	g_start = clock() - g_start;
// 	printf("Execution time (ms): %.2fms\n",
// 			(double)g_start / CLOCKS_PER_SEC * 1000);

// 	return 0;
// }

#endif
