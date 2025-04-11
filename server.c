/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:55:28 by vwautier          #+#    #+#             */
/*   Updated: 2025/04/12 00:52:26 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//static t_node *g_message = NULL;

/*
** 1. Dans signalhandler:
** - OR le bit a 1 de poids fort vers faible
** - Envoie un signal au client pour l'ack
**
** 2. Dans signalsetup:
** - Passe le handler a la structure
** - Active le flag pour passer le siginfo_t qui
** 		donne plus de détails sur le signal
** - Vide le masque
** - Permet de bloquer SIGUSR1 et SIGUSR2 quand le handler est en traitement
** - Quand le programme recois un SIGUSR 1 ou 2 il va se suspendre
**   pour lancer le signalhandler et bloque les signaux SIGUSR 1 et 2
**   pendant le traitement
*/

static t_node	*g_message = NULL;

static void	sigint_handler(int sig)
{
	(void)sig;
	free_list(&g_message);
	exit(EXIT_SUCCESS);
}

static void	charprocess(char *c, int *bit, t_node **list)
{
	(*bit)++;
	if (*bit == 8)
	{
		*bit = 0;
		if (*c == '\0')
			printfree(list);
		else
		{
			if (!add_node(list, *c))
			{
				write(2, "Error: Memory allocation failed\n", 32);
				free_list(list);
				exit(EXIT_FAILURE);
			}
		}
		*c = 0;
	}
}

static void	signalhandler(int sig, siginfo_t *info, void *context)
{
	static int		bit = 0;
	static char		c = 0;
	static int		pids = 0;
	static int		lastpid = 0;
	//static t_node	*message = NULL;
	(void)context;
	pids = info->si_pid;
	if (pids != lastpid)
	{
		lastpid = pids;
		bit = 0;
		c = 0;
		free_list(&g_message);
	}
	if (sig == SIGUSR1)
		c |= (0b10000000 >> bit);
	charprocess(&c, &bit, &g_message);
	kill(pids, SIGUSR1);
}

static void	signalsetup(struct sigaction *sa)
{
	sa->sa_sigaction = signalhandler;
	sa->sa_flags = SA_SIGINFO;
	sigemptyset(&sa->sa_mask);
	sigaddset(&sa->sa_mask, SIGUSR1);
	sigaddset(&sa->sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, sa, NULL) == -1
		|| sigaction(SIGUSR2, sa, NULL) == -1)
	{
		write(2, "ERROR : SIGACTION\n", 18);
		exit(EXIT_FAILURE);
	}
	signal(SIGINT, sigint_handler);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void)argv;
	if (argc != 1)
	{
		write(2, "ERROR : NO PARAMS !\n", 20);
		exit(EXIT_FAILURE);
	}
	ft_printf("Le PID du serveur est :  %d\n", getpid());
	signalsetup(&sa);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
