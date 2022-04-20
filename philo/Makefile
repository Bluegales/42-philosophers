# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/10 12:13:51 by pfuchs            #+#    #+#              #
#    Updated: 2022/04/21 00:56:46 by pfuchs           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler Variables
CC		= gcc
CFLAGSS	= -Wall -Wextra -Werror
INCFLAG	=
# File Variables
NAME	= philo
SRC_N	= main doctor philo philo_util philo_factory time \
			ft_save_atoi ft_save_atol ft_save_atoll
SRC		= $(addsuffix .c,$(SRC_N))
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

fclean:
	@rm -fr _bin

re:		fclean all

all:	$(NAME)

.PHONY: clean fclean re all

-include $(OBJ:.o=.d)
