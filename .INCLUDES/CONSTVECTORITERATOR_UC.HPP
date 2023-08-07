/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constVectorIterator.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:03:25 by ali               #+#    #+#             */
/*   Updated: 2022/09/06 16:35:30 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTVECTORITERATOR_HPP
# define CONSTVECTORITERATOR_HPP

#include "utils.hpp"
#include "vectorIterator.hpp"

namespace ft
{
	//https://www.simplilearn.com/tutorials/cpp-tutorial/iterators-in-cpp
	template<class T, class vectorIterator >
	class constVectorIterator
	{
		public:

			typedef const T							value_type;
			typedef	value_type&						reference;
			typedef	value_type*						pointer;
			typedef	std::ptrdiff_t					difference_type;
			typedef std::random_access_iterator_tag	iterator_category;

			//CONSTRUCTORS
			constVectorIterator(): _ptr(0) {};

			constVectorIterator(const constVectorIterator& other)
			{
				*this = other;
			};

			constVectorIterator(const vectorIterator & other)
			{
				_ptr = other.base();
			};

			constVectorIterator(pointer p) : _ptr(p) {};
			
			//DESTRUCTOR
			virtual ~constVectorIterator() {};

			//ASSIGNEMENT
			constVectorIterator&	operator=(const constVectorIterator& other)
			{
				if (this == &other)
					return *this;
				_ptr = other._ptr;
				return *this;
			};

			//OPERATORS
			constVectorIterator&	operator++()
			{
				_ptr++;
				return *this;
			};

			constVectorIterator	operator++(int)
			{
				constVectorIterator	tmp = *this;
				++(*this);
				return tmp;
			};

			constVectorIterator&	operator--()
			{
				_ptr--;
				return *this;
			};

			constVectorIterator	operator--(int)
			{
				constVectorIterator	tmp = *this;
				--(*this);
				return tmp;
			};

			bool	operator==(const constVectorIterator& other) const
			{
				return (_ptr == other._ptr);
			};

			bool	operator!=(const constVectorIterator& other) const
			{
				return (_ptr != other._ptr);
			};

			bool	operator<=(const constVectorIterator& other) const
			{
				return (_ptr <= other._ptr);
			};

			bool	operator>=(const constVectorIterator& other) const
			{
				return (_ptr >= other._ptr);
			};

			bool	operator<(const constVectorIterator& other) const
			{
				return (_ptr < other._ptr);
			};

			bool	operator>(const constVectorIterator& other) const
			{
				return (_ptr > other._ptr);
			};

			value_type&	operator*()
			{
				return *_ptr;
			};

			value_type*	operator->()
			{
				return _ptr;
			};

			constVectorIterator	operator+(difference_type n)
			{
				return _ptr + n;
			};

			constVectorIterator	operator-(difference_type n)
			{
				return _ptr - n;
			};

			constVectorIterator&	operator+=(difference_type n)
			{
				_ptr += n;
				return *this;
			};

			constVectorIterator&	operator-=(difference_type n)
			{
				_ptr -= n;
				return *this;
			};

			value_type&	operator[](difference_type n) const
			{
				return _ptr[n];
			};

			pointer	base() const
			{
				return _ptr;
			}

		private:
			pointer _ptr;
	};

	template<class T, class vectorIterator>
	std::ptrdiff_t	operator-(const ft::constVectorIterator<T, vectorIterator>& lhs,
			const ft::constVectorIterator<T, vectorIterator>& rhs)
	{
		return lhs.base() - rhs.base();
	}
	
	template<class T, class vectorIterator >
	std::ptrdiff_t	operator+(const ft::constVectorIterator<T, vectorIterator>& lhs,
			const ft::constVectorIterator<T, vectorIterator>& rhs)
	{
		return lhs.base() + rhs.base();
	}

}

#endif
