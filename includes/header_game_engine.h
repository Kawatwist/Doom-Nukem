/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_game_engine.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 12:53:25 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/09 12:47:27 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <doom.h>

typedef struct				s_myraster
{
	float					ftheta;
	float					theta_camera;
	float					pitch; // l'angle pour l'axis y
	float					**mat_trans;
	float					**mat_rot_x;
	float					**mat_rot_y;
	float					**mat_rot_z;
	float					**mat_proje;
	t_myvec					v_camera;
	t_myvec					v_target;
	t_myvec					v_up;
	t_myvec					v_right;
	t_myvec					forward;
	t_myvec					v_look_dir;
	float					**mat_camera_rot;
	float					**mat_camera_look_at;
	float					**mat_camera_view;
	unsigned char			avancer;
	unsigned char			reculer;
	unsigned char			translate_left;
	unsigned char			translate_right;
	unsigned char			leave_mouse;
	unsigned char			modif;
	unsigned char			quit;
	Uint8					*old;
}							t_myraster;


//FILE GAME ENGINE
void			ft_launch_rasterization(t_win *wn);
/* void			ft_apply_modif(t_mywin *s_win, t_mytriangle *triangle_array); */
void			ft_init_rasterization(t_win *wn, t_myraster *raster);
void			ft_update_raster(t_myraster *raster, t_mytriangle *triangle_array, int max, t_win *wn);
//int				ft_get_nbr_of_triangle(t_mywin *s_win);
int				ft_get_nbr_of_triangle(t_mypolygon *polygon_lst);
void			ft_draw_triangle_base(t_myvec *v1, t_myvec *v2, t_myvec *v3, t_win *wn);
int				ft_triangle_clips_again_plan(t_myvec point, t_myvec plane_norm, t_mytriangle *clipped_triangle, t_mytriangle *triangle);

//FILE USER INPUT
void			ft_input_event_check(t_win *wn, t_myraster *raster);
void			ft_mouse_evnet_check(t_win *wn, t_myraster *raster);
//FILE GET TRINAGLES
t_mytriangle	*ft_get_triangle(void);
t_mytriangle	*ft_get_triangles_array(t_mypolygon *polygon_lst);

//FILE ITOA COMMA
char			*ft_itoa_comma(float nbr);

//FILE MATRIX TOOL
t_myvec			ft_scale_screen(t_myvec result);
float			ft_rad(float angle);

float			**ft_make_matrix_5_5(void);
void			ft_set_raster_trans(float x, float y, float z, t_myraster *raster);
void			ft_set_raster_rot_x(float theta, t_myraster *raster);
void			ft_set_raster_rot_y(float theta, t_myraster *raster);
void			ft_set_raster_rot_z(float theta, t_myraster *raster);
void			ft_set_pro(t_myraster *raster);
float			**ft_matrix_multiply_matrix(float **m1, float **m2);
float			**ft_make_identity(void);
float			**ft_make_rotation_y(float theta);
float			**ft_matrix_quick_inverse(float **mu);
float			**t_camera_compute_view(t_myraster *raster); //calcul de la matrice de vue

//FILE VECTOR TOOL
t_myvec			ft_normalise(t_myvec vector);
t_myvec			ft_vector_sub(t_myvec v2, t_myvec v1);
t_myvec			ft_matrix_multiply_vector(float **m, t_myvec i);
t_myvec			ft_matrix_multiply_vector_general(float **matrix, t_myvec v);
t_myvec			ft_vector_add(t_myvec v1, t_myvec v2);
t_myvec			ft_vector_multiply(t_myvec m, float k);
t_myvec			ft_create_vector(float p_x, float p_y, float p_z);
t_myvec			ft_vector_inverse(t_myvec src);
t_myvec			ft_vector_multiply_vector(t_myvec a, t_myvec b);

//FILE FILL TRIANGLE
void			ft_fill_triangle_shade(t_myvec v1, t_myvec v2, t_myvec v3, t_win *wn, float shade);

//file window
void						ft_clear_window(t_win *wn);

//file apply calcul
t_mytriangle	ft_apply_calucul(t_myvec function(float**, t_myvec), t_mytriangle triangle, float **matrix);


