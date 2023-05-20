/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackMain.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 21:39:59 by euyi              #+#    #+#             */
/*   Updated: 2023/02/18 22:07:37 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifdef _STACK_
# include "../stack.hpp"
# include <time.h>
# include <iomanip>
# include <stdio.h>


int main()
{
	clock_t g_start = clock();
	
	ft::stack<int> st;
	for (int i = 0; i < 100000; i++) {
		st.push(i * 3);
	}
	std::cout << "Top element (st): " << st.top() << std::endl;
	std::cout << "stack size (st): " << (st.empty() ? "true" : "false")
				<< std::endl;

	ft::stack<int> st2(st);
	std::cout << "Top element (st2): " << st2.top() << std::endl;
	std::cout << "stack size (st2): " << (st2.empty() ? "true" : "false")
				<< std::endl;
	std::cout << "stack empty (st2): " << (st2.empty() ? "true" : "false")
				<< std::endl;

	st2.push(99);
	st2.push(42);
	std::cout << "Top element (st2): " << st2.top() << std::endl;
	std::cout << "stack size (st2): " << (st2.empty() ? "true" : "false")
				<< std::endl;

	ft::stack<int> st3 = st2;
	std::cout << "st2 == st3: " << std::boolalpha << (st2 == st3) << std::endl;

	st3.pop();
	st3.pop();
	st3.pop();
	st3.pop();
	st3.pop();
	std::cout << "Top element (st3): " << st2.top() << std::endl;
	std::cout << "st2 == st3: " << (st2 == st3) << std::endl;
	std::cout << "st2 != st3: " << (st2 != st3) << std::endl;
	std::cout << "st2 < st3: " << (st2 < st3) << std::endl;
	std::cout << "st2 >= st3: " << (st2 >= st3) << std::endl;

	int count = 0;
	while (!st3.empty()) {
		count++;
		st3.pop();
	}
	std::cout << "Count of pop operations (st3): " << count << std::endl;
	std::cout << "stack empty (st3): " << (st3.empty())
				<< std::endl;

	g_start = clock() - g_start;
	printf("Execution time (ms): %.2fms\n",
			(double)g_start / CLOCKS_PER_SEC * 1000);

	return 0;
}



// # include <stack>
// int main()
// {
// 	clock_t g_start = clock();
	
// 	std::stack<int> st;
// 	for (int i = 0; i < 100000; i++) {
// 		st.push(i * 3);
// 	}
// 	std::cout << "Top element (st): " << st.top() << std::endl;
// 	std::cout << "stack size (st): " << (st.empty() ? "true" : "false")
// 				<< std::endl;

// 	std::stack<int> st2(st);
// 	std::cout << "Top element (st2): " << st2.top() << std::endl;
// 	std::cout << "stack size (st2): " << (st2.empty() ? "true" : "false")
// 				<< std::endl;
// 	std::cout << "stack empty (st2): " << (st2.empty() ? "true" : "false")
// 				<< std::endl;

// 	st2.push(99);
// 	st2.push(42);
// 	std::cout << "Top element (st2): " << st2.top() << std::endl;
// 	std::cout << "stack size (st2): " << (st2.empty() ? "true" : "false")
// 				<< std::endl;

// 	std::stack<int> st3 = st2;
// 	std::cout << "st2 == st3: " << std::boolalpha << (st2 == st3) << std::endl;

// 	st3.pop();
// 	st3.pop();
// 	st3.pop();
// 	st3.pop();
// 	st3.pop();
// 	std::cout << "Top element (st3): " << st2.top() << std::endl;
// 	std::cout << "st2 == st3: " << (st2 == st3) << std::endl;
// 	std::cout << "st2 != st3: " << (st2 != st3) << std::endl;
// 	std::cout << "st2 < st3: " << (st2 < st3) << std::endl;
// 	std::cout << "st2 >= st3: " << (st2 >= st3) << std::endl;

// 	int count = 0;
// 	while (!st3.empty()) {
// 		count++;
// 		st3.pop();
// 	}
// 	std::cout << "Count of pop operations (st3): " << count << std::endl;
// 	std::cout << "stack empty (st3): " << (st3.empty())
// 				<< std::endl;

// 	g_start = clock() - g_start;
// 	printf("Execution time (ms): %.2fms\n",
// 			(double)g_start / CLOCKS_PER_SEC * 1000);

// 	return 0;
// }

#endif


