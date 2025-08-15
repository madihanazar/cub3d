/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:29:34 by mnazar            #+#    #+#             */
/*   Updated: 2024/07/04 18:58:25 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ans;
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	ans = (char *)malloc(i + 1 * sizeof(char));
	if (ans == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		ans[i] = s[i];
		i++;
	}
	ans[i] = '\0';
	return (ans);
}
