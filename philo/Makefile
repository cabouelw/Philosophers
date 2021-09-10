# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cabouelw <cabouelw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/04 13:17:46 by cabouelw          #+#    #+#              #
#    Updated: 2021/09/09 16:55:03 by cabouelw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
THREAD= -pthread
SRC =	main.c\
		parsing.c\
		tools.c\
		ft_atoi.c\
		ft_isdigit.c\
		
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@gcc $(OBJ) $(THREAD) -o $(NAME)


%.o: %.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
