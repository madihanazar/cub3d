/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:12:12 by mnazar            #+#    #+#             */
/*   Updated: 2024/07/04 18:57:02 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_cal_number_digits(int n)
{
	size_t	res;

	res = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		res++;
		n = n * -1;
	}
	while (n != 0)
	{
		n /= 10;
		res++;
	}
	return (res);
}

char	*set_res(size_t num_digits)
{
	char	*res;

	res = (char *)malloc((num_digits + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	return (res);
}

char	*ft_itoa(int num)
{
	char	*res;
	size_t	num_digits;
	long	n;

	n = num;
	num_digits = ft_cal_number_digits(n);
	res = set_res(num_digits);
	if (!res)
		return (NULL);
	res[num_digits] = '\0';
	if (n == 0)
		res[0] = 48;
	if (n < 0)
	{
		res[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		res[--num_digits] = (n % 10) + '0';
		n = n / 10;
	}
	return (res);
}
