# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emauduit <emauduit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/05 10:51:20 by azbk              #+#    #+#              #
#    Updated: 2024/04/09 14:38:50 by emauduit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



################################################################################
#                                COMPILATION                                   #
################################################################################

NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
CIFLAGS	= -Iincludes -I$(LIB_DIR)/includes
MAKEFLAGS += --no-print-directory


SRC_DIR = ./src

################################################################################
#                                  SOURCES                                     #
################################################################################

SRC := check_state.c \
		free_function.c \
		main.c \
		init.c \
		time.c \
		utils_parsing.c

SRC := $(addprefix $(SRC_DIR)/, $(SRC))

################################################################################
#                                  OBJECTS / DEP                                #
################################################################################

OBJ_DIR = obj
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

DEPS := $(OBJ:.o=.d)
DEPS += ./libft/*.d

################################################################################
#                                  ASCII ART                                   #
################################################################################

PINK = \033[1;95m
RED = \033[0;91m
CYAN = \033[0;96m
MAGENTA = \033[1;35m
RESET = \033[0m

################################################################################
#                                  MAKEFILE                                    #
################################################################################

all: $(NAME) 
		
$(NAME): $(OBJ) 
	@$(CC) $(CFLAGS) $(CIFLAGS) $(OBJ) $(CCLIED) -o $(NAME)
	@echo "\n$(CYAN)$(NAME) compiled!$(RESET)"
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ 
	@echo "$(MAGENTA)Compiling: $< $(DEF_COLOR)$(RESET)"

################################################################################
#                                  CLEAN / FCLEAN                              #
################################################################################


clean:
	@echo "\n$(RED)Removing: $(OBJ) $(OBJ_DIR) $(DEF_COLOR)$(RESET)\n"
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Dependencies have been removed.$(RESET)"
	@echo "$(RED)Obj directory has been removed.$(RESET)\n"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.EXTRA_PREREQS:= $(abspath $(lastword $(MAKEFILE_LIST)))
-include $(DEPS)