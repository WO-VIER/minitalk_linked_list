# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vwautier <vwautier@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 16:08:55 by vwautier          #+#    #+#              #
#    Updated: 2025/04/11 13:04:48 by vwautier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a

# Fichiers source normaux
SRCS = 		ft_printf.c \
			util.c		\
			util2.c
#BONUS_SRCS = 		

OBJS = $(SRCS:.c=.o)
#BONUS_OBJS = $(BONUS_SRCS:.c=.o)

# Règle par défaut
all: $(NAME)

# Règle pour créer la bibliothèque statique
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

# Règle pour compiler les fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers objets
clean:
	rm -f $(OBJS) $(BONUS_OBJS)

# Règle pour nettoyer tout (fichiers objets et bibliothèque)
fclean: clean
	rm -f $(NAME)

# Règle pour recompiler tout
re: fclean all

# Règle pour compiler les fichiers bonus
#bonus: $(OBJS) $(BONUS_OBJS)
#ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

# Indique que ces règles ne sont pas des fichiers
.PHONY: all clean fclean re 