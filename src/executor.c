#include "minishell.h"

static void	handle_redirections(t_cmd *cmd)
{
	int	fd;
	
	// printf("test1!\n");
	if (cmd->redir_in && cmd->redir_in->filename)
	{
		fd = open(cmd->redir_in->filename, O_RDONLY);
		// printf("test2!\n");
		if (fd == -1)
		{
			perror(cmd->redir_in->filename);
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->redir_out && cmd->redir_out->filename)
	{
		int flags;
		
		flags = O_WRONLY | O_CREAT | O_TRUNC;
		fd = open(cmd->redir_out->filename, flags, 0644);
		// printf("test3!\n");
		if (fd == -1)
		{
			perror(cmd->redir_out->filename);
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	// printf("test4!\n");
	// ainda preciso fazer o heredoc aqui com o t_redirection ou cmd->delimiter
	// mas por enquanto elas n estao linkando ent mantive assim por agora e vemos isso
}

static int	execute_builtin(t_cmd *cmd, t_hell *shell)
{
	int	flag;

	flag = 0;
	if (!ft_strcmp(cmd->args[0], "echo") && ++flag)
		return (mini_echo(cmd, &shell->env, shell));
	else if (!ft_strcmp(cmd->args[0], "pwd") && ++flag)
		return (mini_pwd(cmd));
	else if (!ft_strcmp(cmd->args[0], "cd") && ++flag)
		mini_cd(cmd, &shell->env, shell);
	else if (!ft_strcmp(cmd->args[0], "env") && ++flag)
		mini_env(shell->env);
	else if (!ft_strcmp(cmd->args[0], "exit") && ++flag)
		mini_exit(shell);
	else if (!ft_strcmp(cmd->args[0], "export") && ++flag)
		mini_export(&shell->env, &shell->export, cmd);
	else if (!ft_strcmp(cmd->args[0], "unset") && ++flag)
		mini_unset(&shell->env, cmd, &shell->export, shell);
	else if (flag)
		return (shell->status = 0);
	return (shell->status = 1);
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
	handle_redirections(cmd);
	if (cmd->is_builtin)
		exit(execute_builtin(cmd, shell));
	if (shell->hist_fd >= 0)
		close(shell->hist_fd);
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
	int		prev_pipe;
	int		pipes[2];

	cmd = shell->cmd;
	prev_pipe = -1;
	while (cmd)
	{
		// if (cmd->is_builtin && !cmd->is_piped && !cmd->next)
		// {
		// 	handle_redirections(cmd);
		// 	shell->status = execute_builtin(cmd, shell);
		// 	return ;
		// }
		if (cmd->is_piped && pipe(pipes) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		cmd->pid = fork();
		if (cmd->pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (cmd->pid == 0)
		{
			shell->cmd = cmd;
			execute_child(cmd, prev_pipe, pipes, shell);
		}
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
