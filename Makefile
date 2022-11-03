NAME	:= so_long
CC		?= gcc
CFLAGS	:= -Wall -Werror -Wextra
LINKFLAGS := -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit MLX42/libmlx42.a
INCLUDEFLAGS := -I ./MLX42/include/MLX42 \
 				-I ./include \
				-I ./LIBFT

CFILES		:=	main.c \
				make_map.c \
				map_validation.c \
				sprites.c \
				movement.c \
				utils.c \

OBJ_DIR		:=	objects/
SRC_DIR		:=	sources/
SRCS		:=	$(addprefix $(SRC_DIR), $(CFILES))
OFILES		:=	$(CFILES:.c=.o)
OBJS		:=	$(addprefix $(OBJ_DIR), $(OFILES))
HEADER		:=	include/so_long.h
LIBFT		:= LIBFT/libft.a

$(NAME): $(OBJ_DIR) $(OBJS) $(SRCS) $(LIBFT)
	@$(CC) $(OBJS) $(CFLAGS) $(LINKFLAGS) $(LIBFT) $(INCLUDEFLAGS) -o $(NAME)
	@printf "\033[0;33m So_long \033[0;32mCompiled \033[0m:)\n"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER) | $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) $< -o $@ $(INCLUDEFLAGS) && printf " \033[0;36mCompiling: $(notdir $<)\n\033[0m"


all: $(NAME)

debug: $(OBJ_DIR) $(OBJS) $(SRCS) $(LIBFT)
	$(CC) $(OBJS) -ggdb3 $(LINKFLAGS) $(LIBFT) $(INCLUDEFLAGS) -o $(NAME)

run: $(NAME) $(OBJS) $(SRCS)
	./$(NAME) maps/map_0.ber
	./$(NAME) maps/map_long.ber

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

mlx:
	git clone https://github.com/codam-coding-college/MLX42.git
	make -C MLX42/

libft:
	@make -C LIBFT/

clean:
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, mlx, libft

.DEFAULT_GOAL := $(NAME)