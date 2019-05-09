/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jeronemo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:37:05 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/09 12:08:17 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef JERONEMO_H
# define JERONEMO_H

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

typedef struct		s_mycross
{
	int				x;
	int				y;
	int				size;
	int				thickness;
	t_mycolor		color;
}					t_mycross;

typedef enum		e_window
{
	J_EDITOR,
}					t_window;


#endif
