# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lsmit <lsmit@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/24 11:54:55 by lsmit          #+#    #+#                 #
#    Updated: 2020/02/27 14:30:54 by lsmit         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = src/cub3d.c src/get_next_line.c src/get_next_line_utils.c src/colours.c \
src/movement.c src/ft_split.c src/ft_errors.c src/readfile.c src/ft_parser.c \
src/readfile2.c src/ft_realloc.c src/sprite.c src/cast.c src/shadow.c

BONUS_SRC = src/cub3d.c src/get_next_line.c src/get_next_line_utils.c src/colours.c \
src/movement.c src/ft_split.c src/ft_errors.c src/readfile_bonus.c src/ft_parser.c \
src/readfile2_bonus.c src/ft_realloc.c src/sprite.c src/cast.c src/shadow.c

OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(BONUS_SRC:.c=.o)

FLAG = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJ)
	@cd mlx && make
	@cp mlx/libmlx.dylib .
	@$(CC) -Lmlx/ -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJ)


bonus: fclean $(BONUS_OBJ)
	@cd mlx && make
	@cp mlx/libmlx.dylib .
	@$(CC) -Lmlx/ -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(BONUS_OBJ)

%.o: %.c
	@gcc $(FLAG) -Imlx -Iinc -Ilibft -c $< -o $@ -Ofast
	
clean:
	/bin/rm -f src/*.o

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f libmlx.dylib

re: fclean all