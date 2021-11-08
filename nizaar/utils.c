/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nainhaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:36:52 by nainhaja          #+#    #+#             */
/*   Updated: 2019/11/06 23:53:15 by nainhaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *s)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = (char *)malloc((ft_strlen(s) * sizeof(char) + 1));
	if (!ptr || !s)
		return (0);
	else
	{
		while (s[i])
		{
			ptr[i] = s[i];
			i++;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}

char	*ft_strchr(char *str, int c)
{
	size_t	i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	if (c == '\0' && str[i] == c)
		return ((str + i));
	if (i == ft_strlen(str))
		return (0);
	ptr = (str + i);
	return (ptr);
}

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	init_var(int *i, int *start, t_list *g_shell, int c)
{
	char	*str;

	str = g_shell->g_red_buff;
	if (c == 0)
		g_shell->g_read = 1;
	g_shell->g_red_buff = ft_strdup("");
	free(str);
	dup2(g_shell->g_fd, c);
	*start = *i;
}

void	cd(t_list *g_shell)
{
	char	*str;

	str = ft_strdup("");
	if (ft_strcmp(g_shell->rest, str) == 0)
	{
		chdir(searchnode("HOME", g_shell));
		editpwd(g_shell, g_shell->rest);
	}
	else
	{
		if (chdir(g_shell->rest) == -1)
		{
			printf("cd: not a directory: %s\n", g_shell->rest);
			g_shell->g_exit_code = 1;
		}
	}
	free(str);
}
