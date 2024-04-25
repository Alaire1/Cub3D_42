NAME			=	cub3d

CC				=	cc
CFLAGS			=	-Wall -Wextra 

LIBFT_DIR		=	./Libft
LIBFT			=	$(LIBFT_DIR)/libft.a
LIBFT_IFLAGS	=	-ILibft

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	MLX_DIR		=	mlx_macos
	MLX			=	$(MLX_DIR)/libmlx.a
	MLX_IFLAGS	=	-Imlx_macos
	MLX_LFLAGS	=	-framework OpenGL -framework AppKit
endif
ifeq ($(UNAME_S), Linux)
	MLX_DIR		=	mlx_linux
	MLX			=	$(MLX_DIR)/libmlx.a
	MLX_IFLAGS	=	-I/usr/include -Imlx_linux -O3
	MLX_LFLAGS	=	-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
endif

HEADER			=	includes/cub3d.h

FILES			=	utils/getting_current_time.c\
                    utils/getting_distances.c\
                    utils/exiting_game.c\
                    utils/radian_calculations.c\
                    parsing/check_input_validity.c \
                    parsing/copy_map_info.c\
                    parsing/get_map_size.c\
                    parsing/import_map.c \
                    parsing/init_structs.c \
                    parsing/parse_map.c \
                    parsing/read_textures.c \
                    parsing/save_textures.c \
                    parsing/utils_1.c \
                    parsing/utils_2.c \
                    player/getting_player_position.c\
                    player/player_movements.c\
                    rendering/get_hit_wall.c\
                    rendering/rendering_frames.c\
                    rendering/rendering_3d_scenes.c\
                    rendering/drawing_floor_and_ceilling.c \
                    main.c

SRCS_DIR		=	srcs/
SRCS			=	$(addprefix $(SRCS_DIR), $(FILES))

OBJS_DIR		=	objs/
OBJS			=	$(patsubst %.c, %.o, $(addprefix $(OBJS_DIR), $(FILES)))

GREEN = \033[0;32m
RESET = \033[0m

$(OBJS_DIR)%.o:$(SRCS_DIR)%.c				$(HEADER)
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) $(LIBFT_IFLAGS) $(MLX_IFLAGS) -c $< -o $@

$(NAME):	$(HEADER) $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLX_LFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) has been created.$(RESET)"
	@echo "$(GREEN)Usage: ./cub3d <map file> $(RESET)"

all:	$(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)
		
$(MLX):
	@make -C $(MLX_DIR)

.PHONY:	all clean fclean re

clean:
	@rm -rf $(OBJS_DIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@echo "$(GREEN)$(NAME) objects have been deleted.$(RESET)"

fclean:	clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@echo "$(GREEN)$(NAME) has been deleted.$(RESET)"

re:		fclean all