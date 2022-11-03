/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:29:37 by smagdela          #+#    #+#             */
/*   Updated: 2022/11/03 15:36:35 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.hpp"

static int	ft_div(size_t nbr)
{
	int	count;

	count = 1;
	if (nbr == 0)
		return (2);
	while (nbr)
	{
		nbr /= 10;
		++count;
	}
	return (count);
}

char	*ft_utoa(size_t	nbr)
{
	size_t	nb;
	int		value;
	char	*ret;

	nb = nbr;
	value = ft_div(nb);
	ret = (char *)malloc(sizeof(char) * value);
	if (!ret)
		return (NULL);
	if (nb == 0)
		ret[0] = 48;
	--value;
	ret[value] = '\0';
	while (nb)
	{
		ret[value - 1] = (nb % 10) + 48;
		nb = nb / 10;
		--value;
	}
	return (ret);
}
