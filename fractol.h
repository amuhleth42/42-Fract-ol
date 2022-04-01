#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "mlx.h"
# include <math.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

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

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	i;
	t_view	view;
	int		iter_max;
}			t_data;

#endif
