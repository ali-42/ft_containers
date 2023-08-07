/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 12:53:25 by ali               #+#    #+#             */
/*   Updated: 2022/09/07 18:53:01 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <ctime>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <iostream>

template<class T>
void	print_vector(const std::vector<T>& v)
{
	std::cout << "size = " << v.size() << std::endl;
	for (typename std::vector<T>::const_iterator ftit = v.begin(); ftit != v.end(); ftit++)
		std::cout << *ftit << std::endl;
}

template<class T>
void	print_elem(const T& elem)
{
	std::cout << elem << std::endl;
}

template<class Container>
void	print_comparisons(const Container& v, const Container& vcpy)
{
			if (v == vcpy)
				std::cout << "equal" << std::endl;
			if (v != vcpy)
				std::cout << "inequal" << std::endl;
			
			if (v < vcpy)
				std::cout << "less" << std::endl;
			if (v >= vcpy)
				std::cout << "greater or equal" << std::endl;

			if (v > vcpy)
				std::cout << "greater" << std::endl;
			if (v <= vcpy)
				std::cout << "less or equal" << std::endl;
}

template<class T>
void	print_stack(std::stack<T>& s)
{
	if (s.empty())
		return ;
	T tmp = s.top();
	s.pop();
	print_stack(s);
	std::cout << tmp << std::endl;
	s.push(tmp);
}

template<class Key, class T>
void	print_map(const std::map<Key, T>& m)
{
	std::cout << "size = " << m.size() << std::endl;
	for (typename std::map<Key, T>::const_iterator it = m.begin(); it != m.end(); it++)
		std::cout << it->first << " : " << it->second << std::endl;
}

template<class Key, class T>
void	print_mapElem(const std::pair<Key, T>& elem)
{
	std::cout << elem.first << " : " << elem.second << std::endl;
}

int	main(void)
{
	{
		std::cout << "*** VECTOR ***" << std::endl << std::endl;

		std::cout << "CONSTRUCTORS" << std::endl << std::endl;
		{	
			std::cout << "default constructor" << std::endl;
			std::vector<int> v;

			print_vector(v);
		}

		{	
			std::cout << std::endl << "construtor by allocator" << std::endl;
			std::allocator<int> alloc;
			std::vector<int> v(alloc);

			print_vector(v);
		}

		{	
			std::cout << std::endl << "construtor by size and value" << std::endl;
			std::vector<int> v(6, 42);

			print_vector(v);
		}

		{	
			std::cout << std::endl << "construtor by size only" << std::endl;
			std::vector<int> v(4);

			print_vector(v);
		}

		{
			std::cout << std::endl << "construtor with an iterator range" << std::endl;
			std::vector<int> base;
			base.push_back(1);
			base.push_back(42);
			base.push_back(84);
			std::vector<int>::iterator baseBegin = base.begin();
			std::vector<int>::iterator baseEnd = base.end();

			std::vector<int> v(baseBegin, baseEnd);

			print_vector(v);
		}

		{
			std::cout << std::endl << "copy constructor" << std::endl;
			std::vector<int> base;
			base.push_back(1);
			base.push_back(42);
			base.push_back(84);

			std::vector<int> v(base);

			print_vector(v);
		}

		std::cout << std::endl << "ASSIGNMENT" << std::endl << std::endl;

		{
			std::cout << "= operator" << std::endl;
			std::vector<int> base;	
			base.push_back(1);
			base.push_back(42);
			base.push_back(84);

			std::vector<int> v = base;

			print_vector(v);
		}

		{
			std::cout << std::endl << "assign() by size and value" << std::endl;
			std::vector<int> v;

			v.assign(6, 42);

			print_vector(v);
		}

		{
			std::cout << std::endl << "assign by iterator range" << std::endl;
			std::vector<int> v;

			std::vector<int> base;
			base.push_back(1);
			base.push_back(42);
			base.push_back(84);
			std::vector<int>::iterator baseBegin = base.begin();
			std::vector<int>::iterator baseEnd = base.end();

			v.assign(baseBegin, baseEnd);

			print_vector(v);
		}

		std::cout << std::endl << "ELEMENT ACCESS" << std::endl << std::endl;

		{
			std::cout << "at() (out of bounds)" << std::endl;

			std::vector<int> v;
			v.push_back(1);
			v.push_back(42);
			v.push_back(84);

			try
			{
				std::cout << v.at(3) << std::endl;
			}
			catch (std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}

			std::cout <<std::endl <<"at() (inside bounds)" << std::endl;

			try
			{
				std::cout << v.at(2) << std::endl;
			}
			catch (std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}

			std::cout << std::endl << "[] operator" << std::endl;
			print_elem(v[2]);

			std::cout << std::endl << "front()" << std::endl;
			print_elem(v.front());

			std::cout << std::endl << "back()" << std::endl;
			print_elem(v.back());

			std::cout << std::endl << "data()" << std::endl;
			print_elem(*v.data());
		}
	
		std::cout << std::endl << "ITERATORS" << std::endl << std::endl;

		{
			std::vector<int> v;
			v.push_back(1);
			v.push_back(42);
			v.push_back(84);

			std::cout << "begin()" << std::endl;
			print_elem(*v.begin());

			std::cout << std::endl << "end() - 1" << std::endl;
			print_elem(*(v.end() - 1));

			std::cout << std::endl << "rbegin()" << std::endl;
			print_elem(*v.rbegin());

			std::cout << std::endl << "rend() - 1" << std::endl;
			print_elem(*(v.rend() - 1));
		}

		std::cout << std::endl << "CAPACITY" << std::endl << std::endl;

		{
			std::cout << "empty() before and after" << std::endl;
		
			std::vector<int> v;

			std::cout << v.empty() << std::endl;
			v.push_back(1);
			std::cout << v.empty() << std::endl;

			std::cout << std::endl << "size()" << std::endl;

			std::cout << v.size() << std::endl;
			v.push_back(42);
			v.push_back(84);
			std::cout << v.size() << std::endl;

			std::cout << std::endl << "max_size()" << std::endl;
			print_elem(v.max_size());

			std::cout << std::endl << "capacity()" << std::endl;
			print_elem(v.capacity());

			std::cout << std::endl << "reserve()" << std::endl;
			v.reserve(100);
			print_elem(v.capacity());
		}

		std::cout << std::endl << "MODIFIERS" << std::endl << std::endl;

		{
			std::vector<int> v;
			v.push_back(1);
			v.push_back(42);
			v.push_back(84);

			std::cout << "clear() before and after" << std::endl;
			print_vector(v);
			v.clear();
			print_vector(v);

			std::cout << std::endl << "insert() single value" << std::endl;
			v.push_back(1);
			v.push_back(42);
			v.push_back(84);

			v.insert(v.begin() + 2, 63);
			print_vector(v);

			std::cout << std::endl << "insert() multiple values" << std::endl;
			v.insert(v.begin() + 1, 3, 21);
			print_vector(v);

			std::cout << std::endl << "insert() iterator range" << std::endl;

			std::vector<int> base;
			base.push_back(2);
			base.push_back(3);
			base.push_back(4);

			v.insert(v.begin() + 1, base.begin(), base.end());
			print_vector(v);

			std::cout << std::endl << "erase() position" << std::endl;
			v.erase(v.begin() + 4);
			print_vector(v);

			std::cout << std::endl << "erase() iterator range" << std::endl;
			v.erase(v.begin() + 1, v.begin() + 5);
			print_vector(v);

			std::cout << std::endl << "push_back()" << std::endl;
			v.push_back(105);
			print_vector(v);

			std::cout << std::endl << "pop_back()" << std::endl;
			v.pop_back();
			print_vector(v);

			std::cout << std::endl << "resize() up" << std::endl;
			v.resize(7, 24);
			print_vector(v);

			std::cout << std::endl << "resize() down" << std::endl;
			v.resize(3);
			print_vector(v);

			std::cout << std::endl << "swap() method" << std::endl;

			std::vector<int> vcopy(v);
			vcopy.insert(vcopy.begin() + 2, 37);

			v.swap(vcopy);
			print_vector(v);

			std::cout << std::endl << "swap() non-method" << std::endl;
			std::swap(v, vcopy);
			print_vector(v);
		}

		std::cout << std::endl << "COMPARISONS" << std::endl << std::endl;
		{
			std::vector<std::string> v;
			v.push_back("bla");
			v.push_back("bli");
			v.push_back("blu");

			std::cout << "* copies *" << std::endl;
			std::vector<std::string> vcpy(v);
			print_comparisons(v, vcpy);

			std::cout << std::endl << "* greater in size *" << std::endl;
			v.push_back("blo");
			print_comparisons(v, vcpy);

			std::cout << std::endl << "* smaller in size *" << std::endl;
			v.pop_back();
			v.pop_back();
			print_comparisons(v, vcpy);

			std::cout << std::endl << "* same size but different values *" << std::endl;
			v.push_back("blo");
			print_comparisons(v, vcpy);

		}
	}


	{
		std::cout << std::endl << "*** STACK ***" << std::endl << std::endl;

		std::cout << "CONSTRUCTORS" << std::endl;

		{
			std::cout << std::endl << "default constructor" << std::endl;

			std::deque<std::string> v;
			v.push_back("bla");
			v.push_back("bli");
			v.push_back("blu");

			std::stack<std::string> s(v);
			print_stack(s);

			std::cout << std::endl << "copy constructor" << std::endl;

			std::stack<std::string> cpy(s);
			print_stack(cpy);
		}

		std::cout << std::endl << "ASSIGNMENT" << std::endl;

		{
			std::cout << std::endl << "= operator" << std::endl;
			std::stack<int> s;
			s.push(1);
			s.push(42);
			s.push(84);

			std::stack<int> other = s;
			print_stack(other);
		}

		std::cout << std::endl << "ACCESS" << std::endl;

		{
			std::cout << std::endl << "top()" << std::endl;
			std::stack<int> s;
			s.push(1);
			s.push(42);
			s.push(84);

			std::cout << s.top() << std::endl;
		}

		std::cout << std::endl << "CAPACITY" << std::endl;

		{
			std::cout << std::endl << "empty() before and after push()" << std::endl;

			std::stack<int> s;
			std::cout << s.empty() << std::endl;
			s.push(1);
			std::cout << s.empty() << std::endl;

			std::cout << std::endl << "size()" << std::endl;
			s.push(42);
			s.push(84);
			std::cout << s.size() << std::endl;
		}

		std::cout << std::endl << "MODIFIERS" << std::endl;

		{
			std::cout << std::endl << "push() before and after" << std::endl;

			std::stack<int> s;
			s.push(1);
			s.push(42);
			print_stack(s);
			std::cout << std::endl;
			s.push(84);
			print_stack(s);
			
			std::cout << std::endl << "pop()" << std::endl;
			s.pop();
			print_stack(s);
		}

		std::cout << std::endl << "COMPARISONS" << std::endl << std::endl;

		{
			std::stack<std::string> s;
			s.push("bla");
			s.push("bli");
			s.push("blu");

			std::cout << "* copies *" << std::endl;
			std::stack<std::string> scpy(s);
			print_comparisons(s, scpy);

			std::cout << std::endl << "* greater in size *" << std::endl;
			s.push("blo");
			print_comparisons(s, scpy);

			std::cout << std::endl << "* smaller in size *" << std::endl;
			s.pop();
			s.pop();
			print_comparisons(s, scpy);

			std::cout << std::endl << "* same size but different values *" << std::endl;
			s.push("blo");
			print_comparisons(s, scpy);
		}
	}

	
	std::cout << std::endl << "*** MAP ***" << std::endl << std::endl;


	std::cout << "CONSTRUCTORS" << std::endl << std::endl;

	{
		std::cout << "default constructor" << std::endl;

		std::map<int, std::string> m;
		print_map(m);
	}

	{
		std::cout << std::endl << "iterator range constructor" << std::endl;

		std::vector<std::pair<int, std::string> > v;
		v.push_back(std::make_pair(0, "bla"));
		v.push_back(std::make_pair(-21, "blu"));
		v.push_back(std::make_pair(42, "bli"));
		v.push_back(std::make_pair(21, "blo"));

		std::map<int, std::string> m(v.begin(), v.end());
		print_map(m);

		std::cout << std::endl << "copy constructor" << std::endl;

		std::map<int, std::string> mcpy(m);
		print_map(mcpy);
	}

	std::cout << std::endl << "ASSIGNMENT" << std::endl;

	{
		std::cout << std::endl << "= operator" << std::endl;

		std::vector<std::pair<int, std::string> > v;
		v.push_back(std::make_pair(0, "bla"));
		v.push_back(std::make_pair(-21, "blu"));
		v.push_back(std::make_pair(42, "bli"));
		v.push_back(std::make_pair(21, "blo"));

		std::map<int, std::string> m(v.begin(), v.end());
		std::map<int, std::string> mcpy = m;
		print_map(mcpy);
	}

	std::cout << std::endl << "ELEMENT ACCESS" << std::endl;

	{
		std::cout << std::endl << "at() out of range" << std::endl;

		std::vector<std::pair<int, std::string> > v;
		v.push_back(std::make_pair(0, "bla"));
		v.push_back(std::make_pair(-21, "blu"));
		v.push_back(std::make_pair(42, "bli"));
		v.push_back(std::make_pair(21, "blo"));

		std::map<int, std::string> m(v.begin(), v.end());
		try 
		{
			std::cout << m.at(32) << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}

		std::cout << std::endl << "at() in range" << std::endl;

		try 
		{
			std::cout << m.at(21) << std::endl;
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}

		std::cout << std::endl << "[] operator" << std::endl;

		std::cout << m[21] << std::endl;
	}

	std::cout << std::endl << "ITERATORS" << std::endl;

	{
		std::vector<std::pair<int, std::string> > v;
		v.push_back(std::make_pair(0, "bla"));
		v.push_back(std::make_pair(-21, "blu"));
		v.push_back(std::make_pair(42, "bli"));
		v.push_back(std::make_pair(21, "blo"));

		std::map<int, std::string> m(v.begin(), v.end());

		std::cout << std::endl << "begin()" << std::endl;
		std::map<int, std::string>::iterator it = m.begin();
		print_mapElem(*it);

		std::cout << std::endl << "--end()" << std::endl;
		std::map<int, std::string>::iterator ite = m.end();
		print_mapElem(*(--ite));

		std::cout << std::endl << "rbegin()" << std::endl;
		std::map<int, std::string>::reverse_iterator itr = m.rbegin();
		print_mapElem(*itr);

		std::cout << std::endl << "--rend()" << std::endl;
		std::map<int, std::string>::reverse_iterator iter= m.rend();
		print_mapElem(*(--iter));
	}

	std::cout << std::endl << "CAPACITY" << std::endl;

	{
		std::cout << std::endl << "empty() before and after insertion" << std::endl;
		std::map<int, std::string> m;
		std::cout << m.empty() << std::endl;

		m.insert(std::make_pair(0, "first"));
		std::cout << m.empty() << std::endl;

		std::cout << std::endl << "size() before and after insertion" << std::endl;

		std::cout << m.size() << std::endl;

		m.insert(std::make_pair(1, "second"));
		m.insert(std::make_pair(2, "third"));
		std::cout << m.size() << std::endl;
	}

	std::cout << std::endl << "MODIFIERS" << std::endl;

	{
		std::cout << std::endl << "insert() by value (before and after)" << std::endl;

		std::map<int, std::string> m;
		m.insert(std::make_pair(0, "blu"));
		m.insert(std::make_pair(1, "bli"));
		print_map(m);

		m.insert(std::make_pair(-1, "blo"));
		m.insert(std::make_pair(2, "bla"));
		print_map(m);

		std::cout << std::endl << "insert() by value (before and after)" << std::endl;

		m.insert(--m.end(), std::make_pair(3, "ble"));
		m.insert(m.begin(), std::make_pair(-2, "bly"));
		print_map(m);

		std::cout << std::endl << "clear()" << std::endl;
		m.clear();
		print_map(m);

		std::cout << std::endl << "insert() by iterator range" << std::endl;
		std::vector<std::pair<int, std::string> > v;
		v.push_back(std::make_pair(0, "blu"));
		v.push_back(std::make_pair(1, "bli"));
		v.push_back(std::make_pair(-1, "blo"));
		v.push_back(std::make_pair(2, "bla"));

		m.insert(v.begin(), v.end());
		print_map(m);

		std::cout << std::endl << "insert() fail (already used keys)" << std::endl;
		
		m.insert(v.begin(), v.end());
		print_map(m);

		std::cout << std::endl << "erase() with iterator" << std::endl;

		m.erase(--m.end());
		m.erase(++m.begin());
		print_map(m);

		std::cout << std::endl << "erase() with key (fail)" << std::endl;

		m.erase(2);
		print_map(m);

		std::cout << std::endl << "erase() with key (success)" << std::endl;

		m.erase(-1);
		print_map(m);

		std::cout << std::endl << "erase() last node" << std::endl;

		m.erase(1);
		print_map(m);
	}
	
	{
		std::cout << std::endl << "swap()" << std::endl;

		std::map<std::string, int> a;
		a.insert(std::make_pair("A", 12445));
		a.insert(std::make_pair("Stupid Key", -111));
		a.insert(std::make_pair("qwerty", 42));

		std::map<std::string, int> b;
		b.insert(std::make_pair("dududu", 33));
		b.insert(std::make_pair("wawawaw", -122));
		b.insert(std::make_pair("0_0", 12314));

		std::cout << "*** before swap ***" << std::endl << std::endl;
		std::cout << "a" << std::endl;
		print_map(a);
		std::cout << std::endl << "b" << std::endl;	
		print_map(b);

		a.swap(b);

		std::cout << std::endl << "*** after swap ***" << std::endl << std::endl;
		std::cout << "a" << std::endl;
		print_map(a);
		std::cout << std::endl << "b" << std::endl;	
		print_map(b);
	}

	std::cout << std::endl << "LOOKUP" << std::endl;

	{
		std::cout << std::endl << "count()" << std::endl;

		std::map<std::string, int> m;
		m.insert(std::make_pair("Key0", 0));
		m.insert(std::make_pair("Key1", 1));
		m.insert(std::make_pair("Key2", 2));
		m.insert(std::make_pair("Key3", 3));

		std::cout << m.count("Key2") << std::endl;
		std::cout << m.count("Key4") << std::endl;

		std::cout << std::endl << "find()" << std::endl;

		for (std::map<std::string, int>::iterator it = m.find("Key2"); it != m.end(); it++)
			std::cout << it->second << std::endl;

		std::cout << std::endl << "lower_bound()" << std::endl;

		std::cout << m.lower_bound("Key2")->first << std::endl;

		std::cout << std::endl << "upper_bound()" << std::endl;

		std::cout << m.upper_bound("Key2")->first << std::endl;

		std::cout << std::endl << "equal_range()" << std::endl;
		
		std::map<std::string, int>::iterator it = m.equal_range("Key1").first;
		std::map<std::string, int>::iterator it2 = m.equal_range("Key1").second;
		std::cout << it->first << " : " << it->second << std::endl;
		std::cout << it2->first << " : " << it2->second << std::endl;
	}

	std::cout << std::endl << "OBSERVERS" << std::endl;

	{
		std::cout << std::endl << "key_comp()" << std::endl;

		std::map<std::string, int> m;
		std::cout << m.key_comp()("arbre", "bateau") << std::endl;
		std::cout << m.key_comp()("bateau", "arbre") << std::endl;

		std::cout << std::endl << "value_comp()" << std::endl;

		std::cout << m.value_comp()(std::make_pair("arbre", 29), std::make_pair("bateau", 42)) << std::endl;
		std::cout << m.value_comp()(std::make_pair("bateau", 42), std::make_pair("arbre", 29)) << std::endl;
	}

	std::cout << std::endl << "COMPARISONS" << std::endl;
	
	{
		std::map<int, std::string> m;

		m.insert(std::make_pair(42, "blu"));
		m.insert(std::make_pair(21, "blo"));
		m.insert(std::make_pair(84, "bla"));

		std::map<int, std::string> m2(m);

		std::cout << "* copies *" << std::endl;
		print_comparisons(m, m2);

		std::cout << std::endl << "* greater in size *" << std::endl;
		m.insert(std::make_pair(100, "bli"));
		print_comparisons(m, m2);

		std::cout << std::endl << "* smaller in size *" << std::endl;
		m.erase(84);
		m.erase(100);
		print_comparisons(m, m2);

		std::cout << std::endl << "* different keys *" << std::endl;
		m.insert(std::make_pair(72, "bla"));
		print_comparisons(m, m2);

		std::cout << std::endl << "* different values *" << std::endl;
		m.erase(72);
		m.insert(std::make_pair(84, "bli"));
		print_comparisons(m, m2);
	}

	std::cout << std::endl << "PERFORMANCE" << std::endl;

	{
		std::vector<int> v;
		std::stack<int> s;
		std::map<int, int> m;
		srand((unsigned)time(0));
		for (int i = 0; i < 100000; i++)
		{
			v.push_back(rand()%1000000);
			s.push(rand()%1000000);
			m.insert(std::make_pair(rand()%1000000, rand()%1000000));
		}
		for (int i = 0; i < 100000; i++)
			m.find(rand()%1000000);
		
		std::map<int, int> m2;
		for (int i = 0; i < 100000; i++)
			m.insert(std::make_pair(i, i));
		for (int i = 0; i < 100000; i++)
			m.find(i);
	}
}
