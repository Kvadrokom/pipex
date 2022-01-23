/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skharjo <skharjo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:53:11 by skharjo           #+#    #+#             */
/*   Updated: 2021/10/13 18:11:53 by skharjo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	msh_strerror_arg_2(char *arg_1, char *arg_2)
{
	ft_putstr_fd(arg_1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg_2, 2);
	ft_putstr_fd("\n", 2);
	errno = 0;
}

void	fatal(int res)
{
	write(2, "Error: fatal\n", ft_strlen("Error: fatal\n"));
	exit(res);
}
