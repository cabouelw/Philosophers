# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/04 13:17:46 by cabouelw          #+#    #+#              #
#    Updated: 2021/09/09 16:52:17 by cabouelw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror
THREAD= -pthread
SRC =	main_bonus.c\
		parsing_bns.c\
		tools.c\
		ft_atoi.c\
		ft_isdigit.c\
		
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@gcc $(OBJ) $(THREAD) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@

bonus: $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
