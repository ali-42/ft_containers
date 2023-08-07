/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:03:09 by ali               #+#    #+#             */
/*   Updated: 2022/09/06 14:18:52 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WARLOCK_HPP
# define WARLOCK_HPP

#include <iostream>

class Warlock
{
	public:
		const std::string&	getName() const;
		const std::string&	getTitle() const;

		void	setTitle(const std::string&	aTitle);

		Warlock(const std::string& aName, const std::string& aTitle);
		~Warlock();

		void	introduce() const;

	private:
		std::string	name;
		std::string	title;

		Warlock&	operator=(const Warlock& aWarlock);

		Warlock();
		Warlock(const Warlock& aWarlock);
};

#endif
