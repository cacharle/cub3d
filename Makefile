# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cacharle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/05 01:34:15 by cacharle          #+#    #+#              #
#    Updated: 2020/02/05 01:34:18 by cacharle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_PATH = ./libft
MINILIBX_PATH = ./minilibx

SRCDIR = src
INCLUDEDIR = include
OBJDIR = obj

CC = gcc
CCFLAGS = -I$(LIBFT_PATH) -I$(MINILIBX_PATH) -I$(INCLUDEDIR) \
		  -Wall -Wextra -Werror
LDFLAGS = -L$(LIBFT_PATH) -lft \
		  -L$(MINILIBX_PATH) -lmlx \
		  -lm -lXext -lX11 -lbsd

NAME = cub3D
SRCFILES = main.c \
		   parse/parse.c \
		   parse/parse_file.c \
		   parse/parse_textures.c \
		   parse/parse_color.c \
		   parse/parse_resolution.c \
		   parse/parse_check.c \
		   event.c \
		   state.c \
		   vector.c \
		   render.c \
		   render_state.c \
		   helper.c \
		   error.c \
		   capture.c \
		   texture.c \
		   render_sprite.c \
		   sprite_sort.c
SRC = $(addprefix $(SRCDIR)/,$(SRCFILES))
$(info $(SRC))
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
$(info $(OBJ))
INCLUDE = $(addprefix $(INCLUDEDIR), cub3d.h)

all: make_obj_dir libft_all minilibx_all $(NAME)

make_obj_dir:
	@if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi
	@if [ ! -d $(OBJDIR)/parse ]; then mkdir $(OBJDIR)/parse; fi

$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CCFLAGS) -c -o $@ $<

clean: libft_clean minilibx_clean
	rm -f $(OBJ)

fclean: clean libft_fclean
	rm -f $(NAME)

re: fclean all

bonus: all

libft_all:
	make -C $(LIBFT_PATH) all

libft_clean:
	make -C $(LIBFT_PATH) clean

libft_fclean:
	make -C $(LIBFT_PATH) fclean

minilibx_all:
	make -C $(MINILIBX_PATH) all

minilibx_clean:
	make -C $(MINILIBX_PATH) clean
