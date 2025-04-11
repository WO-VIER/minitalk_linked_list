/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:57:04 by vwautier          #+#    #+#             */
/*   Updated: 2024/12/06 12:23:05 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

void	print_str(char *current_arg, char format, int *rbyte);
char	*process_format(char format, va_list args);
int		ft_putstr(char *str, char format);
int		size_nombre(long long nb);
char	*ft_strndup(char *s, size_t strlen);
char	*ft_chardup(int c);
size_t	ft_strlen(const char *str);
char	*ft_itoa(int nb);
int		ft_printf(const char *format, ...);
int		ft_putchar(char c);
char	*ft_itoa16(unsigned long long nb, char *format);
char	*ft_itoa16p(unsigned long long nb);
int		size_nombre16(unsigned long long nb, char *format);
char	*unsigned_itoa(unsigned int nb);