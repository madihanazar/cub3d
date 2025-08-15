/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:27:05 by mnazar            #+#    #+#             */
/*   Updated: 2024/07/04 18:59:04 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;
	int		k;

	k = -1;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
		{
			k = i;
		}
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(str + i));
	if (k == -1)
		return (NULL);
	return ((char *)(str + k));
}
