# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/21 12:26:43 by plouvel           #+#    #+#              #
#    Updated: 2022/10/07 15:36:20 by plouvel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

red = @/bin/echo -e "\x1b[31;1m\#\# $1\x1b[0m"

SRCS_DIR	=	srcs

OBJS_DIR	=	objs

TMP_DIR     =	tmp

CFLAGS		=	-Wall -Werror -Wextra -std=c++98 -g3

CINCS		=	-I includes

CC			=	c++

VECTOR_SRCS		=	$(SRCS_DIR)/main_vector.cpp

OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))

NAME		=	ft_containers

RM			=	rm -rf

$(NAME):	$(OBJS) Makefile
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.cpp | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(CINCS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $@

all:	$(NAME)

vector: | tmp
		$(call red, "Compiling...")
		$(CC) $(CFLAGS) $(CINCS) -o $(TMP_DIR)/test_vector_ft $(VECTOR_SRCS) -D NAMESPACE=ft
		$(CC) $(CFLAGS) $(CINCS) -o $(TMP_DIR)/test_vector_std $(VECTOR_SRCS) -D NAMESPACE=std
		$(call red, "Comparing output... a diff in capacity is acceptable.")
		-@cd $(TMP_DIR); \
			./test_vector_ft > output_vector_ft; \
			./test_vector_std > output_vector_std; \
			diff output_vector_ft output_vector_std 

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

tmp:
	mkdir -p $@ 

.PHONY:	all clean fclean re vector
