/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jeronemo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:37:05 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/10 11:34:11 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef JERONEMO_H
# define JERONEMO_H

# include <SDL_ttf.h>

typedef struct		s_mypoint
{
	int				x;
	int				y;
}					t_mypoint;

typedef struct		s_mycolor
{
	int				rrr;
	int				ggg;
	int				bbb;
}					t_mycolor;

typedef struct		s_mywin
{
	SDL_Window		*window[3];
	SDL_Renderer	*renderer[3];
}					t_mywin;

typedef struct		s_mysquare
{
	int				x;
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

typedef enum		e_window
{
	J_EDITOR,
}					t_window;

void			ft_draw_line(t_mywin *s_win, t_myputtheline *s_line);
#endif
