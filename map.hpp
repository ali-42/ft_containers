/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:36:06 by ali               #+#    #+#             */
/*   Updated: 2022/09/28 22:08:37 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include "utils.hpp"
# include "reverse_iterator.hpp"
# include "mapIterator.hpp"

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key>, 
		class Allocator = std::allocator<ft::pair<const Key, T> > > 
	class map
	{
		public:

			typedef Key															key_type;
			typedef T															mapped_type;
			typedef ft::pair<const Key, T>										value_type;
			typedef std::size_t													size_type;
			typedef std::ptrdiff_t												difference_type;
			typedef Compare														key_compare;
			typedef bstNode<value_type>											mapNode;
			typedef Allocator													allocator_type;
			typedef	value_type&													reference;
			typedef const value_type&											const_reference;
			typedef typename Allocator::pointer									pointer;
			typedef typename Allocator::const_pointer							const_pointer;
			typedef	ft::mapIterator<value_type, mapNode>						iterator;
			typedef ft::mapIterator<const value_type, mapNode>					const_iterator;
		//	typedef ft::const_mapIterator<const value_type, mapNode, iterator>	const_iterator;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;

		private:

			typedef typename std::allocator<bstNode<value_type> >	node_allocator_type;

			mapNode*								_tree;
			mapNode*								_end;
			mapNode*								_rend;
			size_type								_size;
			Compare									_comp;
			allocator_type							_alloc;
			node_allocator_type						_nodeAlloc;

		public:

			class value_compare
			{
				friend class map;
				public:
					bool		result_type;
					value_type	first_argument_type;
					value_type	second_argument_type;


					bool		operator()(const value_type& lhs, const value_type& rhs) const
					{
						return comp(lhs.first, rhs.first);
					};

				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {};
			};

			//CONSTRUCTORS
			explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator())
			: _tree(NULL), _end(NULL), _rend(NULL), _size(0), _comp(comp), _alloc(alloc), _nodeAlloc()
			{
				_end = _nodeAlloc.allocate(1);
				_nodeAlloc.construct(_end, mapNode(value_type(), NULL, NULL, NULL));
				_rend = _nodeAlloc.allocate(1);
				_nodeAlloc.construct(_rend, mapNode(value_type(), _end, NULL, NULL));
			};

			template<class InputIt>
			map(InputIt first, InputIt last, const Compare& comp = Compare(),
					const Allocator& alloc = Allocator(),
					typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0)
			: _tree(NULL), _end(NULL), _rend(NULL), _size(0), _comp(comp), _alloc(alloc), _nodeAlloc()
			{
				_end = _nodeAlloc.allocate(1);
				_nodeAlloc.construct(_end, mapNode(value_type(), NULL, NULL, NULL));
				_rend = _nodeAlloc.allocate(1);
				_nodeAlloc.construct(_rend, mapNode(value_type(), _end, NULL, NULL));

				insert(first, last);
			};

			map(const map& other) : _tree(NULL), _end(NULL), _rend(NULL), _size(0), _comp(), _alloc(), _nodeAlloc()
			{
				_end = _nodeAlloc.allocate(1);
				_nodeAlloc.construct(_end, mapNode(value_type(), NULL, NULL, NULL));
				_rend = _nodeAlloc.allocate(1);
				_nodeAlloc.construct(_rend, mapNode(value_type(), _end, NULL, NULL));

				*this = other;
			};
			
			//DESTRUCTOR
			~map()
			{
				clear();

				_nodeAlloc.destroy(_end);
				_nodeAlloc.deallocate(_end, 1); 
				_nodeAlloc.destroy(_rend);
				_nodeAlloc.deallocate(_rend, 1); 
			};

			//ASSIGNMENT
			map&	operator=(const map& other)
			{
				if (this == &other)
					return *this;
				clear();
				insert(other.begin(), other.end());
				return *this;
			};

			//GETTER
			allocator_type get_allocator() const
			{
				return _alloc;
			};

			//ELEMENT_ACCESS
			T&	at(const Key& key)
			{
				iterator it = find(key);
				if (it == end())
					throw std::out_of_range("map::at");
				return it->second;
			};

			const T&	at(const Key& key) const
			{
				const_iterator it = find(key);
				if (it == end())
					throw std::out_of_range("map::at");
				return it->second;
			};

			T&	operator[](const Key& key)
			{
				return (*(this->insert(value_type(key, T())).first)).second;
			};

			//ITERATORS
			iterator	begin()
			{
				return iterator(_rend->parent);
			};

			const_iterator	begin() const
			{
				return const_iterator(_rend->parent);
			};

			iterator	end()
			{
				return iterator(_end);
			};

			const_iterator	end() const
			{
				return const_iterator(_end);
			};

			reverse_iterator	rbegin()
			{
				return reverse_iterator(_end);
			};

			const_reverse_iterator	rbegin() const
			{
				return const_reverse_iterator(_end);
			};

			reverse_iterator	rend()
			{
				return reverse_iterator(_rend->parent);
			};

			const_reverse_iterator	rend() const
			{
				return const_reverse_iterator(_rend->parent);
			};

			//CAPACITY
			bool	empty() const
			{
				if (_size == 0)
					return true;
				return false;
			};

			size_type	size() const
			{
				return _size;
			};

			size_type	max_size() const
			{
				return _alloc.max_size();
			};


			//MODIFIERS
			void	clear()
			{
				clearTree(_tree);
				_size = 0;
				_tree = NULL;
				_rend->parent = _end;
				_end->parent = NULL;
			};

			ft::pair<iterator, bool>	insert(const value_type& value)
			{
				if (_tree == NULL)
				{
					_tree = _nodeAlloc.allocate(1);
					_nodeAlloc.construct(_tree, mapNode(value, NULL, _rend, _end));
					_size++;
					_end->parent = _tree;
					_rend->parent = _tree;
					return ft::make_pair(iterator(_tree), true);
				}
				else
				{
					mapNode* parentNode = findNode(value.first, _tree);

					if (parentNode->value.first == value.first)
						return ft::make_pair(iterator(parentNode), false);

					mapNode* newNode = _nodeAlloc.allocate(1);
					if (parentNode->left == _rend && _comp(value.first, parentNode->value.first))
					{
						_nodeAlloc.construct(newNode, mapNode(value, parentNode, _rend, NULL));
						_rend->parent = newNode;
					}
					else if (parentNode->right == _end && !_comp(value.first, parentNode->value.first))
					{
						_nodeAlloc.construct(newNode, mapNode(value, parentNode, NULL, _end));
						_end->parent = newNode;
					}
					else 
						_nodeAlloc.construct(newNode, mapNode(value, parentNode, NULL, NULL));

					if (_comp(value.first, parentNode->value.first))
						parentNode->left = newNode;
					else
						parentNode->right = newNode;
					_size++;
					return ft::make_pair(iterator(newNode), true);
				}
			};

			iterator	insert(iterator hint, const value_type& value)
			{
				(void)hint;
				return (insert(value)).first;
			};

			template<class InputIt>
			typename ft::enable_if<!ft::is_integral<InputIt>::value, void>::type
			insert(InputIt first, InputIt last)
			{
				while (first != last)
				{
					insert(*first);
					first++;
				}
			};

			void	erase(iterator pos)
			{
				mapNode* node = pos.base();

				if (node == NULL)
					return ;
				else if (node->left == _rend && node->right == _end)
				{
					_rend->parent = _end;
					_end->parent = NULL;
					_nodeAlloc.destroy(node);
					_nodeAlloc.deallocate(node, 1);
					_tree = NULL;
					_size--;

				}
				else if (isLeaf(node))
				{
					unlinkParent(node);
					_nodeAlloc.destroy(node);
					_nodeAlloc.deallocate(node, 1);
					_size--;
				}
				else if (hasOneChild(node))
				{
					linkParentToChild(node);
					_nodeAlloc.destroy(node);
					_nodeAlloc.deallocate(node, 1);
					_size--;
				}
				else
				{
					mapNode* min = node->right->findMin();
					mapNode* newNode = _nodeAlloc.allocate(1);
					_nodeAlloc.construct(newNode, mapNode(min->value, node->parent, node->left, node->right));
					node->left->parent = newNode;
					node->right->parent = newNode;
					if (node->parent && node->parent->left == node)
						node->parent->left = newNode;
					if (node->parent && node->parent->right == node)
						node->parent->right = newNode;
					if (node == _tree)
						_tree = newNode;
					_nodeAlloc.destroy(node);
					_nodeAlloc.deallocate(node, 1);
					erase(min);
				}
			};

			void	erase(iterator first, iterator last)
			{
				iterator tmp;

				if (first == last)
					return ;
				tmp = first;
				first++;
				erase(first, last);
				erase(tmp);
			};

			size_type	erase(const Key& key)
			{
				iterator it = find(key);
				if (it == end())
					return 0;
				else
				{
					erase(it);
					return 1;
				}
			};

			void	swap(map& other)
			{
				if (*this == other)
					return ;

				mapNode*	tmpNode;
				size_type	tmpSize;

				tmpNode = other._tree;
				other._tree = _tree;
				_tree = tmpNode;
				
				tmpNode = other._end;
				other._end = _end;
				_end = tmpNode;

				tmpNode = other._rend;
				other._rend = _rend;
				_rend = tmpNode;

				tmpSize = other._size;
				other._size = _size;
				_size = tmpSize;
			};

			//LOOKUP
			size_type	count(const Key& key) const
			{
				if (find(key) == _end)
					return 0;
				return 1;
			};

			iterator find(const Key& key)
			{
				return iterator(getNode(key));
			};

			const_iterator find(const Key& key) const
			{
				return const_iterator(getNode(key));
			};

			ft::pair<iterator, iterator>	equal_range(const Key& key)
			{
				return ft::make_pair(lower_bound(key), upper_bound(key));
			};

			ft::pair<const_iterator, const_iterator>	equal_range(const Key& key) const
			{
				return ft::make_pair(lower_bound(key), upper_bound(key));
			};

			iterator	lower_bound(const Key& key)
			{
				iterator it = begin();
				while (it != end())
				{
					if (!_comp(it->first, key))
						return it;
					it++;
				}
				return end();
			};

			const_iterator	lower_bound(const Key& key) const
			{
				const_iterator it = begin();
				while (it != end())
				{
					if (!_comp(it->first, key))
						return it;
					it++;
				}
				return end();
			};

			iterator	upper_bound(const Key& key)
			{
				iterator it = begin();
				while (it != end())
				{
					if (_comp(key, it->first))
						return it;
					it++;
				}
				return end();
			};

			const_iterator	upper_bound(const Key& key) const
			{
				const_iterator it = begin();
				while (it != end())
				{
					if (_comp(key, it->first))
						return it;
					it++;
				}
				return end();
			};

			Compare	key_comp() const
			{
				return _comp;
			};

			value_compare	value_comp() const
			{
				return value_compare(key_compare());
			};

		private:
			//TREE INTERNALS
			void	clearTree(mapNode* node)
			{
				if (node == NULL)
					return ;
				if (node->left && node->left != _rend)
					clearTree(node->left);
				if (node->right && node->right != _end)
					clearTree(node->right);
				_nodeAlloc.destroy(node);
				_nodeAlloc.deallocate(node, 1);
				node = NULL;
			}

			void	linkParentToChild(mapNode* node)
			{
				if (node == _tree)
				{
					if (node->left && node->left != _rend)
					{
						_tree = node->left;
						_tree->parent = NULL;
						if (node->left != _rend)
						{
							mapNode*	max = _tree->findMax();
							max->right = _end;
							_end->parent = max;
						}
					}
					else if (node->right && node->right != _end)
					{
						_tree = node->right;
						_tree->parent = NULL;
						if (node->left == _rend)
						{
							mapNode*	min = _tree->findMin();
							min->left = _rend;
							_rend->parent = min;
						}
					}
				}
				else if (node->parent && node->parent->left == node)
				{
					if (node->left && node->left != _rend)
					{
						node->parent->left = node->left;
						node->left->parent = node->parent;
						if (node->right == _end)
						{
							mapNode*	max = node->left->findMax();
							max->right = _end;
							_end->parent = max;
						}
					}
					else if (node->right && node->right != _end)
					{
						node->parent->left = node->right;
						node->right->parent = node->parent;
						if (node->left == _rend)
						{
							mapNode*	min = node->right->findMin();
							min->left = _rend;
							_rend->parent = min;
						}
					}
				}
				else if (node->parent && node->parent->right == node)
				{
					if (node->left && node->left != _rend)
					{
						node->parent->right = node->left;
						node->left->parent = node->parent;
						if (node->right == _end)
							node->left->findMax()->right = _end;
					}
					else if (node->right && node->right != _end)
					{
						node->parent->right = node->right;
						node->right->parent = node->parent;
						if (node->left == _rend)
							node->right->findMin()->left = _rend;
					}
				}
			};

			void	unlinkParent(mapNode* node)
			{
				if (node->parent && node->parent->left == node)
				{
					if (node->left == _rend)
					{
						_rend->parent = node->parent;
						node->parent->left = _rend;
					}
					else
						node->parent->left = NULL;
				}
				else if (node->parent && node->parent->right == node)
				{
					if (node->right == _end)
					{
						_end->parent = node->parent;
						node->parent->right = _end;
					}
					else
						node->parent->right = NULL;
				}
			};

			bool	hasOneChild(mapNode* node)
			{
				if (node->left && node->left != _rend && node->right && node->right != _end)
					return false;
				if (node->left && node->left != _rend)
					return true;
				if (node->right && node->right != _end)
					return true;
				return false;
			};

			bool	isLeaf(mapNode* node)
			{
				if ((node->left && node->left != _rend) || (node->right && node->right != _end))
					return false;
				return true;
			};

			mapNode*	findNode(const key_type& key, mapNode* node) const
			{
				if (!node)
					return NULL;
				if (node->value.first == key)
					return node;
				if (_comp(key, node->value.first))
				{
					if (node->left == NULL || node->left == _rend)
						return node;
					else
						return findNode(key, node->left);
				}
				else
				{
					if (node->right == NULL || node->right == _end)
						return node;
					else
						return findNode(key, node->right);
				}
			};

			mapNode*	getNode(const key_type& key) const
			{
				if (!_tree)
					return _end;
				mapNode* result = findNode(key, _tree);

				if (result->value.first != key)
					return _end;
				return result;
			};

			mapNode*	treeMin() const
			{
				if (!_tree)
					return NULL;
				return _tree->findMin();
			};

			mapNode*	treeMax() const
			{
				if (!_tree)
					return NULL;
				return _tree->findMax();
			};
	};

	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;

		typename ft::map<Key,T,Compare,Alloc>::const_iterator lhsit = lhs.begin();
		typename ft::map<Key,T,Compare,Alloc>::const_iterator rhsit = rhs.begin();
		while (lhsit != lhs.end() && rhsit != rhs.end())
		{
			if (*lhsit != *rhsit)
				return false;
			lhsit++;
			rhsit++;
		}
		return true;
	};

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
	{
		return !(lhs == rhs);
	};

	template<class Key, class T, class Compare, class Alloc>
	bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
	{
		return lhs == rhs || lhs < rhs;
	};

	template<class Key, class T, class Compare, class Alloc>
	bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
	{
		return !(lhs <= rhs);
	};

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
	{
		return !(lhs < rhs);
	};

	template<class Key, class T, class Compare, class Alloc>
	void	swap(ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}

}
#endif
