/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 18:42:50 by ali               #+#    #+#             */
/*   Updated: 2022/09/07 18:46:53 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

# include "utils.hpp"

namespace ft
{
	template <class T>
	struct bstNode
	{
		T			value;
		bstNode*	parent;
		bstNode*	left;
		bstNode*	right;

		bstNode() : T(), parent(NULL), left(NULL), right(NULL) {};

		bstNode(const T& v = T(), bstNode* p = NULL, bstNode* l = NULL, bstNode* r = NULL)
		: value(v), parent(p), left(l), right(r) {};

		bstNode(const bstNode& other)
		: value(other.value), parent(other.parent), left(other.left), right(other.right) {};

		~bstNode() {};

		bstNode&	operator=(const bstNode& other)
		{
			if (this == &other)
				return *this;
			value = other.value;
			parent = other.parent;
			left = other.left;
			right = other.right;
			return *this;
		};

		bstNode*	findMax()
		{
			bstNode* max = this;

			if (!max)
				return NULL;

			while (max->right)
				max = max->right;
			return max;
		}

		bstNode*	findMin()
		{
			bstNode* min = this;

			if (!min)
				return NULL;

			while (min->left)
				min = min->left;
			return min;
		}

		bstNode*	next() 
		{
			bstNode* tmp = this;

			if (tmp->right)
				return tmp->right->findMin();

			bstNode* tmpParent = tmp->parent;
			while (tmpParent && tmp == tmpParent->right)
			{
				tmp = tmpParent;
				tmpParent = tmpParent->parent;
			}
			return tmpParent;
		};

		bstNode*	prev() 
		{
			bstNode* tmp = this;

			if (tmp->left)
				return tmp->left->findMax();
			
			bstNode* tmpParent = tmp->parent;
			while (tmpParent && tmp == tmpParent->left)
			{
				tmp = tmpParent;
				tmpParent = tmpParent->parent;
			}
			return tmpParent;
		};
	};

	template<class T, class Node>
	class mapIterator
	{
		public:
			typedef	T								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef std::bidirectional_iterator_tag	iterator_category;
			
			mapIterator() : _ptr(NULL) {};

			mapIterator(const mapIterator &other)
			{
				*this = other;
			};

			mapIterator(Node* ptr) : _ptr(ptr) {};

			~mapIterator() {};

			Node*	base() const
			{
				return _ptr;
			};

			mapIterator&	operator=(const mapIterator& other)
			{
				_ptr = other._ptr;
				return *this;
			};

			mapIterator&	operator++()
			{
				_ptr = _ptr->next();
				return *this;
			};

			mapIterator&	operator--()
			{
				_ptr = _ptr->prev();
				return *this;
			};

			mapIterator	operator++(int)
			{
				mapIterator	tmp = *this;
				++(*this);
				return tmp;
			};

			mapIterator	operator--(int)
			{
				mapIterator	tmp = *this;
				--(*this);
				return tmp;
			};

			bool	operator==(const mapIterator& other) const
			{
				return _ptr == other._ptr;
			};

			bool	operator!=(const mapIterator& other) const
			{
				return !(*this == other);
			};

			reference	operator*() const
			{
				return _ptr->value;
			}

			pointer	operator->() const
			{
				return &(_ptr->value);
			};

		protected:
			Node*	_ptr;
	};

	template<class T, class Node, class mapIterator>
	class const_mapIterator
	{
		public:
			typedef	T								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef std::bidirectional_iterator_tag	iterator_category;
			
			const_mapIterator() : _ptr(NULL) {};

			const_mapIterator(const const_mapIterator &other)
			{
				*this = other;
			};

			const_mapIterator(const mapIterator &other)
			{
				_ptr = other.base();
			};

			const_mapIterator(Node* ptr) : _ptr(ptr) {};

			~const_mapIterator() {};

			Node*	base() const
			{
				return _ptr;
			};

			const_mapIterator&	operator=(const const_mapIterator& other)
			{
				_ptr = other._ptr;
				return *this;
			};

			const_mapIterator&	operator++()
			{
				_ptr = _ptr->next();
				return *this;
			};

			const_mapIterator&	operator--()
			{
				_ptr = _ptr->prev();
				return *this;
			};

			const_mapIterator	operator++(int)
			{
				const_mapIterator	tmp = *this;
				++(*this);
				return tmp;
			};

			const_mapIterator	operator--(int)
			{
				const_mapIterator	tmp = *this;
				--(*this);
				return tmp;
			};

			bool	operator==(const const_mapIterator& other) const
			{
				return _ptr == other._ptr;
			};

			bool	operator!=(const const_mapIterator& other) const
			{
				return !(*this == other);
			};

			reference	operator*() const
			{
				return _ptr->value;
			}

			pointer	operator->() const
			{
				return &(_ptr->value);
			};

		protected:
			Node*	_ptr;
	};
}

#endif
