/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 17:12:02 by nainhaja          #+#    #+#             */
/*   Updated: 2021/10/30 17:12:03 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*copy_sec(t_node	*temp, char **t, int i)
{
	t_node	*temp2;

	temp2 = malloc(sizeof(t_node));
	temp->next = temp2;
	temp2->beforeeq = ft_beforeeq(t[i]);
	temp2->aftereq = ft_aftereq(t[i], g_shell);
	temp2->next = NULL;
	return (temp2);
}

void	copy(char **t, int n, t_list *g_shell)
{
	t_node	*temp;
	int		i;

	temp = malloc(sizeof(t_node));
	temp->beforeeq = ft_beforeeq(t[0]);
	temp->aftereq = ft_aftereq(t[0], g_shell);
	temp->next = NULL;
	free(g_shell->head);
	g_shell->head = temp;
	i = 1;
	while (i < n)
	{
		temp = copy_sec(temp, t, i);
		i++;
	}
	g_shell->env_len = i;
}

void	copy_env_str(t_list *g_shell)
{
	t_node	*temp;
	int		i;
	char	*s;

	i = 0;
	g_shell->env = malloc(sizeof(char *) * g_shell->env_len);
	temp = g_shell->head;
	while (temp != NULL)
	{
		g_shell->env[i] = ft_strdup("");
		s = g_shell->env[i];
		g_shell->env[i] = ft_strjoin(g_shell->env[i], temp->beforeeq);
		free(s);
		s = g_shell->env[i];
		g_shell->env[i] = ft_strjoin(g_shell->env[i], "=");
		free(s);
		s = g_shell->env[i];
		g_shell->env[i] = ft_strjoin(g_shell->env[i], temp->aftereq);
		free(s);
		temp = temp->next;
		i++;
	}
}

void	print_env(t_list *g_shell)
{
	t_node	*temp;

	temp = g_shell->head;
	while (temp != NULL)
	{
		if (temp->aftereq != 0)
		{
			printf("%s=", temp->beforeeq);
			printf("%s\n", temp->aftereq);
		}
		temp = temp->next;
	}
}

void	get_rest_command_pipe(t_list *g_shell, int c)
{
	int	i;
	int	len;

	i = skip_spaces(0, g_shell->tab[c]);
	len = ft_strlen(g_shell->tab[c]);
	g_shell->rest = ft_substr(g_shell->tab[c], i, len - i);
	g_shell->rest = remove_spaces(g_shell);
	g_shell->rest = remove_quotes(g_shell->rest);
	
}
