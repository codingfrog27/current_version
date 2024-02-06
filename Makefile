NAME	:= so_long
CC		?= gcc
CFLAGS	:= -Wall -Werror -Wextra
LINKFLAGS := -lglfw -ldl -pthread -lm MLX42/build/libmlx42.a
INCLUDEFLAGS := -I ./MLX42/include/MLX42 \
 				-I ./include \
				-I ./LIBFT/include

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
	./$(NAME) maps/map_hoi.ber
	./$(NAME) maps/map_last.ber
	./$(NAME) maps/map_smol.ber
	./$(NAME) maps/map_tall.ber

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

mlx:
	cmake MLX42/ -B MLX42/build && make -C MLX42/build
# if [ -z "ls -A MLX42" ]; then \
# 	git clone https://github.com/codam-coding-college/MLX42.git; \
# fi

libft:
	@make -C LIBFT/

clean:
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, mlx, libft

.DEFAULT_GOAL := $(NAME)
