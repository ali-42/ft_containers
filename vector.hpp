/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:27:06 by ali               #+#    #+#             */
/*   Updated: 2022/09/28 23:10:31 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "vectorIterator.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"
#include <limits>

namespace ft
{
	//https://en.cppreference.com/w/cpp/container/vector
	template<class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:

		typedef T												value_type;
		typedef Allocator										allocator_type;
		typedef std::size_t										size_type;
		typedef	std::ptrdiff_t									difference_type;
		typedef value_type&										reference;
		typedef const value_type&								const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef	typename allocator_type::const_pointer			const_pointer;
		typedef	ft::vectorIterator<value_type>					iterator;
		typedef	ft::vectorIterator<const value_type>			const_iterator;
		typedef	ft::reverse_iterator<iterator>					reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		
		private:
			pointer			_ptr;
			size_type		_size;
			size_type		_cap;
			allocator_type	_alloc;

			void	_extend()
			{
				if (_cap == this->max_size())
					throw std::length_error("vector::reserve");
				if (_cap == 0)
					this->reserve(_cap + 1);
				else if (_cap * 2 > this->max_size())
					this->reserve(this->max_size());
				else
					this->reserve(_cap * 2);
			};

		public:
			// CONSTRUCTORS
			vector()
			: _ptr(0), _size(0), _cap(0), _alloc(allocator_type()) {};

			explicit vector(const allocator_type& alloc)
			: _ptr(0), _size(0), _cap(0), _alloc(alloc) {};

			explicit vector(size_type count, const value_type& value = value_type(),
					const allocator_type& alloc = allocator_type())
			: _ptr(0), _size(0), _cap(0), _alloc(alloc)
			{
				if (count > this->max_size())
					throw std::length_error("vector::reserve");
				_ptr = _alloc.allocate(count);
				for (size_type i = 0; i < count; i++)
					_alloc.construct(_ptr + i, value);
				_size = count;
				_cap = count;
			};

			template<class InputIt>
			vector(InputIt first, InputIt last, 
					const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0)
			: _ptr(0), _size(0), _cap(0), _alloc(alloc)
			{
				assign(first, last);
			}; 

			vector(const vector& other)
			: _ptr(0), _size(0), _cap(0), _alloc(allocator_type())
			{
				*this = other;
			};

			//DESTRUCTOR
			~vector()
			{
				this->clear();
				if (_ptr)
					_alloc.deallocate(_ptr, _cap);
			};

			//ASSIGNMENT
			vector& operator=(const vector& other)
			{
				if (*this == other)
					return *this;
				clear();
				reserve(other._size);
				for (const_iterator it = other.begin(); it != other.end(); it++)
					push_back(*it);
				return *this;
			};

			void	assign(size_type count, const_reference value)
			{
				this->clear();
				if (_cap < count)
					reserve(count);
				for (size_type i = 0; i < count; i++)
					push_back(value);
			};

			template<class InputIt>
			typename ft::enable_if<!ft::is_integral<InputIt>::value, void>::type
			assign(InputIt first, InputIt last)
			{
				clear();

				if (ft::is_input_it<typename ft::iterator_traits<InputIt>::iterator_category>::value)
				{
					while (first != last)
					{
						push_back(*first);
						first++;
					}
					return ;
				}
				typename ft::iterator_traits<InputIt>::difference_type size = 0;
				InputIt	tmp = first;
				while (tmp != last)
				{
					size++;
					tmp++;
				}

				reserve(size);
				while (first != last)
				{
					push_back(*first);
					first++;
				}
			};

			
			//GET_ALLOC
			allocator_type	get_allocator() const
			{
				return _alloc;
			};

			//ELEMENT ACCESS
			reference	at(size_type pos)
			{
				if (pos >= _size)
					throw std::out_of_range("vector::_M_range_check: __n (which is "
							+ ft::to_string(pos) + ") >= this->size() (which is "
							+ ft::to_string(_size) + ")");
				return *(_ptr + pos);
			};

			const_reference	at(size_type pos) const
			{
				if (pos >= _size)
					throw std::out_of_range("vector::_M_range_check: __n (which is "
							+ ft::to_string(pos) + ") >= this->size() (which is "
							+ ft::to_string(_size) + ")");
				return *(_ptr + pos);
			};

			reference	operator[](size_type pos)
			{
				return *(_ptr + pos);
			};

			const_reference	operator[](size_type pos) const
			{
				return *(_ptr + pos);
			};

			reference front()
			{
				return *_ptr;
			};

			const_reference front() const
			{
				return *_ptr;
			};

			reference back()
			{
				return *(_ptr + _size - 1);
			};

			const_reference back() const
			{
				return *(_ptr + _size - 1);
			};

			pointer	data()
			{
				return _ptr;
			};

			const_pointer	data() const
			{
				return _ptr;
			};

			//ITERATORS
			iterator	begin()
			{
				iterator it(_ptr);
				return (it);
			};

			const_iterator	begin() const
			{
				const_iterator it(_ptr);
				return (it);
			};
			
			iterator	end()
			{
				iterator it(_ptr + _size);
				return (it);
			};

			const_iterator	end() const
			{
				const_iterator it(_ptr + _size);
				return (it);
			};

			reverse_iterator rbegin()
			{
				reverse_iterator it(_ptr + _size);
				return (it);
			};

			const_reverse_iterator rbegin() const
			{
				const_reverse_iterator it(_ptr + _size);
				return (it);
			};

			reverse_iterator rend()
			{
				reverse_iterator it(_ptr);
				return (it);
			};

			const_reverse_iterator rend() const
			{
				const_reverse_iterator it(_ptr);
				return (it);
			};

			//CAPACITY
			bool empty() const
			{
				if (begin() == end())
					return true;
				return false;
			};

			size_type size() const
			{
				return _size;
			};

			size_type max_size() const
			{
				return _alloc.max_size();
			};

			void reserve(size_type new_cap)
			{
				pointer	newPtr;

				if (new_cap <= _cap)
					return ;
				if (new_cap > max_size())
					throw(std::length_error("vector::reserve"));
				newPtr = _alloc.allocate(new_cap);
				for (size_type i = 0; i < _size; i++)
				{
					_alloc.construct(newPtr + i, *(_ptr + i));
					_alloc.destroy(_ptr + i);
				}
				if (_ptr)
					_alloc.deallocate(_ptr, _cap);
				_cap = new_cap;
				_ptr = newPtr;
			};

			size_type capacity() const
			{
				return _cap;
			};

			//MODIFIERS
			void clear()
			{
				for (iterator it = begin(); it != end(); it++)
					_alloc.destroy(&(*it));
				_size = 0;
			};

			iterator insert(iterator pos, const_reference value)
			{
				difference_type	intPos = pos - begin();
				vector	tmp(begin() + intPos, end());

				for (size_type i = 0; i < tmp.size(); i++)
					pop_back();
				push_back(value);
				for (iterator it = tmp.begin(); it != tmp.end(); it++)
					push_back(*it);
				return (begin() + intPos);
			};

			void insert(iterator pos, size_type count, const_reference value)
			{
				difference_type	intPos = pos - begin();
				vector	tmp(begin() + intPos, end());

				if (count + _size > _cap)
					reserve(2 * _size);
				if (_cap < _size + count)
					reserve(_size + count);
				for (size_type i = 0; i < tmp.size(); i++)
					pop_back();
				for (size_type i = 0; i < count; i++)
					push_back(value);
				for (iterator it = tmp.begin(); it != tmp.end(); it++)
					push_back(*it);
			};

			template<class InputIt>
			typename ft::enable_if<!ft::is_integral<InputIt>::value, void>::type
			insert(iterator pos, InputIt first, InputIt last)
			{
				difference_type	intPos = pos - begin();
				vector	tmp(begin() + intPos, end());

				for (size_type i = 0; i < tmp.size(); i++)
					pop_back();
				while (first != last)
				{
					push_back(*first);
					first++;
				}
				for (iterator it = tmp.begin(); it != tmp.end(); it++)
					push_back(*it);
			};

			iterator erase(iterator pos)
			{
				vector	tmp(pos + 1, end());

				for (size_type i = 0; i < tmp.size(); i++)
					pop_back();
				pop_back();
				for (iterator it = tmp.begin(); it != tmp.end(); it++)
					push_back(*it);
				return pos;
			};

			iterator erase(iterator first, iterator last)
			{
				vector		tmp(last, end());
				iterator	tmpIt = first;
				size_type	count = 0;

				while (tmpIt != last)
				{
					count++;
					tmpIt++;
				}
				for (size_type i = 0; i < tmp.size(); i++)
					pop_back();
				for (size_type i = 0; i < count; i++)
					pop_back();
				for (iterator it = tmp.begin(); it != tmp.end(); it++)
					push_back(*it);
				return first;
			};

			void push_back(const_reference value)
			{
				if (_size == _cap)
					_extend();
				_alloc.construct(_ptr + _size, value);
				_size++;
			};

			void pop_back()
			{
				if (_size == 0)
					return ;
				_alloc.destroy(_ptr + _size - 1);
				_size--;
			};

			void resize(size_type count, value_type value = value_type())
			{
				if (count > _cap && count > _size * 2)
					reserve(count);
				while (_size > count)
					pop_back();
				if (_size == count)
					return ;
				while (_size < count)
					push_back(value);
			};

			void swap(vector& other)
			{
				pointer		tmpPtr = other._ptr;
				size_type	tmpSize = other._size;
				size_type	tmpCap = other._cap;

				other._ptr = _ptr;
				other._size = _size;
				other._cap = _cap;

				_ptr = tmpPtr;
				_size = tmpSize;
				_cap = tmpCap;
			};
	};

	template<class T, class Allocator>
	bool operator==(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t	i = 0; i < lhs.size(); i++)
		{
			if (lhs[i] != rhs[i])
				return false;
		}
		return true;
	};

	template<class T, class Allocator>
	bool operator!=(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs)
	{
		return !(lhs == rhs);
	};

	template<class T, class Allocator>
	bool operator<(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs)
	{
		if (lhs == rhs)
			return false;
		size_t	i = 0;
		while (i < lhs.size())
		{
			if (i == rhs.size() || lhs[i] > rhs[i])
				return false;
			else if (lhs[i] < rhs[i])
				return true;
			i++;
		}
		return i != rhs.size();
	};

	template<class T, class Allocator>
	bool operator<=(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs)
	{
		if (lhs == rhs)
			return true;
		return (lhs < rhs);
	};

	template<class T, class Allocator>
	bool operator>(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs)
	{
		return !(lhs <= rhs);
	};

	template<class T, class Allocator>
	bool operator>=(const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs)
	{
		return !(lhs < rhs);
	};

	template<class T, class Allocator>
	void swap(vector<T,Allocator>& lhs, vector<T,Allocator>& rhs)
	{
		lhs.swap(rhs);
	};
}

#endif
