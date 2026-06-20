/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:15:51 by ycinarog          #+#    #+#             */
/*   Updated: 2026/06/18 20:59:46 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
}	t_type;

typedef struct s_shell
{
	char	**env;
	int		exit_status;
}	t_shell;

typedef struct s_cmd
{
	char			**args;
	int				*arg_quoted;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_expand
{
	char	*env_val;
	char	*prefix;
	char	*var_name;
	char	*var_value;
	char	*suffix;
	char	*tmp;
}	t_expand;

typedef struct s_token
{
	char			*value;
	t_type			type;
	int				quote_type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_quote_state
{
	int	in_sq;
	int	in_dq;
	int	quote_type;
}	t_quote_state;

extern volatile sig_atomic_t	g_signal;

void	lexer(char *input, t_token **tokens);
void	free_tokens(t_token *tokens);
t_token	*new_token(char *value, t_type type, int quote_type);
void	ft_token_add_back(t_token **tokens, t_token *new_node);
void	operator_create(t_token **tokens, t_type type, char *input, int len);
void	word_create(t_token **tokens, char *input, int quote_type, int len);

void	parse_tokens(t_token *tokens, t_cmd **cmds, t_shell *shell);
void	pipe_or_not(t_token **temp, t_cmd *current_cmd, int *i, t_shell *shell);
int		handle_heredoc(char *delimiter);
void	redirout_or_not(t_token **temp, t_cmd *current_cmd, t_shell *shell);
void	append_or_not(t_token **temp, t_cmd *current_cmd, t_shell *shell);
void	redirin_or_not(t_token **temp, t_cmd *current_cmd, t_shell *shell);

void	heredoc_sigint(int sig);
int		heredoc_cleanup(int *p_fd, int stdin_copy);
int		heredoc_read_loop(int *p_fd, char *delim, int stdin_copy);

void	expand_cmds(t_cmd *cmds, t_shell *shell);
char	*expand_single_str(char *str, t_shell *shell);
void	expand_cmd_args(t_cmd *tmp_cmd, t_shell *shell);
char	*execute_expand(char *str, int *i, t_expand *expand, t_shell *shell);
char	*get_expand_var_value(t_expand *exp, char *str, int *i, t_shell *shell);
char	*remove_quotes(char *str);
char	*build_expanded_str(t_expand *exp, char *str);
void	create_expand(t_expand **expand);
void	reset_expand_fields(t_expand *expand);
void	free_tokens_for_expand(t_expand *expand);
void	strip_empty_unquoted(t_cmd *tmp_cmd);

void	after_lexer(t_cmd *cmds, t_shell *shell);
void	pipe_connection(t_cmd *cmd);
void	ft_multiple_pipe(t_cmd *tmp, t_shell *shell, int *id,
			int *prev_read_fd);
char	*put_command(char *input, char **envp);
int		has_slash(char *str);
void	ft_free_split(char **arr);
int		ft_bypass(t_cmd *tmp, t_shell *shell);

int		is_builtin(char *cmd);
void	execute_builtin(t_cmd *cmd, t_shell *shell, int is_child);
void	ft_cd(t_cmd *cmd, t_shell *shell);
void	ft_echo(t_cmd *cmd, t_shell *shell);
void	ft_env(t_shell *shell);
void	ft_exit(t_cmd *cmd, t_shell *shell, int is_child);
void	ft_export(t_cmd *cmd, t_shell *shell);
void	ft_pwd(t_shell *shell);
void	ft_unset(t_cmd *cmd, t_shell *shell);
void	update_pwd_oldpwd(t_shell *shell);

char	*get_env_value(char *key, char **envp);
char	**export_add(char *new_var, char **old_env);
char	**copy_env(char **envp);
char	**export_remove(char *target, char **old_env);
void	increment_shlvl(t_shell *shell);

int		print_error(t_shell *shell, char *cmd, char *msg, int err_code);
void	export_error(t_shell *shell, char *cmd_name, char *bad_arg);
int		is_valid_env_name(char *str);
int		pipe_error(t_token *tokens, t_shell *shell);
void	print_token_error(t_shell *shell, t_token *bad_token);
int		check_syntax(t_token *tokens, t_shell *shell);
int		check_quotes(char *str, t_shell *shell);
void	free_cmds(t_cmd *cmds);

void	init_signals(void);
void	ignore_sigint_parent(void);
void	restore_sigint_parent(void);
void	handle_sigint(int sig);

#endif
