/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:22:06 by lomasse           #+#    #+#             */
/*   Updated: 2019/04/12 17:16:40 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../SDL2-2.0.9/include/SDL.h"

typedef struct s_cloud
{
	SDL_Texture *txt;
	struct s_cloud *next;
}				t_cloud;

typedef struct s_skybox
{
	
}				t_skybox;				
