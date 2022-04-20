# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfuchs <pfuchs@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/10 12:13:51 by pfuchs            #+#    #+#              #
#    Updated: 2022/04/20 23:53:24 by pfuchs           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH = src

# Compiler Variables
CC		= gcc
CFLAGSS	= -Wall -Wextra -Werror -g
INCFLAG	= -Imlx -I include -I libft
# File Variables
NAME	= philo
SRC_NAMES	= main doctor philo philo_util philo_factory time \
			ft_save_atoi ft_save_atol ft_save_atoll
SRC		= $(addsuffix .c,$(SRC_NAMES))
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
