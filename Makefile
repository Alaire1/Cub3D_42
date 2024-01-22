HEADER			=	includes/cub3d.h
NAME			=	cub3d
FILES			=	utils/getting_current_time.c\
					utils/getting_distances.c\
					utils/exiting_game.c\
					utils/radian_calculations.c\
					parsing/check_input_validity.c \
					parsing/copy_map_info.c\
					parsing/parse_map.c\
					parsing/import_map.c \
					player/getting_player_position.c\
					player/player_movements.c\
					rendering/ft_get_hit_wall.c\
					rendering/rendering_frames.c\
					rendering/rendering_3d_scenes.c\
					rendering/drawing_floor_and_ceilling.c \
					main.c
SRCS_DIR		=	srcs/
SRCS			=	$(addprefix $(SRCS_DIR), $(FILES))
OBJS_DIR		=	objs/
OBJS			=	$(patsubst %.c, %.o, $(addprefix $(OBJS_DIR), $(FILES)))
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
LIBFT_DIR		=	./Libft
LIBFT			=	$(LIBFT_DIR)/libft.a
LIBFT_IFLAGS	=	-ILibft
MLX_DIR		=	mlx
MLX			=	$(MLX_DIR)/libmlx.a
MLX_IFLAGS	=	-Imlx_macos
MLX_LFLAGS	=	-framework OpenGL -framework AppKit

$(OBJS_DIR)%.o:$(SRCS_DIR)%.c				$(HEADER)
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) $(LIBFT_IFLAGS) $(MLX_IFLAGS) -c $< -o $@

$(NAME):	$(HEADER) $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLX_LFLAGS) -o $(NAME)

all:	$(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX):
	@make -C $(MLX_DIR)

.PHONY:	all clean fclean re

clean:
	@rm -rf $(OBJS_DIR)
	@make clean -C $(LIBFT_DIR)

fclean:	clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)

re:		fclean all
