NAME		= fractol

FLAGS		= -Wall -Wextra -Werror -Ofast
INCL		= -I. -I./mlx -I./libft
LIB			= -L./libft -lft -L./mlx -lmlx -framework OpenGL -framework AppKit

SRCS		= $(addprefix srcs/,	\
			  main.c				\
			  draw.c				\
			  mouse.c				\
			  color.c				\
			  fractals.c			\
			  keyboard.c)



all :		$(NAME)

$(NAME) :	libft.a libmlx.a
	gcc $(FLAGS) $(INCL) $(LIB) $(SRCS) -o $(NAME)

libft.a :
	make -C ./libft

libmlx.a :
	make -C ./mlx

clean :
	make fclean -C ./libft
	make clean -C ./mlx
	rm $(NAME)

fclean :	clean

re :		fclean all

.PHONY :	re all clean fclean
