#ifndef __ALGORITHM_HPP__
# define __ALGORITHM_HPP__

namespace ft {

// *******************************************
//    Equal
// *******************************************
template <class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
	for (; first1 != last1; ++first1, ++first2) {
		if (!(*first1 == *first2)) {
			return false;
		}
	}
	if ( first1 == last1 && first2 != last2 )
		return false;
			
	return true;
}

// ****************************************************************************************
//     Lexicographical Compare (Return true only if any of it1 < it2 or it1 len < it2 len)
// ****************************************************************************************
template <class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                             InputIt2 last2) {
	for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2) {
		if (*first1 < *first2) return true;
		if (*first2 < *first1) return false;
	}
	return (first1 == last1) && (first2 != last2);
}

}

#endif
