/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 21:13:36 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/29 21:13:37 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	addnode(char *beforeeq, char *aftereq, t_list *g_shell)
{
	t_node	*temp;
	t_node	*tempp;

	temp = (t_node *) malloc(sizeof(t_node));
	tempp = g_shell->head;
	if (search_used_node(beforeeq, aftereq, g_shell) == 0)
	{
		temp->beforeeq = ft_strdup(beforeeq);
		if (aftereq == 0)
			temp->aftereq = NULL;
		else
			temp->aftereq = ft_strdup(aftereq);
		temp->next = NULL;
		while (tempp->next != NULL)
		{
			tempp = tempp->next;
		}
		tempp->next = temp;
	}
	//free(s);
}

void	delete_node(t_node	*tempp)
{
	t_node	*next;

	next = tempp->next->next;
	tempp->next = next;
}

void	deletenode(char *t, t_list *g_shell)
{
	t_node	*tempp;

	tempp = g_shell->head;
	while (tempp->next != NULL)
	{
		if (strcmp(tempp->next->beforeeq, t) == 0)
		{
			delete_node(tempp);
			break ;
		}
		tempp = tempp->next;
	}
}

char	*searchnode(char *t, t_list *g_shell)
{
	t_node	*tempp;

	tempp = g_shell->head;
	while (tempp->next != NULL)
	{
		if (strcmp(tempp->next->beforeeq, t) == 0)
		{
			return (tempp->next->aftereq);
		}
		tempp = tempp->next;
	}
	return (0);
}

char	*editpwd(t_list *g_shell, char *ptr)
{
	t_node	*tempp;

	tempp = g_shell->head;
	while (tempp->next != NULL)
	{
		if (strcmp(tempp->next->beforeeq, "PWD") == 0)
		{
			if (!(ft_strcmp(ptr, "")))
				tempp->next->aftereq = getcwd(NULL, 0);
			return (tempp->next->aftereq);
		}
		tempp = tempp->next;
	}
	return (0);
}
