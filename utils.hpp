/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:22:57 by ali               #+#    #+#             */
/*   Updated: 2022/09/28 16:55:30 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <cstddef>
# include <iterator>
# include <iostream>
# include <sstream>


namespace ft
{
	//LEXICOGRAPHICAL_COMPARE
	template<class InputIt1, class InputIt2>
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1,
			InputIt2 first2, InputIt2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			if (*first1 < *first2)
				return true;
			first1++;
			first2++;
		}
		return (first2 != last2);
	};

	template<class InputIt1, class InputIt2, class Compare>
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1,
			InputIt2 first2, InputIt2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			if (comp(*first1, *first2))
				return true;
			first1++;
			first2++;
		}
		return (first2 != last2);
	};

	//EQUAL
	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
				return false;
			first1++;
			first2++;
		}
		return true;
	};

	template<class InputIt1, class InputIt2, class BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
	{
		while (first1 != last1)
		{
			if (!p(*first1,*first2))
				return false;
			first1++;
			first2++;
		}
		return true;
	};

	//PAIR
	template<class T1, class T2>
	struct	pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

		//CONSTRUCTORS
		pair() : first(), second() {};
		
		pair(const T1& x, const T2& y) : first(x), second(y) {};

		template<class U1, class U2>
		pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {};

		pair&	operator=(const pair& other)
		{
			if (*this == other)
				return *this;
			first = other.first;
			second = other.second;
			return *this;
		};
	};
	
	template<class T1, class T2>
	pair<T1, T2>	make_pair(T1 t, T2 u)
	{
		return pair<T1, T2>(t, u);
	};

	template<class T1, class T2>
	bool	operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		if (lhs.first != rhs.first)
			return false;
		return lhs.second == rhs.second;
	};

	template<class T1, class T2>
	bool	operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(lhs == rhs);
	};

	template<class T1, class T2>
	bool	operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		if (lhs.first > rhs.first)
			return false;
		if (lhs.first < rhs.first)
			return true;
		return lhs.second < rhs.second;
	};

	template<class T1, class T2>
	bool	operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return lhs == rhs || lhs < rhs;
	}

	template<class T1, class T2>
	bool	operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(lhs <= rhs);
	};

	template<class T1, class T2>
	bool	operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(lhs < rhs);
	};

	//TO_STRING()
	std::string	to_string(int n)
	{
		std::stringstream ss;
        ss << n;
        return (ss.str());
	}

	//ITERATOR_TRAITS
	//https://en.cppreference.com/w/cpp/iterator/iterator_traits
	//https://www.codeproject.com/Articles/36530/An-Introduction-to-Iterator-Traits
	template<class Iter>
	struct iterator_traits
	{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T*								pointer;
		typedef T&								reference;
	};


	template <class T>
	struct iterator_traits<const T*>
	{
		typedef	ptrdiff_t						difference_type;
		typedef	T								value_type;
		typedef	const T*						pointer;
		typedef	const T&						reference;
		typedef	std::random_access_iterator_tag	iterator_category;
	};

	//ENABLE IF
	//https://www.youtube.com/watch?v=Vkck4EU2lOU
	template<bool test, class T>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	//IS_RAI
	
	template <class iterator_category>
	struct is_input_it
	{
		static const bool value = false;
	};

	template <>
	struct is_input_it<std::input_iterator_tag>
	{
		static const bool value = true;
	};

	//IS_INTEGRAL
	template <typename T>
	struct is_integral
	{
		static const bool value = false;
	};

	template <>
	struct is_integral<bool>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<char>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned char>
	{
		static const bool value = true;
	};
	
	template <>
	struct is_integral<int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned int>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<long>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<long unsigned>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<short>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<short unsigned>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<long long>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<long long unsigned>
	{
		static const bool value = true;
	};
}

#endif
