#######################################################
## ARGUMENTS

NAME = minishell
BONUS = minishell_bonus

CC = cc
RM = rm -rf
FLAGS = -Wall -Wextra -Werror -g3
RL_FLAGS = -lreadline
DEP_FLAGS = -MMD -MP

#######################################################
## SOURCES

SRCS_FILES = minishell.c \

LIB_SRCS_FILES = \

SRCS_DIR = ./srcs
LIB_DIR = ./srcs/lib
OBJS_DIR = ./objs

SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
LIB_SRCS = $(addprefix $(LIB_DIR)/, $(LIB_SRCS_FILES))

OBJECTS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o)) $(addprefix $(OBJS_DIR)/, $(LIB_SRCS:.c=.o))

BONUS_SRCS_FILES =  \

BONUS_SRCS_DIR = ./srcs_bonus
BONUS_SRCS = $(addprefix $(BONUS_SRCS_DIR)/, $(BONUS_SRCS_FILES))
BONUS_OBJECTS = $(addprefix $(OBJS_DIR)/, $(BONUS_SRCS:.c=.o))

DEP = $(OBJECTS:.o=.d) $(BONUS_OBJECTS:.o=.d)


#######################################################
## RULES

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) $(RL_FLAGS) -o $@

$(BONUS): $(BONUS_OBJECTS)
	$(CC) $(FLAGS) $(BONUS_OBJECTS) $(RL_FLAGS) -o $@

bonus: $(BONUS)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)/$(SRCS_DIR)
	@mkdir -p $(OBJS_DIR)/$(LIB_DIR)

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	@mkdir -p $(dir $@) 
	$(CC) $(FLAGS) $(DEP_FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(BONUS_OBJECTS) $(DEP)

fclean: clean
	$(RM) $(NAME) $(BONUS)

re: fclean all

re_bonus: fclean bonus

-include $(DEP)

.PHONY: all bonus clean fclean re re_bonus
