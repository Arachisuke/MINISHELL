NAME = minishell

OBJ_DIR = obj
SRC_DIR = srcs
BUILTIN_DIR = $(SRC_DIR)/builtin
EXEC_DIR = $(SRC_DIR)/exec


# Définition des sources
SRC = $(SRC_DIR)/fonction.c $(SRC_DIR)/main.c $(SRC_DIR)/init_node.c \
      $(SRC_DIR)/tokenisation.c $(SRC_DIR)/verif_line.c $(SRC_DIR)/automate.c \
      $(SRC_DIR)/here_doc.c $(SRC_DIR)/find_var.c $(SRC_DIR)/sort_cmds.c \
      $(SRC_DIR)/init_tcmds.c $(SRC_DIR)/sort_cmds_utils.c $(SRC_DIR)/free.c \
      $(SRC_DIR)/init_t_redir.c $(SRC_DIR)/expandornot.c $(SRC_DIR)/init_expand.c \
      $(SRC_DIR)/get_env.c $(SRC_DIR)/get_final_line.c $(SRC_DIR)/mallocs.c \
      $(SRC_DIR)/init.c $(SRC_DIR)/ft_error.c $(SRC_DIR)/token_utils.c \
      $(SRC_DIR)/token_utils2.c $(SRC_DIR)/utils.c $(SRC_DIR)/init_env.c \
      $(BUILTIN_DIR)/cd.c $(BUILTIN_DIR)/echo.c  $(SRC_DIR)/builtins_or_not.c \
	  $(BUILTIN_DIR)/export.c $(BUILTIN_DIR)/unset.c $(SRC_DIR)/modif_env.c $(BUILTIN_DIR)/env.c \
	  $(BUILTIN_DIR)/exit.c $(BUILTIN_DIR)/pwd.c $(EXEC_DIR)/open_and_close.c \
	  $(EXEC_DIR)/pipex_process.c $(EXEC_DIR)/pipex.c $(EXEC_DIR)/utils.c $(EXEC_DIR)/utils2.c $(SRC_DIR)/signal.c $(SRC_DIR)/removes.c 

# Génération des objets en fonction des sources (respecte les sous-dossiers)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS = $(OBJ:.o=.d)

LIBFT = ./libft/libft.a

CC = cc
# CFLAGS = -Wall -Werror -Wextra -g3
# LD_FLAGS = -lreadline -lncurses -lcurses
CFLAGS += -I/usr/local/opt/readline/include
LDFLAGS += -L/usr/local/opt/readline/lib -lreadline

LIB_SHELL = minishell.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(LIB_SHELL)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIB_SHELL): $(OBJ)
	ar rcs $(LIB_SHELL) $(OBJ)

-include $(DEPS)

# Règle de compilation pour les objets, avec création de dossiers si nécessaire
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) $(OBJ_DIR)/builtin $(OBJ_DIR)/exec
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Création des dossiers d'objets pour chaque sous-dossier
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/builtin:
	mkdir -p $(OBJ_DIR)/builtin 
$(OBJ_DIR)/exec:	
	mkdir -p $(OBJ_DIR)/exec

# Compilation de la libft
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