/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jeronemo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:37:05 by jchardin          #+#    #+#             */
/*   Updated: 2019/05/08 18:02:13 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef JERONEMO_H
# define JERONEMO_H


typedef struct		s_my_win
{
	SDL_Window		*window[3];
	SDL_Renderer	*renderer[3];
}					t_my_win;

typedef enum		e_window
{
	J_EDITOR,
}					t_window;

#endif
