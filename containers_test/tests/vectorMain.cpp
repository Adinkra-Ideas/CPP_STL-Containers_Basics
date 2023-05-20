/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorMain.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 21:30:58 by euyi              #+#    #+#             */
/*   Updated: 2023/02/18 23:48:54 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifdef _VECTOR_

# include "../vector.hpp"
# include <time.h>
# include <stdio.h>
# include <iostream>
# include <string>
# include <iomanip>



static void print(const ft::vector<std::string>& v) {
	for (size_t i = 0; i < v.size(); i++)
		std::cout << "Element[" << i << "] == " << v[i] << std::endl;
}
int main()
{
	clock_t g_start = clock();

	ft::vector<std::string> obj;
	obj.push_back("Checking");
	obj.push_back("Testing");
	obj.push_back("Troll");
	obj.push_back("Mothe");
	obj.push_back("Welcome");
	std::cout << "obj: " << std::endl;
	print(obj);

	ft::vector<std::string> obj2(obj.begin(), obj.end());
	std::cout << "obj2: " << std::endl;
	print(obj2);

	ft::vector<std::string> obj3(obj2);
	std::cout << "obj3: " << std::endl;
	print(obj3);

	std::cout << "obj3[1]: " << obj3.at(1) << std::endl;
	std::cout << "obj3[2]: " << obj3[2] << std::endl;
	std::cout << "obj3 front: " << obj3.front() << std::endl;
	std::cout << "obj3 back: " << obj3.back() << std::endl;
	std::cout << "obj3 data: " << *obj3.data() << std::endl;

	ft::vector<std::string>::iterator it = obj3.begin();
	for (; it < obj3.end(); it++) {
		std::cout << "it: " << *it << " ";
	}
	std::cout << std::endl;

	ft::vector<std::string>::reverse_iterator rvrIt = obj3.rbegin();
	for (; rvrIt < obj3.rend(); rvrIt++) {
		std::cout << "rvrIt: " << *rvrIt << " ";
	}
	std::cout << std::endl;

	std::cout << "obj3 empty: " << std::boolalpha << obj3.empty() << std::endl;
	std::cout << "obj3 size: " << obj3.size() << std::endl;
	std::cout << "obj3 max_size: " << obj3.max_size() << std::endl;
	std::cout << "obj3 capacity: " << obj3.capacity() << std::endl;

	std::cout << "obj3 cleared\n";
	obj3.clear();
	std::cout << "obj3 empty: " << std::boolalpha << obj3.empty() << std::endl;
	std::cout << "obj3 size: " << obj3.size() << std::endl;
	
	std::cout << "obj3 insert (from obj2)\n";
	obj3.insert(obj3.begin(), obj2.begin(), obj2.end());
	std::cout << "obj3 size: " << obj3.size() << std::endl;
	std::cout << "obj3: " << std::endl;
	print(obj3);

	std::cout << "erase 4th Element\n";
	obj3.erase(obj3.begin() + 4);
	std::cout << "obj3: " << std::endl;
	print(obj3);

	obj3.push_back("foo");
	obj3.push_back("bar");
	obj3.push_back("kek");
	std::cout << "obj3: " << std::endl;
	print(obj3);

	obj3.pop_back();
	std::cout << "obj3: " << std::endl;
	print(obj3);

	obj3.resize(4);
	std::cout << "obj3: " << std::endl;
	print(obj3);

	obj3.assign(2, "newWord");
	std::cout << "obj3: " << std::endl;
	print(obj3);

	obj3.swap(obj2);
	std::cout << "obj3: " << std::endl;
	print(obj3);

	std::cout << "obj3 == obj2: " << std::boolalpha << (obj3 == obj2) << std::endl;
	std::cout << "obj3 < obj2: " << std::boolalpha << (obj3 < obj2) << std::endl;
	std::cout << "obj3 >= obj2: " << std::boolalpha << (obj3 >= obj2) << std::endl;

	// ft::vector<int> v4;
	// for (int i = 0; i < 300000; i++) {
	// 	v4.push_back(i);
	// }
	// for (int i = 0; i < 300000; i++) {
	// 	std::cout << "v4.at(" << i << ") is " << v4.at(i) << " ";
	// }
	// std::cout << std::endl;
	

	g_start = clock() - g_start;
	printf("Execution time (ms): %.2fms\n",
			(double)g_start / CLOCKS_PER_SEC * 1000);

	return 0;
}


// # include <vector>
// static void print(const std::vector<std::string>& v) {
// 	for (size_t i = 0; i < v.size(); i++)
// 		std::cout << "Element[" << i << "] == " << v[i] << std::endl;
// }
// int main()
// {
// 	clock_t g_start = clock();

// 	std::vector<std::string> obj;
// 	obj.push_back("Checking");
// 	obj.push_back("Testing");
// 	obj.push_back("Troll");
// 	obj.push_back("Mothe");
// 	obj.push_back("Welcome");
// 	std::cout << "obj: " << std::endl;
// 	print(obj);

// 	std::vector<std::string> obj2(obj.begin(), obj.end());
// 	std::cout << "obj2: " << std::endl;
// 	print(obj2);

// 	std::vector<std::string> obj3(obj2);
// 	std::cout << "obj3: " << std::endl;
// 	print(obj3);

// 	std::cout << "obj3[1]: " << obj3.at(1) << std::endl;
// 	std::cout << "obj3[2]: " << obj3[2] << std::endl;
// 	std::cout << "obj3 front: " << obj3.front() << std::endl;
// 	std::cout << "obj3 back: " << obj3.back() << std::endl;
// 	std::cout << "obj3 data: " << *obj3.data() << std::endl;

// 	std::vector<std::string>::iterator it = obj3.begin();
// 	for (; it < obj3.end(); it++) {
// 		std::cout << "it: " << *it << " ";
// 	}
// 	std::cout << std::endl;

// 	std::vector<std::string>::reverse_iterator rvrIt = obj3.rbegin();
// 	for (; rvrIt < obj3.rend(); rvrIt++) {
// 		std::cout << "rvrIt: " << *rvrIt << " ";
// 	}
// 	std::cout << std::endl;

// 	std::cout << "obj3 empty: " << std::boolalpha << obj3.empty() << std::endl;
// 	std::cout << "obj3 size: " << obj3.size() << std::endl;
// 	std::cout << "obj3 max_size: " << obj3.max_size() << std::endl;
// 	std::cout << "obj3 capacity: " << obj3.capacity() << std::endl;

// 	std::cout << "obj3 cleared\n";
// 	obj3.clear();
// 	std::cout << "obj3 empty: " << std::boolalpha << obj3.empty() << std::endl;
// 	std::cout << "obj3 size: " << obj3.size() << std::endl;
	
// 	std::cout << "obj3 insert (from obj2)\n";
// 	obj3.insert(obj3.begin(), obj2.begin(), obj2.end());
// 	std::cout << "obj3 size: " << obj3.size() << std::endl;
// 	std::cout << "obj3: " << std::endl;
// 	print(obj3);

// 	std::cout << "erase 4th Element\n";
// 	obj3.erase(obj3.begin() + 4);
// 	std::cout << "obj3: " << std::endl;
// 	print(obj3);

// 	obj3.push_back("foo");
// 	obj3.push_back("bar");
// 	obj3.push_back("kek");
// 	std::cout << "obj3: " << std::endl;
// 	print(obj3);

// 	obj3.pop_back();
// 	std::cout << "obj3: " << std::endl;
// 	print(obj3);

// 	obj3.resize(4);
// 	std::cout << "obj3: " << std::endl;
// 	print(obj3);

// 	obj3.assign(2, "newWord");
// 	std::cout << "obj3: " << std::endl;
// 	print(obj3);

// 	obj3.swap(obj2);
// 	std::cout << "obj3: " << std::endl;
// 	print(obj3);

// 	std::cout << "obj3 == obj2: " << std::boolalpha << (obj3 == obj2) << std::endl;
// 	std::cout << "obj3 < obj2: " << std::boolalpha << (obj3 < obj2) << std::endl;
// 	std::cout << "obj3 >= obj2: " << std::boolalpha << (obj3 >= obj2) <<  std::endl;

// 	// std::vector<int> v4;
// 	// for (int i = 0; i < 300000; i++) {
// 	// 	v4.push_back(i);
// 	// }
// 	// for (int i = 0; i < 300000; i++) {
// 	// 	std::cout << "v4.at(" << i << ") is " << v4.at(i) << " ";
// 	// }
// 	// std::cout << std::endl;
	

// 	g_start = clock() - g_start;
// 	printf("Execution time (ms): %.2fms\n",
// 			(double)g_start / CLOCKS_PER_SEC * 1000);

// 	return 0;
// }

#endif
