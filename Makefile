SRC_NAME = main.c \
	helpers.c \
	load_shaders.c \
	matrix/matrix.c \
	matrix/matrix_operations.c \
	matrix/rotation_matrix.c \
	print_funcs.c \
	open_file.c \
	event_handling.c \
	load_bmp.c \
	load_opengl_funcs.c \

NAME = scop

CC = gcc

CFLAGS = -Wall -Wextra -Wno-unused-parameter -g -I./include `pkg-config --cflags gtk+-3.0` -I./libft/include

SRCF = ./src/

OBJF = ./obj/

OBJS = $(addprefix $(OBJF), $(SRC_NAME:.c=.o))

LFT = libft/libft.a

all: $(NAME)

$(NAME): $(LFT) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -g `pkg-config --libs gtk+-3.0` -lGL -lm -lpthread -L./libft -lft -ldl

$(LFT):
	make -C ./libft

$(OBJF)%.o: $(SRCF)%.c
	@mkdir -p $(@D)
	$(CC) -o $@ $(CFLAGS) -c $(addprefix $(SRCF), $*.c)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
