NAME = minishell

OBJ_DIR = obj
SRC_DIR = srcs

SRC = $(SRC_DIR)/fonction.c $(SRC_DIR)/main.c $(SRC_DIR)/init_node.c \
      $(SRC_DIR)/tokenisation.c $(SRC_DIR)/verif_line.c $(SRC_DIR)/automate.c \
      $(SRC_DIR)/here_doc.c $(SRC_DIR)/find_var.c $(SRC_DIR)/sort_cmds.c \
      $(SRC_DIR)/init_tcmds.c $(SRC_DIR)/sort_cmds_utils.c $(SRC_DIR)/free.c \
      $(SRC_DIR)/init_t_redir.c $(SRC_DIR)/expandornot.c $(SRC_DIR)/init_expand.c \
      $(SRC_DIR)/get_env.c $(SRC_DIR)/get_final_line.c $(SRC_DIR)/mallocs.c \
      $(SRC_DIR)/init.c $(SRC_DIR)/ft_error.c $(SRC_DIR)/token_utils.c \
      $(SRC_DIR)/token_utils2.c $(SRC_DIR)/utils.c $(SRC_DIR)/init_env.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

DEPS = $(OBJ:.o=.d)

LIBFT = ./libft/libft.a

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
LD_FLAGS = -lreadline -lncurses -lcurses

LIB_SHELL = minishell.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(LIB_SHELL)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LD_FLAGS) -o $(NAME)

$(LIB_SHELL): $(OBJ)
	ar rcs $(LIB_SHELL) $(OBJ)

-include $(DEPS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	make -C ./libft

clean:
	rm -rf $(OBJ_DIR)
	make -C ./libft clean
	
fclean: clean
	rm -f $(NAME)
	rm -f $(LIB_SHELL)
	make -C ./libft fclean

re: fclean all
