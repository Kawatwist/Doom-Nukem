/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jeronemo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:37:05 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/08 20:47:19 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef JERONEMO_H
# define JERONEMO_H

# include <doom.h>
# include <SDL_ttf.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <header_bresenham.h>

#define FALSE 0
#define TRUE 1

# define WHITE 255, 255, 255
# define RED 255, 0, 0
# define GREEN 0, 255, 0
# define BLUE 0, 0, 255
# define BLACK 0, 0, 0
# define PINK 255, 0, 255
# define YELLOW 255, 255, 0
# define ORANGE 255, 128, 0
# define TURQUOISE 0, 255, 255
# define WHITE 255, 255, 255


typedef struct		s_mycolor
{
	int				rrr;
	int				ggg;
	int				bbb;
}					t_mycolor;

typedef struct	s_mytriangle
{
	t_myvec					vertice[3];
	struct s_mytriangle		*next;
	char					ft_color;
	float					shade;
}							t_mytriangle;

typedef struct			s_mypolygon
{
	int					obj_indice;
	t_myvec				*vertex_lst;             //liste des vertex
	t_myvec				normal;                  //la normal au polygon
	int					number_of_vertex;        //nombre de vertex
	int					number_of_indices;       //nombre d'indices
	int					*indices;                //la listes des indices apres triangulasisation
	struct s_mypolygon	*next;                   //le prochain noeud dans la liste
}						t_mypolygon;

typedef struct				s_mywin
{
	t_mypolygon				*polygon_lst;
}							t_mywin;


void			ft_clear_window(t_win *wn);
t_mycolor		ft_setcolor(int rrr, int ggg, int bbb);
void			ft_launch_rasterization(t_mywin *s_win, t_win *wn);
void			ft_launch_bsp_tree(t_mywin *s_win, t_win *wn);

float			ft_dot_product(t_myvec v1, t_myvec v2);
t_myvec			ft_cross_product(t_myvec v1, t_myvec v2);
int				ft_abs(int number);
t_myvec			ft_calculate_normal_of_points(t_myvec vertex1, t_myvec vertex2, t_myvec vertex3);
float			ft_atoi_comma(const char *str);

/* typedef enum		e_window */
/* { */
/* 	J_EDITOR = 0, */
/* 	J_BINARY_TREE = 0, */
/* }					tj_window; */

/* typedef struct		s_mywall */
/* { */
/* 	int				x_a; */
/* 	int				y_a; */
/* 	int				x_b; */
/* 	int				y_b; */
/* 	int				height; */
/* 	int				texture; */
/* 	void			*next; */
/* 	int				current_wall; */
/* }					t_mywall; */

/* typedef enum		s_myprojection */
/* { */
	/* orthographique, */
	/* perspective, */
/* }					t_myprojection; */


/* typedef struct	s_mydisplay */
/* { */
/* 	char		projection; */
/* 	char		culling_face; */
/* 	char		triangle; */
/* 	char		triangle_normal; */
/* 	char		mesh; */
/* 	char		mesh_normal; */
/* 	char		panel; */
/* 	char		color; */
/* 	char		shade; */
/* }				t_mydisplay; */


/* typedef struct		s_mylocalisation_box */
/* { */
	/* int				x; */
	/* int				y; */
	/* int				width; */
	/* int				height; */
/* }					t_mylocalisation_box; */

/* typedef enum		e_wall_height */
/* { */
	/* down = 4, */
	/* middle = 2, */
	/* up_to_ceilling = 3, */
/* }					t_wall_height; */

/* typedef enum		e_wall_texture */
/* { */
	/* file_1 = 1, */
	/* file_2 = 2, */
	/* file_3 = 3, */
/* }					t_wall_texture; */

/* typedef struct		s_mysquare */
/* { */
/* 	int						x; */
/* 	int				y; */
/* 	int				width; */
/* 	int				height; */
/* 	t_mycolor		color; */
/* }					t_mysquare; */

/* typedef struct		s_mywrite */
/* { */
/* 	t_mycolor		color; */
/* 	TTF_Font		*font; */
/* 	int				x; */
/* 	int				y; */
/* 	char			*str; */
/* }					t_mywrite; */


/* typedef struct		s_mycross */
/* { */
	/* int				x; */
	/* int				y; */
	/* int				size; */
	/* int				thickness; */
	/* t_mycolor		color; */
/* }					t_mycross; */


/* typedef struct	s_mypan */
/* { */
/* 	int				marge; */
/* 	int				marge_text; */
/* 	int				indent_text; */
/* 	int				width; */
/* 	int				height; */
/* 	int				box_width; */
/* 	int				box_height; */
/* 	int				i; */
/* 	int				j; */
/* 	t_mycolor		s_color; */
/* 	t_mysquare		s_square; */
/* 	t_mywrite		s_write; */
/* }					t_mypan; */


/* typedef struct			s_mycurrent_wall */
/* { */
/* 	t_mypoint			first_point; */
/* 	t_mypoint			seconde_point; */
/* }						t_mycurrent_wall; */


