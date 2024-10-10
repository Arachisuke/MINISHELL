SRCS	=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c \
		ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
		ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_calloc.c ft_strdup.c ft_atoi.c ft_substr.c ft_strjoin.c ft_strmapi.c ft_strtrim.c \
		ft_itoa.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_split.c ft_printf_fd/ft_printf_fd.c ft_printf_fd/ft_printstr.c ft_printf_fd/ft_print_unsigned.c \
		ft_printf_fd/ft_printhex.c ft_printf_fd/ft_printnbr.c ft_printf_fd/ft_printptr.c \
		ft_printf_fd/ft_printchar.c \

OBJS	=	$(SRCS:.c=.o)

BONUS	=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
		ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c \

BOBJS	=	$(BONUS:.c=.o)

CC	=	cc

RM	=	rm -f

CFLAGS	=	-Wall -Wextra -Werror -g3 -I.

NAME	=	libft.a

all:		$(NAME)

$(NAME):	$(OBJS)
	ar rcs $(NAME) $(OBJS)
	rm -rf $(OBJS)

clean:
	$(RM) $(OBJS) $(BOBJS)

fclean:		clean
	$(RM) $(NAME)

re:		fclean all

bonus:	$(OBJS) $(BOBJS)
		ar rcs $(NAME) $(OBJS) $(BOBJS)

.PHONY:		all clean fclean re bonus