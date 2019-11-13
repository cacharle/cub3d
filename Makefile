LIBFT_PATH = ./libft

CC = gcc
CCFLAGS = -I$(LIBFT_PATH) -Wall -Wextra #-Werror
LDFLAGS = -L$(LIBFT_PATH) -lft

NAME = cub3D
SRC = main.c
OBJ = $(SRC:.c=.o)
INCLUDE = cub3d.h

all: libft_all $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<

clean: libft_clean
	rm -f $(OBJ)

fclean: clean libft_fclean
	rm -f $(NAME)

re: fclean libft_fclean all

libft_all:
	make -C $(LIBFT_PATH) all

libft_clean:
	make -C $(LIBFT_PATH) clean

libft_fclean:
	make -C $(LIBFT_PATH) fclean
