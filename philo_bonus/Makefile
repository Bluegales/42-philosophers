# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/10 12:13:51 by pfuchs            #+#    #+#              #
#    Updated: 2022/04/20 05:42:22 by pfuchs           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH = src

# Compiler Variables
CC		= gcc
CFLAGSS	= -Wall -Wextra -Werror -g
INCFLAG	= -Imlx -I include -I libft
# File Variables
NAME	= philo
SRC		= main.c doctor.c philo.c philo_factory.c time.c
OBJ		= $(addprefix _bin/,$(notdir $(SRC:.c=.o)))

$(NAME): $(OBJ)
	$(CC) -pthread $(CFLAGS) -o $@ $^

libft/libft.a :
	-(cd libft && make && make clean)

_bin :
	mkdir _bin

_bin/%.o : %.c | _bin
	$(CC) -c $(CFLAGSS) -MMD -MP $(INCFLAG) $< -o $@

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(NAME)

re:		fclean all

all:	$(NAME)

norm:
	norminette $(SRC)

.PHONY: clean fclean re all

-include $(OBJ:.o=.d)
