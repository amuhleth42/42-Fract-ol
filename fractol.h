#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "mlx.h"
# include <math.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

# define COLOR1 0xFF2C3C
# define COLOR2 0xB166E1

# define SCROLL_UP 4
# define SCROLL_DOWN 5

enum
{
	ON_KEYDOWN = 2,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6
};

typedef struct s_z
{
	double	r;
	double	i;
}			t_z;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}			t_img;

typedef struct s_view
{
	double	xmin;
	double	xmax;
	double	ymin;
	double	ymax;
	double	zoom;
	double	offsetx;
	double	offsety;
	t_z		mouse;
}			t_view;

typedef struct s_mouse
{
	int	left_down;
	int	x;
	int	y;
	int	lastx;
	int	lasty;
}		t_mouse;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	i;
	t_view	view;
	t_mouse	mouse;
	int		iter_max;
}			t_data;

void	put_pixel_to_img(t_img *i, int x, int y, int color);

int		key_hook(int key, t_data *a);
int		mouse_down(int button, int x, int y, t_data *a);

t_z		convert_pixel_to_z(t_data *a, int x, int y);

void	mandelbrot(t_data *a, int x, int y);

void	clear_img(t_img *i);
void	fill_image(t_data *a);

void	zoom(t_data *a, int x, int y, double i);

int		get_color(int c1, int c2, float shade);

#endif
