/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASpell.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:26:09 by ali               #+#    #+#             */
/*   Updated: 2022/09/06 15:07:21 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASPELL_HPP
# define ASPELL_HPP

#include <iostream>

class ASpell
{
	protected:
		std::string	name;
		std::string	effects;

	public:
		const std::string& getName() const;
		const std::string& getEffects() const;

		virtual ASpell*	clone() = 0 const;

		ASpell(const std::string& aName, const std::string& aEffects);
		
		ASpell();
		ASpell(const ASpell& aASpell);

		virtual ~ASpell();

		ASpell&	operator=(const ASpell& aASpell);

		void	launch(const ATarget& target);
};

#endif
