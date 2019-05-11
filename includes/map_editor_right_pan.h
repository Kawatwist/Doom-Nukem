/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_editor_right_pan.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 10:02:29 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/11 12:05:03 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MAP_EDITOR_RIGHT_PAN_H
# define MAP_EDITOR_RIGHT_PAN_H

#include <doom.h>

typedef struct	s_mypan
{
	int				marge;
	int				marge_text;
	int				indent_text;
	int				width;
	int				height;
	int				box_width;
	int				box_height;
	int				i;
	int				j;
	t_mycolor		s_color;
	t_mysquare		s_square;
	t_mywrite		s_write;
}				t_mypan;



void	ft_display_right_pan(t_mywin *s_win);


#endif
