/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:57:49 by lomasse           #+#    #+#             */
/*   Updated: 2019/04/11 17:31:23 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	init_input(t_win **wn)
{
	if (!((*wn)->input = malloc(sizeof(t_input))))
		stop_exec("malloc inputfailed\n", *wn);
}