NAME = libdlst.a

CC = gcc
C_FLAGS = -Wall -Wextra -I$(DIR_INC)

DIR_INC = include/
DIR_SRC = src/
DIR_OBJ = obj/

C_FILES =	dbl_lst.c

OBJS = $(addprefix $(DIR_OBJ), $(patsubst %.c,%.o,$(C_FILES)))

all:$(DIR_OBJ) $(NAME)

clean:
	@rm -rf $(DIR_OBJ)

fclean:clean
	@rm -f $(NAME)

re:fclean all

$(NAME):$(OBJS)
	@ar -cr $(NAME) $?

$(DIR_OBJ)%.o:$(DIR_SRC)%.c
	@$(CC) $(C_FLAGS) -c -o $@ $^

$(DIR_OBJ):
	@mkdir $(DIR_OBJ)


.PHONY:all clean fclean re bonus
