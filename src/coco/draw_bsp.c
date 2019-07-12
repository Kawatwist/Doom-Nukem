#include <bsp.h>
#include <doom.h>

t_poly *visible_polygons(t_bsp *bsp, int leaf)
{
	t_vp vp;

	//printf("VISIBLE POLY\n");
	vp.pointer = bsp->pvs + bsp->leaf[leaf].pvs_index;
	vp.curr_leaf = 0;
	vp.list = NULL;
	while (vp.curr_leaf < bsp->nb_leafs)
	{
		//printf("CURRLEAF %d\n", vp.curr_leaf);
		if (*vp.pointer != 0)
		{
			vp.i = 0;
			while (vp.i < 8)
			{
				//printf("VP.I %d\n", vp.i);
				vp.mask = 1 << vp.i;
				vp.pvs = *vp.pointer;
				if (vp.pvs & vp.mask)
				{
					vp.start = bsp->leaf[vp.curr_leaf].start_poly;
					vp.finish = bsp->leaf[vp.curr_leaf].end_poly;
					vp.count = vp.start;
					while (vp.count < vp.finish)
					{
						//printf("CHECK VPCOUNT %d\n", vp.count);
						vp.curr = &bsp->poly[vp.count];
						if (vp.list == NULL)
						{
							vp.curr->next = NULL;
							vp.list = vp.curr;
						}
						else
						{
							vp.curr->next = vp.list;
							vp.list = vp.curr;
						}
						vp.count++;
					}
				}
				vp.curr_leaf++;
				vp.i++;
			}
			vp.pointer++;
		}
		else
		{
			vp.pointer++;
			vp.count = *vp.pointer;
			vp.pointer++;
			vp.curr_leaf += vp.count * 8;
		}
	}
	return (vp.list);
}

t_poly *render_bsp(t_bsp *bsp, t_vec *pos)
{
	int node;
	int leaf;
	int result;
	//t_poly *list;

	node = 0;
	leaf = 0;
	//printf("RENDER\n");
	while(1)
	{
		result = class_point(pos, &(bsp->plane[bsp->node[node].plane]));
		//printf("RESULT %d\n", result);
		if (result == 1 || result == 0)
		{
			if (bsp->node[node].isleaf == 1)
			{
				leaf = bsp->node[node].front;
				return (visible_polygons(bsp, leaf));
			}
			else
				node = bsp->node[node].front;
			//break;
		}
		if (result == -1)
		{
			if (bsp->node[node].back == -1)
				return (NULL);
			else
				node = bsp->node[node].back;
			//break;
		}
	}
	return (NULL);
}

t_mytriangle *make_triangles(t_poly *list, int *max)
{
	t_poly		 *tmp;
	t_mytriangle *res;
	t_poly *poly;
	int i;
	int j;

	printf("MAKIng TRIANGLES\n");
	tmp = list;
	*max = 0;
	while(tmp != NULL)
	{
		poly = tmp;
		i = 0;
		while((i * 3) < poly->nb_indices)
			i++;
		*max += i;
		tmp = tmp->next;
	}
	if (!(res = (t_mytriangle*)malloc(sizeof(t_mytriangle) * (*max))))
		exit(0);
	printf("MAX %d\n", *max );
	j = 0;
	while(list != NULL)
	{
		poly = list;
		i = 0;
		while((i * 3) < poly->nb_indices)
		{
			res[j].vertice[0].x = poly->ver_list[poly->indices[i * 3]].x;
			res[j].vertice[0].y = poly->ver_list[poly->indices[i * 3]].y;
			res[j].vertice[0].z = poly->ver_list[poly->indices[i * 3]].z;
			res[j].vertice[1].x = poly->ver_list[poly->indices[(i * 3) + 1]].x;
			res[j].vertice[1].y = poly->ver_list[poly->indices[(i * 3) + 1]].y;
			res[j].vertice[1].z = poly->ver_list[poly->indices[(i * 3) + 1]].z;
			res[j].vertice[2].x = poly->ver_list[poly->indices[(i * 3) + 2]].x;
			res[j].vertice[2].y = poly->ver_list[poly->indices[(i * 3) + 2]].y;
			res[j].vertice[2].z = poly->ver_list[poly->indices[(i * 3) + 2]].z;
		/**	new->vertice[i].x = poly->ver_list[poly->indices[i * 3]].x;
			new->vertice[i].y = poly->ver_list[poly->indices[i * 3]].y;
			new->vertice[i].z = poly->ver_list[poly->indices[i * 3]].z;
			new->vertice[i + 1].x = poly->ver_list[poly->indices[(i * 3) + 1]].x;
			new->vertice[i + 1].y = poly->ver_list[poly->indices[(i * 3) + 1]].y;
			new->vertice[i + 1].z = poly->ver_list[poly->indices[(i * 3) + 1]].z;
			new->vertice[i + 2].x = poly->ver_list[poly->indices[(i * 3) + 2]].x;
			new->vertice[i + 2].y = poly->ver_list[poly->indices[(i * 3) + 2]].y;
			new->vertice[i + 2].z = poly->ver_list[poly->indices[(i * 3) + 2]].z; **/
			j++;
			i++;
		}
		//printf("TRIANGLE\n");
		list = list->next;
	}
	i = 0;
	printf("TRIANGLE LIST\n");
	while (i < *max)
	{
		printf("Triangle: %f %f %f ; %f %f %f ; %f %f %f\n", res[i].vertice[0].x, res[i].vertice[0].y, res[i].vertice[0].z,
				res[i].vertice[1].x, res[i].vertice[1].y, res[i].vertice[1].z,
				res[i].vertice[2].x, res[i].vertice[2].y, res[i].vertice[2].z);
		i++;
	}
	return (res);
}
