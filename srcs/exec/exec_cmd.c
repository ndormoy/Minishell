/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndormoy <ndormoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:48:11 by ndormoy           #+#    #+#             */
/*   Updated: 2022/04/11 16:34:16 by ndormoy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/function.h"

void	ft_exec_cmd_bis_3(t_to_clean *clean, t_command *all, char *path)
{
	if (ft_strcmp(all->cmd_to_exec[0], "") == TRUE)
	{
		free(path);
		ft_putstr_fd(BRED "minishell: : command not found\n" CRESET, 2);
		g_status = 127;
		ft_clean_exit(clean);
		exit(g_status);
	}
}

char	*ft_exec_cmd_bis_2(t_to_clean *clean, t_command *all, char *tmp)
{
	char	*path;

	path = chose_ath_cmd(all->cmd_to_exec[0], tmp);
	if (!path)
	{
		if (ft_strncmp((all->cmd_to_exec[0]), "./", 2) == TRUE)
		{
			redirection_error(ft_strdup(all->cmd_to_exec[0]));
			g_status = errno;
		}
		else
		{
			ft_print_error(1,
				all->cmd_to_exec[0], ": command not found", NULL);
			g_status = 127;
		}
		ft_clean_exit(clean);
		exit(g_status);
	}
	return (path);
}

char	*ft_exec_cmd_bis(char **env
	, t_to_clean *clean, t_command *all, int *out)
{
	char	*tmp;

	tmp = NULL;
	if (*out != -1)
		close(*out);
	if (ft_strcmp(all->cmd_to_exec[0], "exit") == 0)
	{
		ft_exit(all, clean);
		ft_clean_exit(clean);
		exit(g_status);
	}
	g_status = 0;
	tmp = find_val_in_tab(env, "PATH");
	return (tmp);
}

void	ft_exec_cmd_bis_4(t_to_clean *clean, t_command *all, char *path)
{
	ft_print_error(1, all->cmd_to_exec[0], ": Is a directory", NULL);
	g_status = 126;
	free(path);
	ft_clean_exit(clean);
	exit(g_status);
}

int	ft_exec_cmd(char **env, t_to_clean *clean, t_command *all, int out)
{
	char	*path;
	char	*tmp;
	int		pid;

	path = NULL;
	if (prio_exit(all) == TRUE)
		g_status = 0;
	signal_manager2();
	signal_minishell(all);
	pid = fork();
	if (pid == 0)
	{
		tmp = ft_exec_cmd_bis(env, clean, all, &out);
		path = ft_exec_cmd_bis_2(clean, all, tmp);
		ft_exec_cmd_bis_3(clean, all, path);
		if (execve(path, all->cmd_to_exec, env) < 0)
			ft_exec_cmd_bis_4(clean, all, path);
		free(path);
		return (0);
	}
	return (pid);
}

/* int	ft_exec_cmd(char **env, t_to_clean *clean, t_command *all, int out)
{
	char	*path;
	char	*tmp;
	int		pid;

	path = NULL;
	if (prio_exit(all) == TRUE)
	{
		g_status = 0;
	}
	signal_manager2();
	pid = fork();
	if (pid == 0)
	{
		tmp = ft_exec_cmd_bis(env, clean, all, &out);
		path = ft_exec_cmd_bis_2(clean, all, tmp);
		ft_exec_cmd_bis_3(clean, all, path);
		if (execve(path, all->cmd_to_exec, env) < 0)
			ft_exec_cmd_bis_4(clean, all, path);
		free(path);
		return (0);
	}
	return (0);
}
 */