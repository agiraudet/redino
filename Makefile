# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/06 15:43:27 by agiraude          #+#    #+#              #
#    Updated: 2021/02/19 01:14:10 by agiraude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	redino

INC_DIR			=	-I includes/

DEP				=	-lncurses

SRCS_FILE		=	main.c \
					object.c \
					player.c \
					logic.c \
					controller.c \
					level.c \
					render.c \
					init.c \
					utils.c \
					egg.c \
					gnl/get_next_line.c \
					gnl/get_next_line_utils.c \
					obj/lever.c \
					obj/door.c \
					obj/spike.c \
					obj/portal.c \
					obj/check.c \
					mson/mson.c

SRCS_DIR		=	srcs/

SRCS			=	$(addprefix $(SRCS_DIR), $(SRCS_FILE))

OBJS			=	$(SRCS:.c=.o)

CFLAGS			=	-Wall -g -Wextra $(INC_DIR)

CC				=	clang

%.o:			%.s
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):		$(OBJS) 
				$(CC) $(CFLAGS) $(OBJS) $(DEP) -o $(NAME)


all:			$(NAME)

clean:
				rm -f $(OBJS)

fclean:			clean
				rm -f $(NAME)

re:				fclean all

.PHONY:			all clean flcean re
