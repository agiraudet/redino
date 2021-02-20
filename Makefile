# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/06 15:43:27 by agiraude          #+#    #+#              #
#    Updated: 2021/02/20 16:34:00 by agiraude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	redino

INC_DIR			=	-I includes/

DEP				=	-lSDL2

SRCS_FILE		=	main.c \
					play.c \
					object.c \
					player.c \
					logic.c \
					controller.c \
					level.c \
					render.c \
					utils.c \
					egg.c \
					scene.c \
					loader.c \
					gnl/get_next_line.c \
					gnl/get_next_line_utils.c \
					obj/lever.c \
					obj/door.c \
					obj/spike.c \
					obj/portal.c \
					obj/check.c \

SRCS_DIR		=	srcs/

SRCS			=	$(addprefix $(SRCS_DIR), $(SRCS_FILE))

OBJS			=	$(SRCS:.c=.o)

CFLAGS			=	-Wall -Wextra $(INC_DIR)

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
