/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterisation.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 10:07:08 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/17 17:01:53 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RASTERISATION_H
# define RASTERISATION_H

#include "doom.h"

typedef struct		s_vec
{
	float			x;
	float			y;
	float			z;
	int				tx;
	int				ty;
}					t_vec;

typedef struct		s_poly
{
	t_vec			*ver_list;
	t_vec			normal;
	int				nb_ver;
	int				nb_indices;
	int				*indices;
	struct s_poly	*next;
	char			was_splitter;
	int				texture;
}					t_poly;

#endif
