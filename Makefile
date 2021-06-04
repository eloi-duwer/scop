SRC_NAME = main.c \
	helpers.c \
	load_shaders.c \
	matrix/matrix.c \
	matrix/matrix_operations.c \
	matrix/rotation_matrix.c \
	obj_load/load_object.c \
	obj_load/parse_object.c \
	obj_load/reconstruct_index_object.c \
	print_funcs.c \
	event_handling.c \
	load_bmp.c \
	load_opengl_funcs.c \
	skybox.c \
	render.c

NAME = scop

CC = clang

CFLAGS = -Wall -Wextra -Wno-unused-parameter -g -I./include `pkg-config --cflags gtk+-3.0` -I./libft/include

SRCF = ./src/

OBJF = ./obj/

OBJS = $(addprefix $(OBJF), $(SRC_NAME:.c=.o))

DEPS = $(OBJS:%.o=%.d)

LFT = libft/libft.a

all: $(NAME)

$(NAME): $(LFT) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -g `pkg-config --libs gtk+-3.0` -lGL -lm -lpthread -L./libft -lft -ldl

$(LFT):
	make -C ./libft

-include $(DEPS)

$(OBJF)%.o: $(SRCF)%.c
	@mkdir -p $(@D)
	$(CC) -o $@ $(CFLAGS) -MMD -c $(addprefix $(SRCF), $*.c)

clean:
	rm -rf $(OBJS) $(DEPS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

gtk:
	cd gtk && tar -xf gtk+-3.24.29.tar.xz && cd gtk+-3.24.29 && ./configure && sudo make && sudo make install

.PHONY: gtk