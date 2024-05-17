/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mman <mman@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:34:58 by mman              #+#    #+#             */
/*   Updated: 2024/05/17 20:32:04 by mman             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_STRUCT_H
# define MLX_STRUCT_H

# include "miniRT.h"
# include "minilibx/mlx.h"

typedef struct s_mlxdata
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}			t_mlxdata;

void	ft_error_check(char *string);
int		ft_mlx_init(t_mlxdata *mlxdata, char *argv[]);
void	ft_process_other_keys(int keycode, t_mlxdata *mlxdata);
int		ft_key_hook(int keycode, t_mlxdata *mlxdata);
void	ft_cleanup_all(t_mlxdata *mlxdata);
int		ft_close_window_event(t_mlxdata *mlxdata);
int		ft_mouse_hook(int button, int x, int y, t_mlxdata *mlxdata);
void	setup_event_hooks(t_mlxdata *mlxdata);

#endif