/* typedef struct				s_mynode */
/* { */
/* 	t_mywall				*wall; */
/* 	struct s_mynode				*front; */
/* 	struct s_mynode				*back; */
/* 	int						is_leaf; */
/* 	int						is_solid; */
/* }							t_mynode; */


/* typedef struct			s_mykeep */
/* { */
/* 	t_mypolygon			*polygon; */
/* 	t_myvec				*vec; */
/* }						t_mykeep; */


/* typedef struct		s_mygrid */
/* { */
/* 	int				x; */
/* 	int				y; */
/* 	int				height; */
/* 	int				width; */
/* 	int				nbr_dot_height; */
/* 	int				nbr_dot_width; */
/* 	int				step; */
/* }					t_mygrid; */



/* void			ft_draw_square(t_mywin *s_win, t_mysquare *s_square); */
/* t_mysquare	ft_setsquare(int x, int  y, int  width, int  height, t_mycolor s_color ); */
/* void			ft_draw_cross(t_mywin *s_win, t_mycross *s_cross); */
/* t_mycross	ft_setcross(int x, int y, int size, int thickness, t_mycolor color); */
/* t_mywrite	ft_setwrite(int x, int y, t_mycolor color, int size, char *str); */
/* void			ft_write(t_mywin *s_win, t_mywrite *s_write); */
/* t_mygrid		ft_setgrid(int x, int y, int width, int height, int step); */
/* void			ft_draw_grid(t_mywin *s_win, t_mygrid *s_grid); */
/* t_mypoint	ft_setpoint(int x, int y); */
/* t_mywall		ft_setwall(t_mypoint a, t_mypoint b, int height, int texture); */
/* void			ft_draw_wall(t_mywin *s_win, t_mywall *s_wall); */
/* void			ft_display_ihc(t_mywin *s_win); */
/* t_mywall		*ft_read_map(void); */
/* void			ft_save_map(t_mywin *s_win); */
/* t_mywall		*ft_create_wall_node(t_mywall wall); */
/* void			ft_add_wall_node(t_mywall **lst_wall, t_mywall *s_wall); */
/* void			ft_display_right_pan(t_mywin *s_win); */
/* void			ft_display_save_button(t_mywin *s_win); */
/* void			ft_draw_map(t_mywin *s_win); */
/* void			ft_display_quit_button(t_mywin *s_win); */
/* void			ft_display_save_button(t_mywin *s_win); */
/* void			ft_display_title(t_mywin *s_win); */
/* void			ft_display_grid(t_mywin *s_win); */
/* void			ft_display_delete_button(t_mywin *s_win); */
/* void			ft_update_show_cross(t_mywin *s_win, t_win *wn); */
/* void			ft_init_show_cross(t_mywin *s_win); */
/* void			ft_launch_map_editor(t_mywin *s_win, t_win *wn); */
/* void			ft_display_right_pan(t_mywin *s_win); */
/* t_myvec		ft_rotation_x(float angle, t_myvec vertex); */
/* t_myvec		ft_rotation_y(float angle, t_myvec vertex); */
/* t_myvec		ft_rotation_z(float angle, t_myvec vertex); */
/* t_myvec		ft_matrix_multiply(float matrix[5][5], t_myvec vertex); */
/* t_myvec		ft_translation_x(float value, t_myvec vertex); */
/* t_myvec		ft_translation_y(float value, t_myvec vertex); */
/* t_myvec		ft_translation_z(float value, t_myvec vertex); */
/* t_myvec		ft_scale(float zoom, t_myvec vertex); */
/* void			ft_draw_change(t_mywin *s_win, t_mychange *change); */
/* t_myvec		ft_normalise(t_myvec vector); */
//void			ft_mouse_event_check(t_win *wn, t_mychange *change, t_myraster *raster);
/* void			ft_display_panel(); */
/* float		**ft_make_projection(void);   //DONE */
/* float		**ft_make_rotation_x(float theta);  //DONE */
/* float		**ft_make_rotation_z(float theta); //DONE */
/* float		**ft_matrix_multiply_matrix(float **m1, float **m2);  //surement DONE */
/* float		**ft_make_matrix_5_5(void); */
/* float		**ft_make_translation(float x, float y, float z); */
/* t_myvec		ft_perspective_projection(t_myvec vertex); */
/* void			ft_get_polynome_lst(t_mywin *s_win); */
/* void			ft_display_triangle_array(t_mywin *s_win, t_mytriangle *triangle); */
/* float		ft_get_the_indice_vertex_x(int indice, t_myvec *vertex_lst); */
/* float		ft_get_the_indice_vertex_y(int indice, t_myvec *vertex_lst); */
/* float		ft_get_the_indice_vertex_z(int indice, t_myvec *vertex_lst); */
/* float		**ft_make_perspectiv(void); */
/* t_myvec		ft_scale_screen(t_myvec result); */
/* int			ft_triangle_clips_again_plan(t_myvec point, t_myvec plan, t_mytriangle *clipped_triangle, t_mytriangle *triangle, t_mywin *s_win); */
/* int			ft_calcul_culing(t_mychange *change, t_mytriangle *triangle); */

#endif
