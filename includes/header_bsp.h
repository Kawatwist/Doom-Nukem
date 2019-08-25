/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_bsp.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 12:57:02 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/09 11:09:41 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

typedef struct		s_mypoint
{
	int				x;
	int				y;
	int				set;
}					t_mypoint;

typedef struct		s_mypointf
{
	double				x;
	double				y;
}					t_mypointf;

typedef struct			s_mynode
{
	t_mypolygon			*splitter;
	struct s_mynode		*front;
	struct s_mynode		*back;
	char				is_leaf;
	char				is_solid;
}						t_mynode;

typedef enum			e_myclass
{
	FRONT,
	BACK,
	SPANNING,
	ON_PLANE,
}						t_myclass;

void			ft_build_bsp_tree(t_mynode *current_node, t_mypolygon *polygon_lst);
t_mypolygon		*ft_select_the_best_poly_splitter(t_mypolygon *polygon_lst);
void			ft_split_polygon(t_mypolygon *poly,
							t_mypolygon *plane,
							t_mypolygon *front_split,
							t_mypolygon *back_split);
void			ft_add_polygon(t_mypolygon **polygon_lst, t_mypolygon *polygon_node);
void			ft_afficher_le_bsp(t_mynode *s_node);
void			ft_display_the_polygon_list(t_mypolygon *polygon_lst);
t_mypolygon		*ft_read_the_polygon_file(void);
void			ft_process_polygon(t_mypolygon *polygon_lst);
int				ft_classify_polygon(t_mypolygon *plane, t_mypolygon *polygon_node);
int				ft_classify_point(t_myvec point, t_mypolygon *plane);
void			ft_split_polygon(t_mypolygon *poly,
							t_mypolygon *plane,
							t_mypolygon *front_split,
							t_mypolygon *back_split);
t_myvec			ft_vector_from_two_points(t_myvec v2, t_myvec v1);
void			ft_add_vertex(t_myvec **vertex_lst, t_myvec *vertex_node);
t_mypolygon		*ft_create_polygon_node(t_myvec *vertex_lst);
int				ft_calculate_number_of_indices(t_mypolygon *polygon_node);
int				*ft_calculate_indices_tab(t_mypolygon *polygon_node);

