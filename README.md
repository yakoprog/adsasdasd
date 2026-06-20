*This project has been created as part of the 42 curriculum by ycinarog, bahkaya.*

# Minishell

A simplified shell written in C, built for the 42 common core.

## Description

Minishell is our own version of a Unix shell, close to bash. The goal of the project is to understand what actually happens between typing a command and seeing its output: reading input, splitting it into tokens, parsing it into commands, and running it with the right file descriptors.

What it can do:

- Run an interactive prompt with history (`readline`)
- Find and run commands from `PATH`, or by absolute/relative path
- Pipes (`|`)
- Redirections: `<`, `>`, `>>`, `<<` (heredoc)
- Environment variable expansion (`$VAR`, `$?`)
- Single and double quotes
- Signals (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`) behaving like in a real shell
- Builtins, run without forking: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

Anything that isn't a builtin goes through `fork` + `execve`, with `dup2` used to wire up pipes and redirections. Exit codes are tracked properly, including the ones coming from signals.

We also wrote our own `libft`, a small C library used instead of part of the standard library.

### How it works

| Module | Role |
| --- | --- |
| **Lexer** (`lexer_parser/lexer.c`) | Turns raw input into a list of tokens (words, pipes, redirections) |
| **Parser** (`lexer_parser/parser*.c`) | Groups tokens into commands, handles redirections, opens heredocs |
| **Expander** (`expander/`) | Expands `$VAR` / `$?` and removes quotes |
| **Executor** (`execution/`) | Forks processes, connects pipes, runs builtins or `execve` |
| **Builtins** (`buildins/`) | `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit` |
| **Signals** (`signals.c`) | `Ctrl+C` / `Ctrl+\` handling for the shell and its children |
| **libft** (`libft/`) | Our own string/memory/list utilities |

Flow: `input → lexer → parser → expander → executor`

## Instructions

### Requirements

- Linux (or any POSIX system)
- `cc` / `gcc`
- `make`
- `readline` dev library (`libreadline-dev` on Debian/Ubuntu)

### Build

```bash
make
```

This builds `libft` first, then compiles and links `minishell`.

```bash
make clean   # remove .o files
make fclean  # remove .o files and the binary
make re      # fclean + all
```

### Run

```bash
./minishell
```

```
minishell$ ls -la | grep ".c"
minishell$ echo $USER
minishell$ export FOO=bar
minishell$ exit
```

Quit with `exit` or `Ctrl+D`.

## Resources

### References

- GNU Bash Reference Manual
- man pages: `readline(3)`, `fork(2)`, `execve(2)`, `pipe(2)`, `dup2(2)`, `waitpid(2)`, `signal(2)`
- GNU Readline documentation
- POSIX Shell Command Language spec
- The 42 Minishell subject

### AI usage

We used an AI assistant mainly to understand concepts before implementing them ourselves: We tried to implement out pipex project to minishell project. In order to do that we tried to understand how multiple should work. Moreover, how signals should behave in parent vs child processes, and how bash handles edge cases like quoting or heredoc. It was also used to double check our handling of exit statuses and to help write this README.

All the actual code — lexer, parser, command location check, expander, executor, builtins, signal handling — was written by us.

## Project Structure

```
minishell/
├── Makefile
├── README.md
├── main.c
├── minishell.h
├── signals.c
├── lexer_parser/
│   ├── lexer.c
│   ├── parser.c
│   ├── parser_check.c
│   ├── parser_utils.c
│   ├── redirect_check.c
│   ├── token_create.c
│   └── free_tokens.c
├── expander/
│   ├── expander.c
│   ├── expander_utils.c
│   └── expand_cmd.c
├── execution/
│   ├── after_lexer.c
│   ├── command_parsed.c
│   ├── pipe_connection.c
│   ├── ft_multible_pipe.c
│   └── ft_free.c
├── buildins/
│   ├── builtins.c
│   ├── env_manager.c
│   ├── env_utils.c
│   ├── ft_cd.c
│   ├── ft_echo.c
│   ├── ft_env.c
│   ├── ft_exit.c
│   ├── ft_export.c
│   ├── ft_pwd.c
│   └── ft_unset.c
├── error_and_utils/
│   ├── utils.c
│   └── error_utils.c
└── libft/
    ├── libft.h
    ├── Makefile
    └── *.c
```
