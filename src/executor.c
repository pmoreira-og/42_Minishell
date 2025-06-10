#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

static char *join_path(const char *dir, const char *cmd)
{
	size_t len;
	char *full_path;

	len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	full_path = (char *)malloc(len);
	if (!full_path)
		return NULL;
	snprintf(full_path, len, "%s/%s", dir, cmd);
	return (full_path);
}

static char *resolve_cmd_path(char *cmd, char **envp)
{
	char	*path_env;
	char	*paths;
	char	*token;

	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return strdup(cmd);
		return NULL;
	}
	path_env = NULL;
	for (int i = 0; envp && envp[i]; i++)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break;
		}
	}
	if (!path_env)
		return NULL;
	paths = strdup(path_env);
	if (!paths)
		return NULL;
	token = strtok(paths, ":");
	while (token)
	{
		char *full_path = join_path(token, cmd);
		if (full_path && access(full_path, X_OK) == 0)
		{
			free(paths);
			return full_path;
		}
		free(full_path);
		token = strtok(NULL, ":");
	}
	free(paths);
	return NULL;
}

// static void	handle_redirections(t_cmd *cmd)
// {
// 	int	fd;

// 	if (cmd->infile)
// 	{
// 		fd = open(cmd->infile, O_RDONLY);
// 		if (fd == -1)
// 		{
// 			perror(cmd->infile);
// 			exit(EXIT_FAILURE);
// 		}
// 		dup2(fd, STDIN_FILENO);
// 		close(fd);
// 	}
// 	if (cmd->outfile)
// 	{
// 		int flags = O_WRONLY | O_CREAT | O_TRUNC;
// 		fd = open(cmd->outfile, flags, 0644);
// 		if (fd == -1)
// 		{
// 			perror(cmd->outfile);
// 			exit(EXIT_FAILURE);
// 		}
// 		dup2(fd, STDOUT_FILENO);
// 		close(fd);
// 	}
// 	// ainda preciso fazer o heredoc aqui com o t_redirection ou cmd->delimiter
// 	// mas por enquanto elas n estao linkando ent mantive assim por agora e vemos isso
// }

static int	execute_builtin(t_hell *shell)
{
	int	flag;

	flag = 0;
	if (!ft_strcmp(shell->cmd->args[0], "echo") && flag++)
		mini_echo(shell->cmd, &shell->env);
	else if (!ft_strcmp(shell->cmd->args[0], "pwd") && flag++)
		mini_pwd(shell->cmd);
	else if (!ft_strcmp(shell->cmd->args[0], "cd") && flag++)
		mini_cd(shell->cmd, &shell->env);
	else if (!ft_strcmp(shell->cmd->args[0], "env") && flag++)
		mini_env(shell->env);
	else if (!ft_strcmp(shell->cmd->args[0], "exit") && flag++)
		mini_exit(shell);
	else if (!ft_strcmp(shell->cmd->args[0], "export") && flag++)
		mini_export(&shell->env, &shell->export, shell->cmd);
	else if (!ft_strcmp(shell->cmd->args[0], "unset") && flag++)
		mini_unset(&shell->env, shell->cmd);
	else if (flag)
	{
		shell->status = 0;
		return (shell->status);
	}
	shell->status = 1;
	return (shell->status);
}

static void	execute_child(t_cmd *cmd, int prev_pipe_fd, int *pipefd, t_hell *shell)
{
	if (prev_pipe_fd != -1)
	{
		dup2(prev_pipe_fd, STDIN_FILENO);
		close(prev_pipe_fd);
	}
	if (cmd->is_piped)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	// handle_redirections(cmd);
	if (cmd->is_builtin)
		exit(execute_builtin(shell));
	if (!cmd->cmd_path)
		cmd->cmd_path = resolve_cmd_path(cmd->args[0], shell->envp);
	if (!cmd->cmd_path)
	{
		fprintf(stderr, "%s: command not found\n", cmd->args[0]);
		exit(127);
	}
	execve(cmd->cmd_path, cmd->args, cmd->envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

static void	wait_for_all(t_cmd *cmd_list, t_hell *shell)
{
	int		status;
	t_cmd	*tmp;

	tmp = cmd_list;
	while (tmp)
	{
		if (tmp->pid > 0)
		{
			waitpid(tmp->pid, &status, 0);
			if (WIFEXITED(status))
				shell->status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->status = 128 + WTERMSIG(status);
		}
		tmp = tmp->next;
	}
}

void	execute_pipeline(t_hell *shell)
{
	t_cmd	*cmd;
	int		prev_pipe = -1;
	int		pipes[2];

	cmd = shell->cmd;
	prev_pipe = -1;
	while (cmd)
	{
		if (cmd->is_builtin && !cmd->is_piped && !cmd->next)
		{
			// handle_redirections(cmd);
			shell->status = execute_builtin(shell);
			return ;
		}
		if (cmd->is_piped)
		{
			if (pipe(pipes) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		cmd->pid = fork();
		if (cmd->pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (cmd->pid == 0)
			execute_child(cmd, prev_pipe, pipes, shell);
		if (prev_pipe != -1)
			close(prev_pipe);
		if (cmd->is_piped)
		{
			close(pipes[1]);
			prev_pipe = pipes[0];
		}
		else
			prev_pipe = -1;
		cmd = cmd->next;
	}
	wait_for_all(shell->cmd, shell);
}
