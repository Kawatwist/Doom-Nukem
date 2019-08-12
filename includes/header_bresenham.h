/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_bresenham.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 20:42:36 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/16 14:42:35 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_BRESENHAM_H
# define HEADER_BRESENHAM_H

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

#endif
