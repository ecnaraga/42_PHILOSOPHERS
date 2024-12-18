# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: galambey <galambey@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/10 11:40:45 by galambey          #+#    #+#              #
#    Updated: 2023/08/31 16:57:42 by galambey         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = cc
C_FLAGS = -Wall -Wextra -Werror -MMD

################################### SOURCES ###################################

SRCS_DIR 	= 	srcs
OBJS_DIR 	= 	objs

SRCS 		= 	parsing.c \
	   			routine.c \
	   			action.c \
	   			action_utils.c \
	   			monitoring.c \
	   			atoi.c \
	   			free.c \
	   			error.c

SRCS := $(SRCS:%=$(SRCS_DIR)/%)
OBJS := $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

#################################### RULES ####################################

all : $(NAME)

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(C_FLAGS) -pthread -g -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(C_FLAGS) -g $(OBJS) -o $@

-include $(DEPS)

clean :
	rm -rf $(OBJS_DIR)

fclean : clean
	rm -f philo_bonus

re : fclean
	make all

.PHONY : all clean fclean re