/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_game_engine.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 12:53:25 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/30 10:58:26 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <jeronemo.h>

typedef struct				s_myraster
{
	float					f_theta;
	float					**mat_trans;
	float					**mat_rot_x;
	float					**mat_rot_y;
	float					**mat_rot_z;
	float					**mat_proje;
	t_myvec					v_camera;
}							t_myraster;

//FILE GAME ENGINE
void	ft_launch_rasterization(t_mywin *s_win, t_win *wn);
void	ft_apply_modif(t_mywin *s_win, t_mychange *change, t_mykeep *keep, t_mytriangle *triangle_array);
void	ft_init_rasterization(t_mykeep *keep, t_mychange *change, t_myraster *raster);
void	ft_update_raster(t_mywin *s_win, t_myraster *raster, t_mytriangle *triangle_array, int max);

//FILE USER INPUT
void	ft_input_event_check(t_win *wn, t_mychange *change);

//FILE GET TRINAGLES
t_mytriangle	*ft_get_triangle(void);
t_mytriangle	*ft_get_triangles_array(t_mywin *s_win);

//FILE ITOA COMMA
char	*ft_itoa_comma(float nbr);

//FILE MATRIX TOOL
t_myvec	ft_scale_screen(t_myvec result);
float	ft_rad(float angle);

void	ft_set_raster_trans(float x, float y, float z, t_myraster *raster);
void	ft_set_raster_rot_x(float theta, t_myraster *raster);
void	ft_set_raster_rot_y(float theta, t_myraster *raster);
void	ft_set_raster_rot_z(float theta, t_myraster *raster);
void	ft_set_pro(t_myraster *raster);

//FILE VECTOR TOOL
t_myvec        ft_normalise(t_myvec vector);

//FILE FILL TRIANGLE
void	ft_fill_triangle_shade(t_myvec *v1, t_myvec *v2, t_myvec *v3, t_mywin *s_win, float shade);
