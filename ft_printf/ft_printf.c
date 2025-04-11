/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:55:30 by vwautier          #+#    #+#             */
/*   Updated: 2024/12/06 12:23:02 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	char	*current_arg;
	int		rbyte;

	rbyte = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			current_arg = process_format(*++format, args);
			print_str(current_arg, *format, &rbyte);
		}
		else
			print_str(NULL, *format, &rbyte);
		if (rbyte == -1)
			break ;
		format++;
	}
	va_end(args);
	return (rbyte);
}

void	print_str(char *current_arg, char format, int *rbyte)
{
	int	tmp;

	if (*rbyte == -1)
		return ;
	if (!current_arg)
	{
		tmp = ft_putchar(format);
		if (tmp == -1)
		{
			*rbyte = -1;
			return ;
		}
		*rbyte += tmp;
		return ;
	}
	tmp = ft_putstr(current_arg, format);
	free(current_arg);
	if (tmp == -1)
	{
		*rbyte = -1;
		return ;
	}
	*rbyte += tmp;
}

char	*process_format(char format, va_list args)
{
	char	*result;

	result = NULL;
	if (format)
	{
		if (format == 's')
		{
			result = va_arg(args, char *);
			result = ft_strndup(result, ft_strlen(result));
		}
		else if (format == 'c')
			result = (ft_chardup(va_arg(args, int)));
		else if (format == 'd' || format == 'i')
			result = ft_itoa(va_arg(args, int));
		else if (format == 'u')
			result = unsigned_itoa(va_arg(args, unsigned int));
		else if (format == 'x' || format == 'X')
			result = ft_itoa16(va_arg(args, unsigned int), &format);
		else if (format == 'p')
			result = ft_itoa16p((unsigned long long)va_arg(args, void *));
		else if (format == '%')
			result = ft_strndup("%", 1);
	}
	return (result);
}

char	*ft_itoa16p(unsigned long long nb)
{
	char	*result;
	int		size;

	if ((void *)nb == NULL)
		return (ft_strndup("(nil)", 5));
	size = size_nombre16(nb, "p");
	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	result[size--] = '\0';
	while (size >= 0)
	{
		if (nb % 16 < 10)
			result[size--] = nb % 16 + '0';
		else
			result[size--] = nb % 16 + 'a' - 10;
		nb = nb / 16;
	}
	result[0] = '0';
	result[1] = 'x';
	return (result);
}

/*
#include <stdio.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>
#include "util.c"
#include "util2.c"

int main(){
	 int ret1, ret2;
    char c = 'a';
    char *str = "test";
    int num = 42;
    int neg = -42;
    unsigned int u_num = 4294967295;
    void *ptr = &num;
	int ret_og, ret_ft;

    // Test %c
    printf("\n=== Test %%c ===\n");
    ret1 = printf("Printf:    [%c]\n", c);
    ret2 = ft_printf("ft_printf: [%c]\n", c);
    printf("Return printf: %d | ft_printf: %d\n", ret1, ret2);

    // Test %s 
    printf("\n=== Test %%s ===\n");
    ret1 = printf("Printf:    [%s]\n", str);
    ret2 = ft_printf("ft_printf: [%s]\n", str);
    printf("Return printf: %d | ft_printf: %d\n", ret1, ret2);
    ret1 = printf("Printf:    [%s]\n", NULL);
    ret2 = ft_printf("ft_printf: [%s]\n", NULL);
    printf("Return printf: %d | ft_printf: %d\n", ret1, ret2);

    // Test %p
    printf("\n=== Test %%p ===\n"); 
    ret1 = printf("Printf:    [%p]\n", ptr);
    ret2 = ft_printf("ft_printf: [%p]\n", ptr);
    printf("Return printf: %d | ft_printf: %d\n", ret1, ret2);
    ret1 = printf("Printf:    [%p]\n", NULL);
    ret2 = ft_printf("ft_printf: [%p]\n", NULL);
    printf("Return printf: %d | ft_printf: %d\n", ret1, ret2);

    // Test %d et %i
    printf("\n=== Test %%d et %%i ===\n");
    ret1 = printf("Printf:    [%d] [%i]\n", num, neg);
    ret2 = ft_printf("ft_printf: [%d] [%i]\n", num, neg);
    printf("Return printf: %d | ft_printf: %d\n", ret1, ret2);

    // Test %u
    printf("\n=== Test %%u ===\n");
    ret1 = printf("Printf:    [%u]\n", u_num);
    ret2 = ft_printf("ft_printf: [%u]\n", u_num);
    printf("Return printf: %d | ft_printf: %d\n", ret1, ret2);

    // Test %x et %X
    printf("\n=== Test %%x et %%X ===\n");
    ret1 = printf("Printf:    [%x] [%X]\n", num, num);
    ret2 = ft_printf("ft_printf: [%x] [%X]\n", num, num);
    printf("Return printf: %d | ft_printf: %d\n", ret1, ret2);

    // Test %%
    printf("\n=== Test %% ===\n");
    ret1 = printf("Printf:    [%%]\n");
    ret2 = ft_printf("ft_printf: [%%]\n");
    printf("Return printf: %d | ft_printf: %d\n", ret1, ret2);

	printf("\n=== Test -1===\n");
    ret1 = printf(NULL);
    ret2 = ft_printf(NULL);
    printf("Return printf: %d | ft_printf: %d\n", ret1, ret2);
	
    int ret_printf, ret_ft_printf;

    //ferme la sortie standart printf ne peux rien afficher
   	close(1);

    // Test avec printf
    ret_printf = printf("Test printf %d\n", 42);
    if (ret_printf < 0)
        fprintf(stderr, "printf a détecté une erreur: %d\n", ret_printf);
    else
        fprintf(stderr, "printf a réussi avec un retour de : %d\n", ret_printf);

    // Test avec ft_printf
    ret_ft_printf = ft_printf("Test ft_printf %d\n", 42);
    if (ret_ft_printf < 0)
        fprintf(stderr, "ft_printf  erreur %d\n", ret_ft_printf);
    else
        fprintf(stderr, "ft_printf a réussi : %d\n", ret_ft_printf);
	
    return 0;
}
*/