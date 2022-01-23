/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 20:02:17 by skharjo           #+#    #+#             */
/*   Updated: 2021/10/12 19:26:27 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	if (n == 0)
		return (0);
	while (*str1 && *str2 && n)
	{
		if (*str1 != *str2)
			return ((unsigned char)*str1 - (unsigned char)*str2);
		n--;
		str1++;
		str2++;
	}
	if (n == 0)
		return ((unsigned char)*(--str1) - (unsigned char)*(--str2));
	else
		return ((unsigned char)*(str1) - (unsigned char)*(str2));
}

char	**str_array_free(char **str_array[])
{
	int	i;

	if (!*str_array)
		return (NULL);
	i = 0;
	while ((*str_array)[i])
	{
		free((*str_array)[i]);
		i++;
	}
	free(*str_array);
	*str_array = NULL;
	return (NULL);
}
