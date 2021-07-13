#include "minilibx/include/mlx.h"
#include "fdf.h"
#include "libft1/libft.h"
#include "get_next_line/get_next_line.h"
#include <math.h>

int main(void)
{
	void *mlx_ptr;
	void *win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "fdf");
	mlx_loop(win_ptr);
}