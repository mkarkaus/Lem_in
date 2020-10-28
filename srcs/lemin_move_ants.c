/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_move_ants.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreijola <sreijola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 10:29:30 by sreijola          #+#    #+#             */
/*   Updated: 2020/10/28 10:36:43 by sreijola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** lasketaan yhteen mahdollisia dd:tä, menee sinne missä pienin
** ensin katsotaan ekalla muurahaiselle lyhin reitti, jolloin se varaa seuraavan huoneen 
** seuraavaksi katsotaan toisen muurahaisen lyhin reitti ja lisätään kyseisen reitin pituuteen 
** huoneen "varausjonossa" olevien muurahaisten määrä.
** lasketaan movet
*/

#include "../includes/lem_in.h"

void	print_move(int antnb, char *roomname, int first, int j)
{
	if (first == 0)
		write(1, " ", 1);
	ft_printf("L%d-%s:%d", antnb, roomname, j);
}

int		check_routes(t_hill *ah, int ant)
{
	int			i;
	int			nxt_rm;
	int			tmp;
	t_alhead 	*ptr;
	t_node		*node;
	
	i = 0;
	tmp = 0;
	nxt_rm = -1;
	while (ah->maze->array[i].antnb[ant] == 0)//i < (ah->maze->ver - 1) && 
	{
		ft_printf("SOTASORSA\n");
		++i;
	}
	if (i == 1)
		return (0);
	ptr = ah->maze->array;
	node = ptr[i].head;
	ft_printf("!!i:%d dd:%d!!\n", i, ptr[i].dd);
	while (node != NULL) // pitää tarkistaa array[i]:hin linkattujen nodejen dd + q ja valita pienin
	{
		tmp = node->v;
		if (ptr[tmp].dd != -1 && (nxt_rm == -1 || ((ptr[tmp].dd + ptr[tmp].q) < \
		(ptr[nxt_rm].dd + ptr[nxt_rm].q))))
			nxt_rm = tmp;
		node = node->next;
	}
	if (nxt_rm == -1)
		return (-1);
	ptr[nxt_rm].q++;
	ptr[i].antnb = 0;
	if (ptr[nxt_rm].q == 1)
		return(nxt_rm);
	return (0);
}

int		route_ants(t_hill *ah)
{
	int		a;
	int		first;
	int		nxt_rm;
	int		finished;
	int		j;
	
	finished = 0;
	while (finished == 0)//niin kauan kun kaikki ei oo maalissa)
	{
		first = 1;
		a = 0;
		j = 0;
		//while (++a < ah->ants) //anna liike jokaiselle muurahaiselle
		//{
		// while (j < ah->rooms)
		// {
		// 	ft_printf("%3i", ah->maze->array[j].antnb[a]);
		// 	j++;
		// }
		// write(1, "\n", 1);
		if ((nxt_rm = check_routes(ah, a)) == -1) //palauttaa -1 jos ei reitteja maaliin, 0 jos jää odottamaan
			return (-1);
		else if (nxt_rm > 0)
		{
			print_move(a + 1, ah->name[nxt_rm], first, nxt_rm);
			if (ah->maze->array[j].head == NULL)
				write(1, "HEllo\n", 6);
			ah->maze->array[nxt_rm].q = 0;
			ah->maze->array[nxt_rm].antnb[a] = 1;
			first = 0;
			if (nxt_rm == 1)//jos liike vie endroomin
				finished++;
		}
		//}
	}
	return (0);
}
