/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:06:54 by vwautier          #+#    #+#             */
/*   Updated: 2025/04/12 13:53:22 by vwautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
** 1. Configuration des signaux
**    - Mise en place du handler pour recevoir les ACK du serveur
**    - Utilise SIGUSR1 pour les ACK de réception
**
** 2. Traitement des caractères (processchar):
**    - Décompose chaque caractère en 8 bits
**			isole bit par bit poids fort -> faible avec un masque
**    - Envoie SIGUSR1 pour un bit à 1
**    - Envoie SIGUSR2 pour un bit à 0
**    - Attend l'ACK du serveur après chaque bit
**
** 3. Synchronisation:
**    - Utilise une variable volatile sig_atomic_t pour la synchronisation
**    - Attend la confirmation du serveur avant d'envoyer le bit suivant
**    - Réinitialise le flag après chaque ACK
*/

static volatile sig_atomic_t	g_serveur = 0;

static void	handler(int sig)
{
	if (sig == SIGUSR1)
		g_serveur = 1;
}

static void	signalsetup(struct sigaction *sa)
{
	sa->sa_handler = handler;
	sa->sa_flags = 0;
	sigemptyset(&sa->sa_mask);
	sigaddset(&sa->sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, sa, NULL) == -1)
	{
		write(2, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
}

static void	processchar(char c, int pid)
{
	int	bit;
	int	time_count;

	bit = 0;
	time_count = 0;
	while (bit < 8)
	{
		if (c & (0b10000000 >> bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_serveur)
		{
			usleep(1000);
			time_count++;
			if (time_count >= 1000)
			{
				write(2, "Error: Server not responding\n", 29);
				exit(EXIT_FAILURE);
			}
		}
		g_serveur = 0;
		bit++;
	}
}

int	main(int argc, char **argv)
{
	int					pids;
	char				*currentmessage;
	struct sigaction	sa;

	if (argc != 3)
	{
		write(2, "Client <PID> \"message\"\n", 23);
		exit(EXIT_FAILURE);
	}
	signalsetup(&sa);
	pids = ft_pidtoi(argv[1]);
	if (kill(pids, 0) == -1)
		error_exit();
	currentmessage = argv[2];
	while (*currentmessage)
		processchar(*currentmessage++, pids);
	processchar('\0', pids);
	return (EXIT_SUCCESS);
}
