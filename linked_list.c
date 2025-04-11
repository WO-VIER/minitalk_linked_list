/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:26:56 by vwautier          #+#    #+#             */
/*   Updated: 2025/04/12 01:00:35 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_node	*add_node(t_node **head, char c)
{
	t_node	*new;
	t_node	*current;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->c = c;
	new->next = NULL;
	if (*head == NULL)
	{
		*head = new;
		return (new);
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new;
	return (new);
}

void	free_list(t_node **head)
{
	t_node	*current;
	t_node	*next;

	if (!head || !*head)
		return ;

	current = *head;
	while (current)
	{
		next = current->next;
		free(current);
		current = NULL;
		current = next;
	}
	*head = NULL;
}

void	printfree(t_node **head)
{
	t_node	*current;
	t_node	*next;

	current = *head;
	while (current)
	{
		write(1, &current->c, 1);
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
	write(1, "\n", 1);
}
