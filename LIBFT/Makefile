# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mde-cloe <mde-cloe@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2021/12/13 18:00:17 by mde-cloe      #+#    #+#                  #
#    Updated: 2022/10/14 20:18:25 by mde-cloe      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := libft.a

HFILE := libft.h

SRCS := ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
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
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_strrev.c \
		ft_strrcmp.c \
		ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c \
		ft_printf.c \
		char_printers.c \
		hex_printers.c \
		nbr_printers.c \
		get_next_line.c \
		get_next_line_utils.c \
		get_next_line_bonus.c \
		get_next_line_utils_bonus.c \
		ft_print_map.c \
		free_map.c

OFILES := $(SRCS:.c=.o)

CFLAGS ?= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OFILES) | $(HFILE)
	@ar -rcs $@ $?
	@$(RM) $(OFILES) $(BONUS_OFILES)
	@printf "$(WHITE)\n BUILDING LIBRARY \n$(YELLOW) $@ $(GREEN)(DONE) \n"

$(OFILES): %.o: %.c
	@$(CC) -c $(CFLAGS) $^
#	@printf "$(BLUE)$@$(GREEN) (DONE) $(BLUE)\n"
bonus:
	make BONUSTIME=1
clean:
	@$(RM) $(OFILES) $(BONUS_OFILES)
	@printf "$(RED)\n FILES CLEANED\n\n"

fclean: clean
	@$(RM)	$(NAME)



re: fclean $(NAME)

.PHONY: all clean fclean re bonus

BLUE = \x1b[34;01m
GREEN = \x1b[32;01m
WHITE = \x1b[31;37m
YELLOW = \x1b[33;01m
RED = \x1b[31;01m