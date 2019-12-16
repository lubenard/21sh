/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_env2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 13:46:20 by lubenard          #+#    #+#             */
/*   Updated: 2019/12/16 14:27:02 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>
#include <sh21.h>

int		exec_env(char *right_path, char **argv, char **env)
{
	pid_t	pid;
	int		statval;

	if ((pid = fork()) < 0)
		return (display_error("ymarsh: error: fork failed", NULL));
	reset_shell_attr(0);
	signal(SIGINT, handle_signals_proc);
	if (!pid)
		execve(right_path, argv, env);
	waitpid(pid, &statval, WUNTRACED | WCONTINUED);
	set_none_canon_mode(0);
	return (free_after_exec(right_path, env, statval));
}

t_env	*print_env_no_command(t_env *env, int flags, int *is_command)
{
	t_env *tmp;

	tmp = env;
	*is_command = 0;
	if (flags & PE_V && flags & PE_I)
		print_verbose_env(env, NULL, 1);
	while (env)
	{
		if (ft_strcmp(env->env_line, ""))
		{
			ft_putstr_fd(env->env_line, 1);
			if (!(flags & PE_0))
				ft_putchar_fd('\n', 1);
		}
		env = env->next;
	}
	free_env(tmp);
	return (NULL);
}

void	verbose(t_env *env, char *right_path, char *command)
{
	print_verbose_env(env, NULL, 1);
	if (right_path != NULL)
	{
		ft_putstr_fd("#env executing: ", 1);
		ft_putendl_fd(command, 1);
	}
}

int		print_err_env(t_env *env, char **compacted_env, char *comm)
{
	ft_putstr_fd("No file found with the following name: ", 2);
	ft_putendl_fd(comm, 2);
	free_env(env);
	free(compacted_env);
	return (127);
}
