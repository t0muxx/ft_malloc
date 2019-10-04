# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/24 11:50:56 by tmaraval          #+#    #+#              #
#    Updated: 2019/10/03 17:10:21 by tmaraval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
#NAME OF THE PROG#
NAME =			unit_tests.bin

#FLAG AND COMPILATOR#
CC =		clang
CFLAGS =  -g 

#PATH#
OBJ_PATH =  obj/
SRC_PATH =  ./
INC_PATH :=  ./

ifeq ($(HOSTTYPE),x86_64_Darwin)
	INC_BREW = -I/Users/tmaraval/.brew/include
	LIB_BREW = -L/Users/tmaraval/.brew/lib
endif

SRCS = main.c \
	   test_zone.c \
	   test_free.c \
	   test_page.c \
	   test_malloc.c \
	   utils.c

OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
SRC = $(addprefix $(SRC_PATH)/,$(SRCS))

all: $(NAME) $(COVERAGE)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I$(INC_PATH) $(INC_BREW) $(OBJ) ../libft_malloc.so $(LIB_BREW) -lcmocka -o $(NAME)
ifeq ($(HOSTTYPE),x86_64_Darwin)
	cp ../libft_malloc_x86_64_Darwin.so .
endif

$(OBJ): $(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	echo $(INC_BREW)
	echo $(LIB_BREW)
	mkdir -p $(dir $@)
	$(CC) -o $@ $(CFLAGS) -I$(INC_PATH) $(INC_BREW) -I../inc/ -c $<

clean:
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
