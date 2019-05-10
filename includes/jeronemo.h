/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jeronemo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:37:05 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/10 08:35:17 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef JERONEMO_H
# define JERONEMO_H

# include <SDL_ttf.h>

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

typedef				s_mygrid
{
	int				x;
	int				y;
	int				height;
	int				width;
	int				nbr_dot_height;
	int				nbr_dot_width;
}					t_mygrid;

typedef enum		e_window
{
	J_EDITOR,
}					t_window;

#endif
