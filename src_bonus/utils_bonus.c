/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 20:02:17 by skharjo           #+#    #+#             */
/*   Updated: 2021/10/17 20:03:50 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

char	*ft_strdup(const char *str)
{
	char	*strdup;
	int		i;

	i = 0;
	strdup = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (strdup && str)
	{
		while (*str)
		{
			*strdup++ = *str++;
			i++;
		}
		*strdup = '\0';
	}
	else
		return (NULL);
	return (strdup - i);
}

void	close_all_fd(int *pipefd, int fd1, int fd2)
{
	if (pipefd[0] >= 0)
		close(pipefd[0]);
	if (pipefd[1] >= 0)
		close(pipefd[1]);
	if (fd1 >= 0)
		close(fd1);
	if (fd2 >= 0)
		close(fd2);
}

void	call_msh_error(char *str1, char *str2)
{
	msh_strerror_arg_2(str1, str2);
	exit(EXIT_FAILURE);
}
