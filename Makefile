MAIN=pipex
NAME=libft.a
CC=gcc
CCFLAGS=-Wall -Wextra -Werror
MAINSRC=srcs/main.c srcs/mandatory.c
SRCS = ft_atoi.c \
       ft_bzero.c \
	ft_calloc.c \
       ft_itoa.c \
       ft_isalnum.c \
       ft_isalpha.c \
       ft_isascii.c \
       ft_isdigit.c \
       ft_isprint.c \
       ft_memchr.c \
       ft_memcmp.c \
       ft_memcpy.c \
       ft_memmove.c \
       ft_memset.c \
       ft_putchar_fd.c \
       ft_putendl_fd.c \
       ft_putnbr_fd.c \
       ft_putstr_fd.c \
       ft_split.c \
       ft_strchr.c \
       ft_strdup.c \
       ft_strjoin.c \
       ft_strlcat.c \
       ft_strlcpy.c \
       ft_strlen.c \
       ft_strmapi.c \
       ft_strncmp.c \
       ft_strnstr.c \
       ft_strrchr.c \
       ft_strtrim.c \
       ft_substr.c \
       ft_tolower.c \
       ft_toupper.c \
       ft_striteri.c \
       #pipex_utils.c

BONUS_SRCS = ft_lstadd_back.c \
	   ft_lstadd_front.c \
	   ft_lstclear.c \
	   ft_lstdelone.c \
	   ft_lstiter.c \
	   ft_lstlast.c \
	   ft_lstmap.c \
	   ft_lstnew.c \
	   ft_lstsize.c \

OBJS = libft/ft_atoi.o \
       libft/ft_bzero.o \
	libft/ft_calloc.o \
       libft/ft_itoa.o \
       libft/ft_isalnum.o \
       libft/ft_isalpha.o \
       libft/ft_isascii.o \
       libft/ft_isdigit.o \
       libft/ft_isprint.o \
       libft/ft_memchr.o \
       libft/ft_memcmp.o \
       libft/ft_memcpy.o \
       libft/ft_memmove.o \
       libft/ft_memset.o \
       libft/ft_putchar_fd.o \
       libft/ft_putendl_fd.o \
       libft/ft_putnbr_fd.o \
       libft/ft_putstr_fd.o \
       libft/ft_split.o \
       libft/ft_strchr.o \
       libft/ft_strdup.o \
       libft/ft_strjoin.o \
       libft/ft_strlcat.o \
       libft/ft_strlcpy.o \
       libft/ft_strlen.o \
       libft/ft_strmapi.o \
       libft/ft_strncmp.o \
       libft/ft_strnstr.o \
       libft/ft_strrchr.o \
       libft/ft_strtrim.o \
       libft/ft_substr.o \
       libft/ft_tolower.o \
       libft/ft_toupper.o \
       libft/ft_striteri.o \
       #libft/pipex_utils.o \

BONUS_OBJS = ft_lstadd_back.o \
	   ft_lstadd_front.o \
	   ft_lstclear.o \
	   ft_lstdelone.o \
	   ft_lstiter.o \
	   ft_lstlast.o \
	   ft_lstmap.o \
	   ft_lstnew.o \
	   ft_lstsize.o \

RM = rm -rf

.c.o:	
			${CC} ${CCFLAGS} -c $<

all:		${MAIN}
              
$(MAIN):	${NAME}
			${CC} ${CCFLAGS} $(MAINSRC) $(NAME) -o $(MAIN)

$(NAME):	${OBJS}
			ar rcs ${NAME} ${SRCS:.c=.o}

bonus: 		${OBJS} ${BONUS_OBJS}
			ar rcs ${NAME} ${OBJS} ${BONUS_OBJS}

clean:
			${RM} ${SRCS:.c=.o} ${BONUS_OBJS}

fclean:		clean
			${RM} ${NAME} $(MAIN)

re:			fclean all
