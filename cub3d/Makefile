# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lsmit <lsmit@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/24 11:54:55 by lsmit          #+#    #+#                 #
#    Updated: 2020/03/12 12:05:31 by lsmit         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = src/cub3d.c src/get_next_line.c src/get_next_line_utils.c src/colours.c \
src/movement.c src/ft_split.c src/ft_errors.c src/readfile.c src/ft_parser.c \
src/readfile2.c src/ft_realloc.c src/sprite.c src/cast.c src/shadow.c \
src/subfunctions.c src/subfunctions2.c src/wallsubfunctions.c \
src/floorsubfunctions.c src/keyfunctions.c src/filereader.c src/spritecast.c \
src/playsound.c src/spritecalc2.c src/screenshot.c src/getimg.c src/points.c \
src/subfunctions3.c src/bmp.c src/readfile3.c

BONUS_SRC = src/cub3d.c src/get_next_line.c src/get_next_line_utils.c \
src/colours.c src/movement.c src/ft_errors.c src/readfile_bonus.c \
src/readfile2_bonus.c src/ft_realloc.c src/sprite.c src/cast.c src/shadow.c \
src/spritecalc2.c src/ft_parser_bonus.c src/subfunctions.c \
src/subfunctions2.c src/wallsubfunctions.c src/floorsubfunctions.c \
src/keyfunctions.c src/filereader.c src/spritecast.c src/playsound.c \
src/screenshot.c src/points.c src/getimg.c src/subfunctions3.c src/ft_split.c \
src/readfile3_bonus.c src/bmp.c src/weapon.c

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
	@$(CC) -Lmlx/ -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(BONUS_OBJ) -D BONUS=1

%.o: %.c
	@gcc $(FLAG) -Imlx -Iinc -Ilibft -c $< -o $@ -Ofast
	
clean:
	/bin/rm -f src/*.o

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f libmlx.dylib
	@cd mlx && make clean

re: fclean all