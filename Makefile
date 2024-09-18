NAME = minishell
SRC	= srcs/fonction.c srcs/main.c srcs/init_node.c srcs/tokenisation.c srcs/verif_line.c srcs/automate.c srcs/sort_cmds.c srcs/init_tcmds.c
OBJ = $(SRC:.c=.o)
LIBFT = ./libft/libft.a
CC = gcc
FLAG = -Wall -Werror -Wextra -g3
LD_FLAGS = -lreadline -lncurses -lcurses

$(NAME): $(OBJ) $(LIBFT) 
	$(CC) $(FLAG) -o $(NAME) $(SRC) $(LIBFT) $(LD_FLAGS) 

all: $(NAME)

$(LIBFT):
	make -C ./libft

clean:
	rm -rf $(OBJ)
	make -C ./libft clean
	
fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean

re: fclean all           