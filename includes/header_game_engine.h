/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_game_engine.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 12:53:25 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/04 13:21:53 by jchardin         ###   ########.fr       */
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
	t_myvec					v_up;
	t_myvec					v_target;
	float					**mat_camera_rot;
	float					**mat_camera_look_at;
	float					**mat_camera_view;
	t_myvec					v_look_dir;
	float					ftheta;
	float					theta_camera;
	unsigned char			avancer;
	unsigned char			reculer;
}							t_myraster;


typedef struct		s_camera
{
	float			**view;
	float			**projection;
	t_myvec			pos;
	float			pitch; // l'angle pour l'axis y
	float			yaw; // l'angle pour l'axis x
	t_myvec			forward;
	t_myvec			right;
	t_myvec			up;
	float			fov;
	float			near;
	float			far;
}					t_camera;

typedef struct		s_user_engine
{
	SDL_Event		event;
}					t_user_engine;

typedef struct		s_engine
{
	/* int				playing; */
	t_camera		*cam;
	t_user_engine	*user_engine;
}					t_engine;


//FILE GAME ENGINE
void	ft_launch_rasterization(t_mywin *s_win, t_win *wn);
void	ft_apply_modif(t_mywin *s_win, t_mychange *change, t_mykeep *keep, t_mytriangle *triangle_array);
void	ft_init_rasterization(t_mykeep *keep, t_mychange *change, t_myraster *raster);
void	ft_update_raster(t_mywin *s_win, t_myraster *raster, t_mytriangle *triangle_array, int max);

//FILE USER INPUT
void	ft_input_event_check(t_win *wn, t_mychange *change, t_myraster *raster);

//FILE GET TRINAGLES
t_mytriangle	*ft_get_triangle(void);
t_mytriangle	*ft_get_triangles_array(t_mywin *s_win);

//FILE ITOA COMMA
char	*ft_itoa_comma(float nbr);

//FILE MATRIX TOOL
t_myvec	ft_scale_screen(t_myvec result);
float	ft_rad(float angle);

float	**ft_make_matrix_5_5(void);
void	ft_set_raster_trans(float x, float y, float z, t_myraster *raster);
void	ft_set_raster_rot_x(float theta, t_myraster *raster);
void	ft_set_raster_rot_y(float theta, t_myraster *raster);
void	ft_set_raster_rot_z(float theta, t_myraster *raster);
void	ft_set_pro(t_myraster *raster);
float	**ft_matrix_multiply_matrix(float **m1, float **m2);
float	**ft_make_identity(void);
float	**ft_make_rotation_y(float theta);
float	**ft_matrix_point_at(t_myvec v_pos, t_myvec v_target, t_myvec v_up);
float	**ft_matrix_quick_inverse(float **mu);

//FILE VECTOR TOOL
t_myvec		ft_normalise(t_myvec vector);
t_myvec		ft_vector_sub(t_myvec v2, t_myvec v1);
t_myvec		ft_matrix_multiply_vector(float **m, t_myvec i);
t_myvec		ft_matrix_multiply_vector_general(float matrix[5][5], t_myvec v);
t_myvec		ft_vector_add(t_myvec v1, t_myvec v2);
t_myvec		ft_vector_multiply(t_myvec m, float k);
t_myvec		ft_create_vector(float p_x, float p_y, float p_z);
t_myvec		ft_vector_inverse(t_myvec src);

//FILE FILL TRIANGLE
void	ft_fill_triangle_shade(t_myvec v1, t_myvec v2, t_myvec v3, t_mywin *s_win, float shade);

//FILE MATHS DANS BSP
//dot product
//cross product
//calculate normal of point
//vector from two point

//FILE JEREM
void		compute_t_camera(t_camera *cam);
float		**t_camera_compute_view(t_camera *cam); //calcul de la matrice de vue
float		**compute_projection_matrix(t_camera *p_cam); //calcul de la matrice de projection

t_myvec		mult_vector3_by_matrix(t_myvec vertex, float **m);


