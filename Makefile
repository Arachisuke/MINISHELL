NAME = minishell
SRC	= srcs/fonction.c srcs/main.c srcs/init_node.c srcs/tokenisation.c srcs/verif_line.c srcs/automate.c srcs/here_doc.c srcs/find_var.c \
		 srcs/sort_cmds.c srcs/init_tcmds.c srcs/sort_cmds_utils.c srcs/free.c srcs/init_t_redir.c srcs/expandornot.c \
		 srcs/init_expand.c srcs/get_env.c srcs/get_final_line.c srcs/mallocs.c \
		 
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