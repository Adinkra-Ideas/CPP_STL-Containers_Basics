
#include <iostream>
#include <string>
#include <deque>

	// #include <map>
	// #include <stack>
	#include <vector>

	// #include "map.hpp"
	// #include "stack.hpp"
	#include "vector.hpp"


#include <stdlib.h>

# define TESTED_NAMESPACE ft

int		main(void)
{
	const int size = 5;
	TESTED_NAMESPACE::vector<int> const vct(size);

	TESTED_NAMESPACE::vector<int>::iterator it = vct.begin(); // <-- error expected

	for (int i = 0; i < size; ++i)
		it[i] = i;

	return (0);
}