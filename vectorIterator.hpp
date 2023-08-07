/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:03:25 by ali               #+#    #+#             */
/*   Updated: 2022/09/07 17:34:55 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

#include "utils.hpp"

namespace ft
{
	//https://www.simplilearn.com/tutorials/cpp-tutorial/iterators-in-cpp
	template<class T>
	class vectorIterator
	{
		public:

			typedef T								value_type;
			typedef	value_type&						reference;
			typedef	value_type*						pointer;
			typedef	std::ptrdiff_t					difference_type;
			typedef std::random_access_iterator_tag	iterator_category;

			//CONSTRUCTORS
			vectorIterator(): _ptr(0) {};

			vectorIterator(const vectorIterator& other)
			{
				*this = other;
			};

			vectorIterator(pointer p) : _ptr(p) {};
			
			operator vectorIterator<const T>() const
			{
				return vectorIterator<const T>(this->_ptr);
			}

			//DESTRUCTOR
			virtual ~vectorIterator() {};

			//ASSIGNEMENT
			vectorIterator&	operator=(const vectorIterator<const T>& other)
			{
				if (this == &other)
					return *this;
				_ptr = other.base();
				return *this;
			};

			//OPERATORS
			vectorIterator&	operator++()
			{
				_ptr++;
				return *this;
			};

			vectorIterator	operator++(int)
			{
				vectorIterator	tmp = *this;
				++(*this);
				return tmp;
			};

			vectorIterator&	operator--()
			{
				_ptr--;
				return *this;
			};

			vectorIterator	operator--(int)
			{
				vectorIterator	tmp = *this;
				--(*this);
				return tmp;
			};

			bool	operator==(const vectorIterator<const T>& other) const
			{
				return (_ptr == other.base());
			};

			bool	operator!=(const vectorIterator<const T>& other) const
			{
				return (_ptr != other.base());
			};

			bool	operator<=(const vectorIterator<const T>& other) const
			{
				return (_ptr <= other.base());
			};

			bool	operator>=(const vectorIterator<const T>& other) const
			{
				return (_ptr >= other.base());
			};

			bool	operator<(const vectorIterator<const T>& other) const
			{
				return (_ptr < other.base());
			};

			bool	operator>(const vectorIterator<const T>& other) const
			{
				return (_ptr > other.base());
			};

			value_type&	operator*()
			{
				return *_ptr;
			};

			value_type*	operator->()
			{
				return _ptr;
			};

			vectorIterator	operator+(difference_type n)
			{
				return _ptr + n;
			};

			difference_type	operator+(const vectorIterator<const T>& other) const
			{
				return _ptr + other.base();
			}

			friend vectorIterator	operator+(difference_type n, vectorIterator it)
			{
				return it.base() + n;
			}

			vectorIterator	operator-(difference_type n)
			{
				return _ptr - n;
			};

			difference_type	operator-(const vectorIterator<const T>& other) const
			{
				return _ptr - other.base();
			}

			vectorIterator&	operator+=(difference_type n)
			{
				_ptr += n;
				return *this;
			};

			vectorIterator&	operator-=(difference_type n)
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

	template<class T>
	std::ptrdiff_t	operator-(const ft::vectorIterator<T>& lhs,
			const ft::vectorIterator<T>& rhs)
	{
		return lhs.base() - rhs.base();
	}
	
	template<class T>
	std::ptrdiff_t	operator+(const ft::vectorIterator<T>& lhs,
			const ft::vectorIterator<T>& rhs)
	{
		return lhs.base() + rhs.base();
	}

}

#endif
