# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iderighe <iderighe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/25 17:12:34 by iderighe          #+#    #+#              #
#    Updated: 2024/03/29 13:28:19 by iderighe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	divideandconquer

INC		=	Includes

CC		=	c++
CFLAGS	=	-Wall -Wextra -Werror -g -Wshadow -std=c++98 -I $(INC)
CDEP	=	-MMD
# -Wshadow : Warn whenever a local variable or type declaration shadows another 
# 			variable, parameter, type or class member
CFA		=	-fsanitize=address -g3
RM		=	/usr/bin/rm -rf

vpath %.c Srcs

SRC		=	Srcs/main.cpp \
			Srcs/Account.cpp \
			Srcs/Bank.cpp

OBJ		=	$(SRC:Srcs/%.cpp=Objs/%.o)
DEP		=	$(SRC:Srcs/%.cpp=Objs/%.d)


all			:	obj $(NAME)

-include $(DEP)

$(NAME)		:	$(OBJ)
				$(CC) $(CFLAGS) -o $(NAME) $(SRC)

obj			:
				@if [ ! -d "./Objs" ]; then\
					echo "mkdir -p Objs";\
					mkdir -p Objs;\
				fi
				@echo ""

Objs/%.o	:	Srcs/%.cpp
				$(CC) -o $@ -c $< $(CFLAGS) $(CDEP)

clean		: 
				$(RM) $(OBJ)
				$(RM) Objs

fclean		:	clean
				$(RM) $(NAME)

fsa			:	fclean obj $(OBJ)
				$(CC) $(CFLAGS) $(CDEP) $(CFA) -o $(NAME) $(SRC)

re			:	fclean all

.PHONY		:	all obj clean fclean fsa re
