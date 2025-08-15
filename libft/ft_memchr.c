/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:41:22 by mnazar            #+#    #+#             */
/*   Updated: 2024/07/04 18:57:31 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	ch;
	unsigned char	*s;
	size_t			i;

	i = 0;
	s = (unsigned char *)str;
	ch = (unsigned char)c;
	while (i < n)
	{
		if (*s == ch)
		{
			return (s);
		}
		i++;
		s++;
	}
	return (NULL);
}
