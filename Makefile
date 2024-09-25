# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: artberna <artberna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/27 13:25:02 by artberna          #+#    #+#              #
#    Updated: 2024/09/06 11:21:12 by artberna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
HEADER = philo.h

#******************************************************************************
#                                 DIRECTORIES                                 *
#******************************************************************************

OBJ_DEP_DIR = obj_dep/
SRC_DIR = src/

#******************************************************************************
#                       SOURCES, OBJECTS & DEPENDENCIES                       *
#******************************************************************************

PHILO_SRC = main struct_init utils thread_n_monitoring thread_routine monitoring_routine

PHILO_FLS = $(addsuffix .c, $(PHILO_SRC))

SRC = $(PHILO_FLS)

OBJ = $(addprefix $(OBJ_DEP_DIR), $(SRC:.c=.o))

OBJF = .cache_exists

DEP = $(addprefix $(OBJ_DEP_DIR), $(OBJ:.o=.d))

#******************************************************************************
#                                INSTRUCTIONS                                 *
#******************************************************************************

CC = cc -g3
SPECIAL_FLAGS = -pthread
FLAGS = -Wall -Wextra -Werror -I.
RM = rm -rf
AR = ar rcs

#******************************************************************************
#                                  COLORS                                     *
#******************************************************************************

RESET = \033[0m
ROSE = \033[1;38;5;225m
VIOLET = \033[1;38;5;55m
VERT = \033[1;38;5;85m
BLEU = \033[1;34m

#******************************************************************************
#                                COMPILATION                                  *
#******************************************************************************

all : $(NAME)
	@echo "$(ROSE)COMPILATION FINISHED, $(NAME) IS CREATED!$(RESET)"

$(NAME) : $(OBJ)
	@$(CC) $(FLAGS) $(SPECIAL_FLAGS) $(OBJ) -o $(NAME)

$(OBJ_DEP_DIR)%.o: %.c $(HEADER) | $(OBJF)
	@$(CC) $(FLAGS) -MMD -MP -c $< -o $@
	@echo "$(BLEU)Compiling $< to $@.$(RESET)"

$(OBJF):
	@mkdir -p $(OBJ_DEP_DIR)

clean :
	@$(RM) $(OBJ_DEP_DIR)
	@echo "$(VIOLET)Suppressing objects & dependencies files of $(NAME).$(RESET)"

fclean : clean
	@$(RM) $(NAME)
	@echo "$(VERT)Suppressing archives $(NAME).$(RESET)"

re : fclean all

-include $(DEP)

.PHONY : re fclean clean all