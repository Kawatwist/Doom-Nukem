/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:45:03 by lomasse           #+#    #+#             */
/*   Updated: 2019/07/11 16:47:20 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_color	itocolor(int value)
{
	t_color	color;

	color.r = (value & 0xFF000000) >> 24;
	color.g = (value & 0xFF0000) >> 16;
	color.b = (value & 0xFF00) >> 8;
	color.a = (value & 0xFF);
	return (color);
}
