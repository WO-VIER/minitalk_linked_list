/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:33:06 by vwautier          #+#    #+#             */
/*   Updated: 2025/04/11 18:07:30 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	error_exit(void)
{
	write(2, "Error: Invalid PID\n", 19);
	exit(EXIT_FAILURE);
}

int	ft_pidtoi(const char *string)
{
	long	number;
	int		i;

	i = 0;
	number = 0;
	if (string[i] == '\0')
		error_exit();
	while (string[i])
	{
		if (!(string[i] >= '0' && string[i] <= '9'))
			error_exit();
		i++;
	}
	i = 0;
	while (string[i] >= '0' && string[i] <= '9')
	{
		number = (number * 10) + (string[i++] - '0');
		if (number > INT_MAX)
			error_exit();
	}
	return ((int)number);
}
