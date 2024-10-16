NAME = minishell
LIB_SHELL = minishell.a
SRC	= srcs/fonction.c srcs/main.c srcs/init_node.c srcs/tokenisation.c srcs/verif_line.c srcs/automate.c srcs/here_doc.c srcs/find_var.c \
		 srcs/sort_cmds.c srcs/init_tcmds.c srcs/sort_cmds_utils.c srcs/free.c srcs/init_t_redir.c srcs/expandornot.c \
		 srcs/init_expand.c srcs/get_env.c srcs/get_final_line.c srcs/mallocs.c  srcs/init.c srcs/ft_error.c srcs/token_utils.c\
		 srcs/utils.c srcs/init_env.c \
		 
OBJ = $(SRC:.c=.o)
LIBFT = ./libft/libft.a
CC = cc
FLAG = -Wall -Werror -Wextra -g3
LD_FLAGS = -lreadline -lncurses -lcurses

$(NAME): $(OBJ) $(LIBFT) $(LIB_SHELL)
	$(CC) $(FLAG) $(SRC) $(LIBFT) $(LD_FLAGS) -o $(NAME)

$(LIB_SHELL):	$(OBJ)
	ar rcs $(LIB_SHELL) $(OBJ)

all: $(NAME) $(LIB_SHELL)

$(LIBFT):
	make -C ./libft

clean:
	rm -rf $(OBJ)
	make -C ./libft clean
	
fclean: clean
	rm -f $(NAME)
	rm -f $(LIB_SHELL)
	make -C ./libft fclean

re: fclean all              