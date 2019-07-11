/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objparser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 11:29:31 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/10 11:47:41 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJPARSER_H
# define OBJPARSER_H
# include <stdlib.h>
# include "libft.h"

typedef struct		s_normal
{
}					t_normal;

typedef struct		s_point
{
	float			x;
	float			y;
	float			z;
	struct s_point	*next;
}					t_point;

typedef struct		s_poly
{
	t_point			*point;
	struct s_poly	*next;
}					t_poly;

typedef struct		s_obj
{
	t_poly			*poly; // VER LIST
	int				*indice;
	t_normal		*normal;
}					t_obj;

#endif
