/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATarget.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:50:59 by ali               #+#    #+#             */
/*   Updated: 2022/09/06 15:07:28 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATARGET_HPP
# define ATARGET_HPP

# include <iostream>

class ATarget
{
	protected:
		std::string	type;

	public:
		const std::string& getType() const;

		virtual ATarget*	clone() = 0 const;

		ATarget(const std::string& aType);

		ATarget();
		ATarget(const ATarget& aATarget);

		virtual ~ATarget();

		ATarget&	operator=(const ATarget& aATarget);

		void	getHitBySpell(const ASpell& spell);
};

#endif
