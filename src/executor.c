#include "minishell.h"

int	shell_heredoc(char *limiter)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		line = readline(RED"> "RESET);
		if (!line)
			break;
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			break;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

static void	do_heredoc(t_redirection *redir)
{
	int fd;

	fd = shell_heredoc(redir->limiter);
	if (fd == -1)
		exit(EXIT_FAILURE);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	open_infile(t_redirection *redir)
{
	redir->fd = open(redir->filename, O_RDONLY);
	if (redir->fd == -1)
	{
		perror(redir->filename);
		exit(EXIT_FAILURE);
	}
	dup2(redir->fd, STDIN_FILENO);
	close(redir->fd);
}

static void	open_outfile(t_redirection *redir, int append)
{
	int flags;
	
	if (append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	redir->fd = open(redir->filename, flags, 0644);
	if (redir->fd == -1)
	{
		perror(redir->filename);
		exit(EXIT_FAILURE);
	}
	dup2(redir->fd, STDOUT_FILENO);
	close(redir->fd);
}

void	handle_redirections(t_cmd *cmd)
{
	t_redirection *in;
	t_redirection *out;

	in = cmd->redir_in;
	out = cmd->redir_out;
	while (in)
	{
		if (in->type == REDIR_IN || in->type == INFILE)
			open_infile(in);
		else if (in->type == REDIR_HERE_DOC)
			do_heredoc(in);
		in = in->next;
	}
	while (out)
	{
		if (out->type == REDIR_OUT || out->type == OUTFILE)
			open_outfile(out, 0);
		else if (out->type == REDIR_OUT_APPEND || out->type == OUTFILE_APPEND)
			open_outfile(out, 1);
		out = out->next;
	}
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
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
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
		if (!cmd->is_piped && cmd->is_builtin)
		{
			shell->status = execute_builtin(cmd, shell);
			return ;
		}
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
