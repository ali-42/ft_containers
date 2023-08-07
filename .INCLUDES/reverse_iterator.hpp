/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:24:11 by ali               #+#    #+#             */
/*   Updated: 2022/09/07 18:13:02 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "utils.hpp"

namespace ft
{
	//https://en.cppreference.com/w/cpp/iterator/reverse_iterator
	template <class Iter>
	class reverse_iterator
	{
		public:

		typedef Iter													iterator_type;
		typedef	typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iter>::value_type			value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer				pointer;
		typedef typename ft::iterator_traits<Iter>::reference			reference;

		//CONSTRUCTORS
		reverse_iterator() {};

		reverse_iterator(iterator_type it) : _it(it) {};

		template <class Iterator>
		reverse_iterator(const reverse_iterator<Iterator>& other) : _it(other.base()) {};


		//ACCESS
		iterator_type	base() const
		{
			return iterator_type(_it);
		};

		//OPERATORS
		reverse_iterator&	operator++()
		{
			_it--;
			return *this;
		};

		reverse_iterator	operator++(int)
		{
			reverse_iterator tmp = *this;
			++(*this);
			return tmp;
		};

		reverse_iterator&	operator--()
		{
			_it++;
			return *this;
		};

		reverse_iterator	operator--(int)
		{
			reverse_iterator tmp = *this;
			--(*this);
			return tmp;
		};
		
		reference	operator*() const
		{
			iterator_type tmp = _it;
			return *(--tmp);
		}

		pointer	operator->() const
		{
			return &(operator*());
		}

		reverse_iterator	operator+(difference_type n) const
		{
			iterator_type tmp(_it);
			tmp -= n;
			return reverse_iterator(tmp);
		}

		reverse_iterator	operator-(difference_type n) const
		{
			iterator_type tmp(_it);
			tmp += n;
			return reverse_iterator(tmp);
		}

		reverse_iterator&	operator+=(difference_type n)
		{
			_it -= n;
			return *this;
		}

		reverse_iterator&	operator-=(difference_type n)
		{
			_it += n;
			return *this;
		}

		reference operator[](difference_type n) const
		{
			return _it[-n - 1];
		}

		protected:
	
		iterator_type	_it;

	};

	template <class Iterator1, class Iterator2>
	bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>rhs)
	{
		return lhs.base() == rhs.base();
	};

	template <class Iterator1, class Iterator2>
	bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>rhs)
	{
		return lhs.base() != rhs.base();
	};

	template <class Iterator1, class Iterator2>
	bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>rhs)
	{
		return lhs.base() >= rhs.base();
	};

	template <class Iterator1, class Iterator2>
	bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>rhs)
	{
		return lhs.base() <= rhs.base();
	};

	template <class Iterator1, class Iterator2>
	bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>rhs)
	{
		return lhs.base() > rhs.base();
	};

	template <class Iterator1, class Iterator2>
	bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>rhs)
	{
		return lhs.base() < rhs.base();
	};
	
	template <class Iterator1, class Iterator2>
	std::ptrdiff_t operator+(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>rhs)
	{
		return lhs.base() + rhs.base();
	};

	template <class Iterator>
	reverse_iterator<Iterator> operator+(std::ptrdiff_t n, const reverse_iterator<Iterator>& rit)
	{
		return reverse_iterator<Iterator>(rit.base() - n);
	}

	template <class Iterator1, class Iterator2>
	std::ptrdiff_t operator-(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>rhs)
	{
		return rhs.base() - lhs.base();
	};
}

#endif
