#include <bsp.h>

void delete_portal(t_portal *portal)
{
	if (portal->prev != NULL)
		portal->prev->next = portal->next;
	if (portal->next != NULL)
		portal->next->prev = portal->prev;
	free(portal);
	portal = NULL;
	//deletes a portal, TO DO
}

void init_pclip(t_pclip *pclip)
{
	pclip->p_list = NULL;
	pclip->fp_list = NULL;
	pclip->bp_list = NULL;
	pclip->iter = NULL;
	pclip->back_split = NULL;
	pclip->front_split = NULL;
	pclip->result = 0;
}

void split_portal(t_portal *front, t_portal *back, t_portal *portal, t_plane *plane)
{
	//printf("split portal\n");
	split_poly((t_poly*)portal, plane, (t_poly*)(front), (t_poly*)(back));
	//printf("split portal 2\n");
	front->nb_leafs = portal->nb_leafs;
	back->nb_leafs = portal->nb_leafs;
	front->leafs[0] = portal->leafs[0];
	front->leafs[1] = portal->leafs[1];
	back->leafs[0] = portal->leafs[0];
	back->leafs[1] = portal->leafs[1];

	front->debug_node = portal->debug_node; //to remove
	back->debug_node = portal->debug_node; //to remove
	//printf("fin split portal\n");
}

t_portal *clip_portal(t_bsp *bsp, int node, t_portal *portal)
{
	t_pclip pclip;

	init_pclip(&pclip);
	pclip.result = class_poly(&bsp->plane[bsp->node[node].plane], (t_poly*)portal);
	if (pclip.result == 1)
	{

		if (bsp->node[node].isleaf == 0)
		{
			pclip.p_list = clip_portal(bsp, bsp->node[node].front, portal);
			return (pclip.p_list);
		}
		else
		{
			if (portal->nb_leafs > 2)
			{
				printf("PORTAL CLIP NB LEAFS >2\n"); //testing only, to remove
				exit(0);
			}
			portal->leafs[portal->nb_leafs] = bsp->node[node].front;
			portal->nb_leafs++;
			portal->next = NULL;
			portal->prev = NULL;
			return (portal);
		}
	}
	if (pclip.result == -1)
	{
		if (bsp->node[node].back != -1)
		{
			pclip.p_list = clip_portal(bsp, bsp->node[node].back, portal);
			return (pclip.p_list);
		}
		else
		{

			delete_portal(portal);
			return NULL;
		}
	}
	if (pclip.result == 2)
	{
		if (!(pclip.front_split = (t_portal*)malloc(sizeof(t_portal))))
			exit(0);
		if (!(pclip.back_split = (t_portal*)malloc(sizeof(t_portal))))
			exit(0);
		init_portal(pclip.front_split);
		init_portal(pclip.back_split);
		split_portal(pclip.front_split, pclip.back_split, portal, &bsp->plane[bsp->node[node].plane]);
		delete_portal(portal);

		if (bsp->node[node].isleaf == 0)
			pclip.fp_list = clip_portal(bsp, bsp->node[node].front, pclip.front_split);
		else
		{
			pclip.front_split->leafs[pclip.front_split->nb_leafs] = bsp->node[node].front;
			pclip.front_split->nb_leafs++;
			pclip.front_split->prev = NULL;
			pclip.front_split->next = NULL;
			pclip.fp_list = pclip.front_split;
		}
		if (bsp->node[node].back != -1)
			pclip.bp_list = clip_portal(bsp, bsp->node[node].back, pclip.back_split);
		else
			delete_portal(pclip.back_split);
		if (pclip.fp_list != NULL)
		{
			pclip.iter = pclip.fp_list;
			while (pclip.iter->next != NULL)
				pclip.iter = pclip.iter->next;
			if (pclip.bp_list != NULL)
			{
				pclip.iter->next = pclip.bp_list;
				pclip.bp_list->prev = pclip.iter;
			}
			return (pclip.fp_list);
		}
		else
		{
			if (pclip.bp_list != NULL)
				return (pclip.bp_list);
			return (NULL);
		}
		return (NULL);
	}
	if (pclip.result == 0)
	{
		if (bsp->node[node].isleaf == 1)
		{
			portal->leafs[portal->nb_leafs] = bsp->node[node].front;
			portal->nb_leafs++;
			portal->next = NULL;
			portal->prev = NULL;
			pclip.fp_list = portal;
		}
		else
			pclip.fp_list = clip_portal(bsp, bsp->node[node].front, portal);
		if (pclip.fp_list == NULL)
			return (NULL);
		if (bsp->node[node].back == -1)
			return (pclip.fp_list);
		while (pclip.fp_list != NULL)
		{
			pclip.tmp = pclip.fp_list->next;
			pclip.bp_list = NULL;
			pclip.bp_list = clip_portal(bsp, bsp->node[node].back, pclip.fp_list);
			if (pclip.bp_list != NULL)
			{
				pclip.iter = pclip.bp_list;
				while (pclip.iter->next != NULL)
					pclip.iter = pclip.iter->next;
				pclip.iter->next = pclip.p_list;
				if (pclip.p_list != NULL)
					pclip.p_list->prev = pclip.iter;
				pclip.p_list = pclip.bp_list;
			}
			pclip.fp_list = pclip.tmp;
		}
		return (pclip.p_list);
	}
	return (NULL);
}
