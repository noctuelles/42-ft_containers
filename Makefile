# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/21 12:26:43 by plouvel           #+#    #+#              #
#    Updated: 2022/09/15 11:04:20 by plouvel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR	=	srcs

OBJS_DIR	=	objs

CFLAGS		=	-Wall -Werror -Wextra -std=c++98 -MD -g3 -fsanitize=address

CINCS		=	-I includes

CC			=	c++

SRCS		=	main.cpp

OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))

DEPS		=	$(addprefix $(OBJS_DIR)/, $(SRCS=.cpp=.d))

NAME		=	ft_containers

RM			=	rm -rf

$(NAME):	$(OBJS) Makefile
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.cpp | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(CINCS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $@

all:	$(NAME)

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

-include $(DEPS)

.PHONY:	all clean fclean re
