/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 19:41:24 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/29 19:41:25 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*checkvariables(char *str, t_list *g_shell)
{
	char	*s;
	t_node	*temp;
	char	*ptr;

	temp = g_shell->head;
	s = ft_strdup("");
	while (temp != NULL)
	{
		if (temp->aftereq != 0)
		{
			if (ft_strcmp(temp->beforeeq, str) == 0)
			{
				ptr = s;
				s = temp->aftereq;
				free(ptr);
				return (s);
			}
		}
		temp = temp->next;
	}
	return (s);
}

char	*expand_variable(t_list *g_shell, char *str, int *i, char *res)
{
	int		start;
	char	*var;
	char	*s;
	char	*ptr;

	*i = *i + 1;
	start = *i;
	while (str[*i] != ' ' && str[*i] != '\'' && str[*i] != '$' && str[*i] != '"' && str[*i])
		*i = *i + 1;
	ptr = ft_substr(str, start, *i - start);
	var = checkvariables(ptr, g_shell);
	s = res;
	res = ft_strjoin(res, var);
	free(s);
	free(ptr);
	return (res);
}

void	ft_export(t_list *g_shell)
{
	if (!(ft_strcmp(g_shell->rest, "")))
		print_export(g_shell);
	else
		check_line(g_shell);
}

char	*ft_strjoin_sec(char *str, char *ptr)
{
	char	*s;

	s = str;
	str = ft_strjoin(str, ptr);
	free(str);
	return (str);
}

void	finalise(char *ptr, int i, int start)
{
	char	*str;
	char	*p;

	str = g_shell->buffer;
	p = ft_substr(g_shell->buffer, start, i - start);
	free(str);
	g_shell->buffer = ft_strjoin(ptr, p);
	if (p)
		free(p);
}
