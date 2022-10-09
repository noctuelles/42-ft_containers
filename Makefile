# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/21 12:26:43 by plouvel           #+#    #+#              #
#    Updated: 2022/10/09 18:54:27 by plouvel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

red = @/bin/echo -e "\x1b[31;1;4m\#\# $1\x1b[0m"
green = @/bin/echo -e "\x1b[32;1;4m\#\# $1\x1b[0m"

SRCS_DIR		=	srcs

OBJS_DIR		=	objs

TEST_OUT_DIR	 =	test_out

ASAN		=	-fsanitize=address

CFLAGS		=	-Wall -Werror -Wextra -std=c++98 -g3 $(ASAN) 

CINCS		=	-I includes

CC			=	c++

VECTOR_SRCS		=	main_vector.cpp		\
					test_utils.cpp

STACK_SRCS		=	main_stack.cpp

MAP_SRCS		=	main_map.cpp		\
					RBT.cpp				\
					RBTNode.cpp			\
					test_utils.cpp

VECTOR_OBJS_FT		=	$(addprefix $(OBJS_DIR)/, $(VECTOR_SRCS:.cpp=.o.ft))
VECTOR_OBJS_STD		=	$(addprefix $(OBJS_DIR)/, $(VECTOR_SRCS:.cpp=.o.std))

STACK_OBJS_FT		=	$(addprefix $(OBJS_DIR)/, $(STACK_SRCS:.cpp=.o.ft))
STACK_OBJS_STD		=	$(addprefix $(OBJS_DIR)/, $(STACK_SRCS:.cpp=.o.std))

MAP_OBJS_FT		=	$(addprefix $(OBJS_DIR)/, $(MAP_SRCS:.cpp=.o.ft))
MAP_OBJS_STD	=	$(addprefix $(OBJS_DIR)/, $(MAP_SRCS:.cpp=.o.std))

RM			=	rm -rf

all:	test_vector test_stack test_map

test_vector_ft: $(VECTOR_OBJS_FT)
		$(CC) $(ASAN) $(CINCS) -o $@ $(VECTOR_OBJS_FT) -D NAMESPACE=ft

test_vector_std: $(VECTOR_OBJS_STD)
		$(CC) $(ASAN) $(CINCS) -o $@ $(VECTOR_OBJS_STD) -D NAMESPACE=std

test_vector: test_vector_ft test_vector_std | $(TEST_OUT_DIR)
		$(call green, "Comparing vector output... a diff in capacity is acceptable.")
		./$< > $(TEST_OUT_DIR)/$<_output
		./$(word 2, $^) > $(TEST_OUT_DIR)/$(word 2, $^)_output
		-@cd $(TEST_OUT_DIR) && \
			diff --unified=0 --report-identical-files $<_output $(word 2, $^)_output
		$(call red, "End of vector test.")

test_stack_ft: $(STACK_OBJS_FT)
		$(CC) $(ASAN) $(CINCS) -o $@ $(STACK_OBJS_FT) -D NAMESPACE=ft

test_stack_std: $(STACK_OBJS_STD)
		$(CC) $(ASAN) $(CINCS) -o $@ $(STACK_OBJS_STD) -D NAMESPACE=std

test_stack: test_stack_ft test_stack_std | $(TEST_OUT_DIR)
		$(call green, "Comparing stack output...")
		./$< > $(TEST_OUT_DIR)/$<_output
		./$(word 2, $^) > $(TEST_OUT_DIR)/$(word 2, $^)_output
		-@cd $(TEST_OUT_DIR) && \
			diff --unified=0 --report-identical-files $<_output $(word 2, $^)_output
		$(call red, "End of stack test.")

test_map_ft: $(MAP_OBJS_FT)
		$(CC) $(ASAN) $(CINCS) -o $@ $(MAP_OBJS_FT) -D NAMESPACE=ft

test_map_std: $(MAP_OBJS_STD)
		$(CC) $(ASAN) $(CINCS) -o $@ $(MAP_OBJS_STD) -D NAMESPACE=std

test_map: test_map_ft test_map_std | $(TEST_OUT_DIR)
		$(call green, "Comparing map output...")
		./$< > $(TEST_OUT_DIR)/$<_output
		./$(word 2, $^) > $(TEST_OUT_DIR)/$(word 2, $^)_output
		-@cd $(TEST_OUT_DIR) && \
			diff --unified=0 --report-identical-files $<_output $(word 2, $^)_output
		$(call red, "End of map test.")

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(TEST_OUT_DIR)
	@$(RM) test_vector_ft
	@$(RM) test_vector_std
	@$(RM) test_stack_ft
	@$(RM) test_stack_std
	@$(RM) test_map_ft
	@$(RM) test_map_std

re:	fclean all

$(OBJS_DIR)/%.o.ft:	$(SRCS_DIR)/%.cpp | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(CINCS) -c $< -o $@ -D NAMESPACE=ft

$(OBJS_DIR)/%.o.std:	$(SRCS_DIR)/%.cpp | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(CINCS) -c $< -o $@ -D NAMESPACE=std

$(OBJS_DIR):
	@mkdir -p $@

$(TEST_OUT_DIR):
	@mkdir -p $@ 

.PHONY:	all clean fclean re test_vector test_stack test_map
