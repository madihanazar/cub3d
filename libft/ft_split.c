/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:24:15 by mnazar            #+#    #+#             */
/*   Updated: 2024/10/03 19:38:46 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**malloc_free(char **array, int position)
{
	int	i;

	i = 0;
	while (i < position)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static int	ft_word_count(const char *s, char sep)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] != sep && (s[i + 1] == sep || s[i + 1] == '\0'))
			word++;
		i++;
	}
	return (word);
}

static char	*ft_get_word(const char *s, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc(sizeof(char) * ((end - start + 1) + 1));
	if (!word)
	{
		return (NULL);
	}
	while (start <= end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

char	**get_array(const char *s, char c, size_t i, int j)
{
	char	**ptr;
	int		k;

	ptr = (char **)malloc(sizeof(char *) * (ft_word_count(s, c) + 1));
	if (!ptr)
		return (NULL);
	k = 0;
	while (i <= (size_t) ft_strlen(s))
	{
		j = i;
		while (s[i] && s[i] != c)
		{
			if (s[++i] == c || s[i] == '\0')
			{
				ptr[k++] = ft_get_word(s, j, i - 1);
				if (!(ptr[k - 1]))
					return (malloc_free(ptr, k - 1));
			}
		}
		if (s[i++] == '\0')
			break ;
	}
	ptr[k] = NULL;
	return (ptr);
}

char	**ft_split(const char *s, char c)
{
	char	**ptr;

	if (!s)
		return (NULL);
	ptr = get_array(s, c, 0, 0);
	return (ptr);
}
// static int	count_words(const char *s, char c)
// {
// 	int	words;
// 	int	flag;

// 	words = 0;
// 	flag = 0;
// 	while (*s)
// 	{
// 		if (*s != c && flag == 0)
// 		{
// 			flag = 1;
// 			words++;
// 		}
// 		else if (*s == c)
// 			flag = 0;
// 		s++;
// 	}
// 	return (words);
// }

// static char	*word_dup(const char *s, int start, int end)
// {
// 	char	*word;
// 	int		i;

// 	i = 0;
// 	word = malloc((end - start + 1) * sizeof(char));
// 	if (!word)
// 	{
// 		return (NULL);
// 	}
// 	while (start < end)
// 	{
// 		word[i++] = s[start++];
// 	}
// 	word[i] = '\0';
// 	return (word);
// }

// static char	**free_array(char **arr, size_t k)
// {
// 	while (k-- > 0)
// 	{
// 		free(arr[k]);
// 		arr[k] = NULL;
// 	}
// 	free(arr);
// 	arr = NULL;
// 	return (NULL);
// }

// static char	**result_array(size_t size, char **res_arr, char const *s, char c)
// {
// 	size_t	i;
// 	size_t	start;
// 	size_t	end;

// 	i = 0;
// 	start = 0;
// 	end = 0;
// 	while (i < size)
// 	{
// 		while (s[start] == c)
// 			start++;
// 		end = start;
// 		while (s[end] && s[end] != c)
// 			end++;
// 		res_arr[i] = word_dup(s, start, end);
// 		if (!res_arr[i])
// 			return (free_array(res_arr, i));
// 		start = end;
// 		i++;
// 	}
// 	res_arr[i] = NULL;
// 	return (res_arr);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char		**result;
// 	size_t		size;

// 	size = count_words(s, c);
// 	if (!s)
// 		return (NULL);
// 	result = (char **)malloc(sizeof(char *) * (size + 1));
// 	if (!result)
// 		return (NULL);
// 	result = result_array(size, result, s, c);
// 	if (!result)
// 		return (NULL);
// 	return (result);
// }
