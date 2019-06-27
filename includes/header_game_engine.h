/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_game_engine.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 12:53:25 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/27 17:07:10 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <jeronemo.h>

//FILE GAME ENGINE
void	ft_launch_rasterization(t_mywin *s_win, t_win *wn);
void	ft_apply_modif(t_mywin *s_win, t_mychange *change, t_mykeep *keep, t_mytriangle *triangle_array);
void	ft_init_rasterization(t_mykeep *keep, t_mychange *change, t_myraster raster);
void		ft_update_raster(t_mywin *s_win, t_mytriangle *triangle_array);

//FILE USER INPUT
void	ft_input_event_check(t_win *wn, t_mychange *change);


//FILE GET TRINAGLES
t_mytriangle	*ft_get_triangles_array(t_mywin *s_win);

//FILE ITOA COMMA
char	*ft_itoa_comma(float nbr);
