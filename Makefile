##
## Makefile for makefile in /home/zellou_i/rendu/PSU_2013_lemipc
##
## Made by ilyas zelloufi
## Login   <zellou_i@epitech.net>
##
## Started on  Fri Mar 28 22:57:18 2014 ilyas zelloufi
## Last update Sun Mar 30 19:25:39 2014 ilyas zelloufi
##

NAME	=	lemipc

SRC	=	ia.c \
		make_map.c \
		my_lib.c \
		lemipc.c \
		main.c

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

CFLAGS	=	-W -Wextra

RM	=	rm -f
ECHO	=	echo -e

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
		@$(ECHO) '\033[0;32m> Compiled\033[0m'

clean	:
		@$(RM) $(OBJ)
		@$(RM) *~
		@$(RM) \#*#
		@$(ECHO) '\033[0;31m> Directory cleaned\033[0m'


fclean	:	clean
		@$(RM) $(NAME)
		@$(ECHO) '\033[0;31m> Remove executable\033[0m'

re	:	fclean  all

.PHONY	:	all clean fclean re
