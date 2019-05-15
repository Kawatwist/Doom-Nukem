/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:22:06 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/11 13:15:21 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SKYBOX_H
# define SKYBOX_H

# include "SDL.h"
/*
typedef struct		s_cloud
{
	SDL_Texture		*txt;
	int				life;
	int				size;
	int			currsize;
	int				sens;
	int				tmp;
	int				flag;
	int				start;
	SDL_Rect		dst;
	struct s_cloud	*next;
}					t_cloud;
*/
typedef struct		s_cloudy
{
	char			sens;
	char			id;
	char			size;
	float			speed;
	int				ybase;
	int				xbase;
	int				life_time;
	int				life_time2;
	SDL_Rect		pos;
	struct s_cloudy	*next;
}					t_cloudy;

#endif
