/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:07:22 by mnazar            #+#    #+#             */
/*   Updated: 2024/07/04 18:57:44 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t num)
{
	unsigned char	*tempd;
	unsigned char	*temps;

	if (!destination && !source)
		return (destination);
	tempd = (unsigned char *)destination;
	temps = (unsigned char *)source;
	while (num > 0)
	{
		*(tempd++) = *(temps++);
		num--;
	}
	return (destination);
}
