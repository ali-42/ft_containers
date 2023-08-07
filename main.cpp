/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:22:21 by ali               #+#    #+#             */
/*   Updated: 2022/07/18 11:58:20 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <fstream>
#include <iostream>

int main()
{
	std::cout << "FT containers" << std::endl;
	std::system("time ./ft > resultFT");

	std::cout << std::endl << std::endl;

	std::cout << "STL containers" << std::endl;
	std::system("time ./stl > resultSTL");

	std::cout << std::endl << std::endl;

	std::cout << "output differences" << std::endl << std::endl;
	std::system("diff resultFT resultSTL");
}
