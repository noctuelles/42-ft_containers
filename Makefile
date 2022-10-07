# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/21 12:26:43 by plouvel           #+#    #+#              #
#    Updated: 2022/10/07 16:18:57 by plouvel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

red = @/bin/echo -e "\x1b[31;1;4m\#\# $1\x1b[0m"

SRCS_DIR	=	srcs

OBJS_DIR	=	objs

TMP_DIR     =	tmp

CFLAGS		=	-Wall -Werror -Wextra -std=c++98 -g3 -fsanitize=address

CINCS		=	-I includes

CC			=	c++

VECTOR_SRCS		=	$(SRCS_DIR)/main_vector.cpp

STACK_SRCS		=	$(SRCS_DIR)/main_stack.cpp

MAP_SRCS		=	$(SRCS_DIR)/main_map.cpp		\
					$(SRCS_DIR)/RBT.cpp				\
					$(SRCS_DIR)/RBTNode.cpp			\

SET_SRCS		=	$(SRCS_DIR)/main_set.cpp		\
					$(SRCS_DIR)/RBT.cpp				\
					$(SRCS_DIR)/RBTNode.cpp			\

RM			=	rm -rf

$(OBJS_DIR):
	mkdir -p $@

all:	vector stack

vector: | tmp
		$(call red, "Compiling vector test...")
		$(CC) $(CFLAGS) $(CINCS) -o $(TMP_DIR)/test_$@_ft $(VECTOR_SRCS) -D NAMESPACE=ft
		$(CC) $(CFLAGS) $(CINCS) -o $(TMP_DIR)/test_$@_std $(VECTOR_SRCS) -D NAMESPACE=std
		$(call red, "Comparing output... a diff in capacity is acceptable.")
		-@cd $(TMP_DIR); \
			./test_$@_ft > output_$@_ft; \
			./test_$@_std > output_$@_std; \
			diff --report-identical-files output_$@_ft output_$@_std 

stack: | tmp
		$(call red, "Compiling stack test...")
		$(CC) $(CFLAGS) $(CINCS) -o $(TMP_DIR)/test_$@_ft $(STACK_SRCS) -D NAMESPACE=ft
		$(CC) $(CFLAGS) $(CINCS) -o $(TMP_DIR)/test_$@_std $(STACK_SRCS) -D NAMESPACE=std
		$(call red, "Comparing output...")
		-@cd $(TMP_DIR) && \
			./test_$@_ft > output_$@_ft && \
			./test_$@_std > output_$@_std && \
			diff --report-identical-files output_$@_ft output_$@_std 

map: | tmp
		$(call red, "Compiling map test...")
		$(CC) $(CFLAGS) $(CINCS) -o $(TMP_DIR)/test_$@_ft $(MAP_SRCS) -D NAMESPACE=ft
		$(CC) $(CFLAGS) $(CINCS) -o $(TMP_DIR)/test_$@_std $(MAP_SRCS) -D NAMESPACE=std
		$(call red, "Comparing output...")
		-@cd $(TMP_DIR) && \
			./test_$@_ft > output_$@_ft && \
			./test_$@_std > output_$@_std && \
			diff --report-identical-files output_$@_ft output_$@_std 

set: | tmp

clean:
	$(RM) $(TMP_DIR)/test_*

fclean: clean
	$(RM) $(TMP_DIR)

re:	fclean all

tmp:
	mkdir -p $@ 

.PHONY:	all clean fclean re vector stack map set
