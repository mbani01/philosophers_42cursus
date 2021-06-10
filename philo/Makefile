# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbani <mbani@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/07 12:05:27 by mbani             #+#    #+#              #
#    Updated: 2021/06/10 10:46:56 by mbani            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c philo_arg.c threads_creation.c threads_start.c threads_supervisor.c utils.c 
NAME = philo
FLAG = -Wall -Wextra -Werror

all : $(NAME)

$(NAME): $(SRC)
	@gcc $(FLAG) $(SRC) -o $(NAME)
clean:
	@rm -rf $(NAME)
fclean: clean
re : fclean all
.PHONY: all clean fclean re