/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jeronemo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:37:05 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/15 17:15:43 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef JERONEMO_H
# define JERONEMO_H

# include <SDL_ttf.h>


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

typedef struct		s_mypoint
{
	int				x;
	int				y;
	int				set;
}					t_mypoint;

typedef struct		s_mycolor
{
	int				rrr;
	int				ggg;
	int				bbb;
}					t_mycolor;

typedef struct		s_mylocalisation_box
{
	int				x;
	int				y;
	int				width;
	int				height;
}					t_mylocalisation_box;


typedef struct		s_mysquare
{
	int						x;
	int				y;
	int				width;
	int				height;
	t_mycolor		color;
}					t_mysquare;

typedef struct		s_mywrite
{
	t_mycolor		color;
	TTF_Font		*font;
	int				x;
	int				y;
	char			*str;
}					t_mywrite;

typedef struct		s_mywall
{
	int				x_a;
	int				y_a;
	int				x_b;
	int				y_b;
	int				height;
	int				texture;
	void			*next;
}					t_mywall;

typedef struct		s_mycross
{
	int				x;
	int				y;
	int				size;
	int				thickness;
	t_mycolor		color;
}					t_mycross;

typedef struct		s_mygrid
{
	int				x;
	int				y;
	int				height;
	int				width;
	int				nbr_dot_height;
	int				nbr_dot_width;
	int				step;
}					t_mygrid;

typedef struct			s_xyz_point
{
	double				a;
	double				b;
}						t_xyz_point;

typedef struct			s_myputtheline
{
	int					above;
	t_xyz_point			un;
	t_xyz_point			deux;
	int					ex;
	int					ey;
	int					dx;
	int					dy;
	int					d_x;
	int					d_y;
	int					i;
	int					j;
	int					x_incr;
	int					y_incr;
	float				ab;
	float				le_z1;
	float				le_z2;
}						t_myputtheline;

typedef struct			s_mycurrent_wall
{
	t_mypoint			first_point;
	t_mypoint			seconde_point;
}						t_mycurrent_wall;

typedef struct				s_mywin
{
	SDL_Window				*window[3];
	SDL_Renderer			*renderer[3];
	t_mylocalisation_box	*s_localisation_box;
	t_mysquare				*s_localisation_quit_button;
	t_mysquare				*s_localisation_save_button;
	int						show_cross[5];
	t_mysquare				***s_localisation_color_box;
	t_mygrid				*s_localisation_grid;
	t_mywall				*lst_wall;
	t_mycurrent_wall		current_wall;
}							t_mywin;

typedef enum		e_window
{
	J_EDITOR,
}					t_window;

void			ft_draw_line(t_mywin *s_win, t_myputtheline *s_line);
void			ft_draw_square(t_mywin *s_win, t_mysquare *s_square);
void			ft_launch_window(t_mywin *s_win);
t_mysquare		ft_setsquare(int x, int  y, int  width, int  height, t_mycolor s_color );
t_mycolor		ft_setcolor(int rrr, int ggg, int bbb);
void			ft_draw_cross(t_mywin *s_win, t_mycross *s_cross);
t_mycross		ft_setcross(int x, int y, int size, int thickness, t_mycolor color);
t_mywrite		ft_setwrite(int x, int y, t_mycolor color, int size, char *str);
void			ft_write(t_mywin *s_win, t_mywrite *s_write);
t_mygrid		ft_setgrid(int x, int y, int width, int height, int step);
void			ft_draw_grid(t_mywin *s_win, t_mygrid *s_grid);
t_mypoint		ft_setpoint(int x, int y);
t_mywall		ft_setwall(t_mypoint a, t_mypoint b, int height, int texture);
void			ft_draw_wall(t_mywin *s_win, t_mywall *s_wall);
void			ft_display_ihc(t_mywin *s_win);
t_mywall		*ft_read_map(void);
void			ft_quit(char *txt, t_mywin *s_win);
void			ft_save_map(t_mywin *s_win);
t_mywall		*ft_create_wall_node(t_mywall wall);
void			ft_add_wall_node(t_mywall **lst_wall, t_mywall *s_wall);



#endif
