/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 20:23:33 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/29 20:23:34 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_before_eq(char *str, int *i)
{
	int		start;
	char	*before_eq;
	char	*s;

	start = 0;
	*i = 0;
	while (str[*i] != '=' && str[*i] != '\0')
		*i = *i + 1;
	s = ft_substr(str, start, *i - start);
	before_eq = s;
	return (before_eq);
}

char	*get_after_eq(char *str, int *i)
{
	int		start;
	char	*after_eq;
	char	*s;

	if (str[*i] == '=')
	{
		start = *i + 1;
		while (str[*i] != '\0')
			*i = *i + 1;
		s = ft_substr(str, start, *i - start);
		after_eq = s;
		return (after_eq);
	}
	else if (str[*i] == '\0')
		return (0);
	else
		return (ft_strdup(""));
}

void	get_variables(char *str, t_list *g_shell)
{
	int		i;
	char	*before_eq;
	char	*after_eq;

	before_eq = get_before_eq(str, &i);
	after_eq = get_after_eq(str, &i);
	addnode(before_eq, after_eq, g_shell);
	free(before_eq);
	free(after_eq);
}

void	check_line(t_list *g_shell)
{
	char	**line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	line = ft_split_spaces(g_shell->rest, ' ');
	while (line[i])
	{
		if (line[i][0] == '=')
		{
			printf("minishell: export: `%s': not a valid identifier\n", line[i]);
			g_shell->g_exit_code = 1;
		}
		else
			get_variables(line[i], g_shell);
		i++;
	}
	while (j < i)
	{
		free(line[j]);
		j++;
	}
	free(line);
	//system("leaks minishell");
}

void	print_export(t_list *g_shell)
{
	t_node	*temp;
	int		i;

	temp = g_shell->head;
	ft_sort(g_shell);
	i = 0;
	while (temp != NULL)
	{
		printf("declare -x %s", temp->beforeeq);
		if (temp->aftereq == 0)
			printf("\n");
		else
			printf("=\"%s\" \n", temp->aftereq);
		temp = temp->next;
		i++;
	}
}
