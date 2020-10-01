/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adjlstnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkarkaus <mkarkaus@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 14:44:41 by mkarkaus          #+#    #+#             */
/*   Updated: 2020/10/01 14:54:12 by mkarkaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_graph		*create_graph(int ver, int **edges)
{
	t_graph		*graph;

	graph = (t_graph *)ft_memalloc(sizeof(t_graph));
	graph->array = (t_alhead *)ft_memalloc(ver * sizeof(t_alhead));
	
}