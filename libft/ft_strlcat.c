/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:17:08 by mnazar            #+#    #+#             */
/*   Updated: 2024/07/04 18:58:36 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	const char	*s;
	char		*d;
	size_t		destlen;
	size_t		srclen;
	size_t		i;

	d = dest;
	s = src;
	i = 0;
	destlen = 0;
	srclen = 0;
	while (d[destlen] != '\0')
		destlen++;
	while (s[srclen] != '\0')
		srclen++;
	if (size <= destlen)
		return (size + srclen);
	while (destlen + i < (size - 1) && s[i] != '\0')
	{
		d[destlen + i] = s[i];
		i++;
	}
	d[destlen + i] = '\0';
	return (destlen + srclen);
}
