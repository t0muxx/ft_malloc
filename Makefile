# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/24 11:50:56 by tmaraval          #+#    #+#              #
#    Updated: 2019/10/01 21:40:23 by tmaraval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#NAME OF THE PROG#
ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME =			libft_malloc_$(HOSTTYPE).so
LINK =			libft_malloc.so

#FLAG AND COMPILATOR#
CC =		gcc
CFLAGS =  -g -Wall -Werror -Wextra -fPIC -fsanitize=address

#PATH#
OBJ_PATH =  obj
SRC_PATH =  src
INC_PATH =  inc

SRCS = malloc.c \
	   init.c \
	   debug.c \
	   free.c \
	   utils.c \
	   zone.c \
	   chunks.c \
	   page.c

OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
SRC = $(addprefix $(SRC_PATH)/,$(SRCS))

all: $(NAME)

$(NAME): $(OBJ)
	@+$(MAKE) -C libft/
	@$(CC) $(CFLAGS) -I$(INC_PATH) $(OBJ) libft/libft.a  -shared -o $(NAME)
	@/bin/rm -f $(LINK)
	@ln -s $(NAME) $(LINK)

$(OBJ): $(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) -o $@ $(CFLAGS) -I$(INC_PATH) -c $<

clean:
	/bin/rm -rf $(OBJ_PATH)
	@(cd libft ; make clean)

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f libft/libft.a

re: fclean all

.PHONY: all clean fclean re
