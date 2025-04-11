/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:56:31 by vwautier          #+#    #+#             */
/*   Updated: 2024/12/06 12:23:09 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str, char format)
{
	int	nbytes;
	int	tmp;

	nbytes = 0;
	if (format == 'c')
		return (ft_putchar(str[0]));
	while (str[nbytes])
	{
		tmp = ft_putchar(str[nbytes]);
		if (tmp == -1)
			return (-1);
		nbytes++;
	}
	return (nbytes);
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	size_nombre(long long nb)
{
	int	size;

	size = 1;
	if (nb < 0)
	{
		nb = -nb;
		size++;
	}
	while (nb / 10 > 0)
	{
		nb = nb / 10 ;
		size++;
	}
	return (size);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strndup(char *s, size_t strlen)
{
	char	*str;
	size_t	i;

	if (!s)
	{
		str = malloc(sizeof(char) * 7);
		if (!str)
			return (NULL);
		i = -1;
		while ("(null)"[++i])
			str[i] = "(null)"[i];
		str[i] = '\0';
		return (str);
	}
	str = malloc(sizeof(char) * (strlen + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && i < strlen)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
