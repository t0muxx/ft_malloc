# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/24 11:50:56 by tmaraval          #+#    #+#              #
#    Updated: 2019/10/01 15:25:28 by tmaraval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#NAME OF THE PROG#
NAME =			unit_tests.bin

#FLAG AND COMPILATOR#
CC =		gcc
CFLAGS =  -g -fsanitize=address

#PATH#
OBJ_PATH =  obj
SRC_PATH =  ./
INC_PATH =  ./

SRCS = main.c \
	   test_zone.c \
	   test_free.c \
	   test_page.c \
	   utils.c

OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
SRC = $(addprefix $(SRC_PATH)/,$(SRCS))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -I$(INC_PATH) $(OBJ) ../libft_malloc.so -lcmocka -o $(NAME)

$(OBJ): $(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) -o $@ $(CFLAGS) -I$(INC_PATH) -I../inc/ -c $<

clean:
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
