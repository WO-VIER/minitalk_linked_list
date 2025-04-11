/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:56:14 by vwautier          #+#    #+#             */
/*   Updated: 2025/04/11 19:00:34 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "ft_printf/ft_printf.h"

typedef struct s_node
{
	char				c;
	struct s_node		*next;
}	t_node;

void	error_exit(void);
int		ft_pidtoi(const char *string);

//linked_list.c
void	free_list(t_node **head);
void	printfree(t_node **head);
t_node	*add_node(t_node **head, char c);
#endif