/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maange_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 20:59:02 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/29 20:59:03 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sorting(int sort_indice, t_node *temp, char *tmp_ae, char *tmp_be)
{
	while (sort_indice)
	{
		sort_indice = 0;
		while (temp->next != NULL)
		{
			if (strcmp(temp->beforeeq, temp->next->beforeeq) > 0)
			{
				sort_indice = 1;
				tmp_be = temp->beforeeq;
				temp->beforeeq = temp->next->beforeeq;
				temp->next->beforeeq = tmp_be;
				tmp_ae = temp->aftereq;
				temp->aftereq = temp->next->aftereq;
				temp->next->aftereq = tmp_ae;
			}
			temp = temp->next;
		}
		temp = g_shell->head;
	}
}

void	ft_sort(t_list *g_shell)
{
	t_node	*temp;
	int		sort_indice;
	char	*tmp_be;
	char	*tmp_ae;

	sort_indice = 1;
	tmp_ae = NULL;
	tmp_be = NULL;
	temp = g_shell->head;
	sorting(sort_indice, temp, tmp_ae, tmp_be);
}
