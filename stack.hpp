/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:28:41 by ali               #+#    #+#             */
/*   Updated: 2022/06/30 19:00:04 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"
# include "utils.hpp"

namespace ft
{
	template<class T, class Container = vector<T> >
	class stack
	{
		public:
			typedef Container						container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;

			//CONSTRUCTORS
			explicit stack(const container_type& cont = container_type())
			: c(cont) {};
			
			stack(const stack& other) : c()
			{
				*this = other;
			};

			// DESTRUCTOR
			~stack() {};

			//ASSIGNMENT
			stack&	operator=(const stack& other)
			{
				c = other.c;
				return *this;
			};

			//ACCESS
			reference	top()
			{
				return c.back();
			}

			const_reference	top() const
			{
				return c.back();
			}

			// CAPACITY
			bool	empty() const
			{
				return c.empty();
			}

			size_type	size() const
			{
				return c.size();
			}

			//MODIFIERS
			void	push(const value_type& value)
			{
				c.push_back(value);
			}

			void	pop()
			{
				c.pop_back();
			}

			template<class T_, class Container_>
			friend bool operator==(const stack<T_, Container_>& lhs, const stack<T_, Container_>& rhs);

			template<class T_, class Container_>
			friend bool operator!=(const stack<T_, Container_>& lhs, const stack<T_, Container_>& rhs);

			template<class T_, class Container_>
			friend bool operator<(const stack<T_, Container_>& lhs, const stack<T_, Container_>& rhs);

			template<class T_, class Container_>
			friend bool operator<=(const stack<T_, Container_>& lhs, const stack<T_, Container_>& rhs);

			template<class T_, class Container_>
			friend bool operator>(const stack<T_, Container_>& lhs, const stack<T_, Container_>& rhs);

			template<class T_, class Container_>
			friend bool operator>=(const stack<T_, Container_>& lhs, const stack<T_, Container_>& rhs);


		protected:
			container_type	c;

	};

	template<class T, class Container >
	bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs.c == rhs.c);
	};

	template<class T, class Container >
	bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs.c != rhs.c);
	};

	template<class T, class Container >
	bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs.c < rhs.c);
	};

	template<class T, class Container >
	bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs.c <= rhs.c);
	};

	template<class T, class Container >
	bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs.c > rhs.c);
	};

	template<class T, class Container >
	bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
	{
		return (lhs.c >= rhs.c);
	};
}

#endif
