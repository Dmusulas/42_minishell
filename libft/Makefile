CC           = cc
CFLAGS       = -Wall -Wextra -Werror -g -Iinclude -Isrc
CCA = ar rc
NAME = libft.a
OBJS =	$(addprefix obj/,$(SRCS:.c=.o))
VPATH = src:incluce
SRCS =	ft_atoi.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_itoa.c\
		ft_get_next_line.c\
		ft_get_next_line_utils.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		ft_split.c\
		ft_strchr.c\
		ft_strdup.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strmapi.c\
		ft_strncmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strtrim.c\
		ft_substr.c\
		ft_tolower.c\
		ft_toupper.c\
		ft_printf.c \
		ft_convert_s.c \
		ft_convert_c.c \
		ft_convert_p.c \
		ft_convert_nums.c \
		ft_convert_d.c \
		ft_convert_ll.c \
		ft_convert_x.c \
		ft_convert_u.c \
		ft_lstadd_back.c\
		ft_lstadd_front.c\
		ft_lstclear.c\
		ft_lstdelone.c\
		ft_lstiter.c\
		ft_lstlast.c\
		ft_lstmap.c\
		ft_lstnew.c\
		ft_lstsize.c\
		ft_strnumspace.c\
		ft_strcmp.c
all: $(NAME)

obj:
	mkdir -p obj

obj/%.o: %.c | obj
		mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CCA) $(NAME) $(OBJS)

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all
