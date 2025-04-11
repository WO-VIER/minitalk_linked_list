/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 20:34:14 by vwautier          #+#    #+#             */
/*   Updated: 2024/12/06 12:23:11 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_chardup(int c)
{
	char	*str;

	str = malloc(2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*ft_itoa(int nb)
{
	char	*result;
	int		size;

	if (nb == 2147483647)
		return (ft_strndup("2147483647", 10));
	if (nb == -2147483648)
		return (ft_strndup("-2147483648", 11));
	size = size_nombre((int)nb);
	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	result[size] = '\0';
	if (nb == 0)
		result[0] = '0';
	if (nb < 0)
	{
		result[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		result[--size] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (result);
}

char	*unsigned_itoa(unsigned int nb)
{
	char	*result;
	int		size;

	if (nb == 4294967295)
		return (ft_strndup("4294967295", 10));
	size = size_nombre((unsigned int)nb);
	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	result[size] = '\0';
	while (size > 0)
	{
		size--;
		result[size] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (result);
}

int	size_nombre16(unsigned long long nb, char *format)
{
	int	size;

	size = 1;
	while (nb / 16 > 0)
	{
		nb = nb / 16;
		size++;
	}
	if (*format == 'p')
		size = size + 2;
	return (size);
}

char	*ft_itoa16(unsigned long long nb, char *format)
{
	char	*result;
	int		size;

	size = size_nombre16(nb, format);
	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	result[size--] = '\0';
	while (size >= 0)
	{
		if (nb % 16 < 10)
			result[size--] = nb % 16 + '0';
		else if (*format == 'X')
			result[size--] = nb % 16 + 'A' - 10;
		else if (*format == 'x' || *format == 'p')
			result[size--] = nb % 16 + 'a' - 10;
		nb = nb / 16;
	}
	return (result);
}
