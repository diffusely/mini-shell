# Minishell

Minishell is a minimal Unix shell implemented in C, designed to mimic the basic behavior of bash. It supports command execution, pipes, redirections, environment variables, and robust signal handling.

## Features
- **Command Execution**: Run binaries and built-in commands (echo, cd, pwd, env, exit, etc.).
- **Pipes**: Chain commands using `|`.
- **Redirections**: Input (`<`), output (`>`), append (`>>`), and heredoc (`<<`).
- **Environment Variables**: Export, unset, and expand variables.
- **Signal Handling**: Handles Ctrl+C (SIGINT), Ctrl+\ (SIGQUIT), and Ctrl+D (EOF) like bash.
- **History**: Stores command history in `history.txt`.

## Signal Handling
- **Prompt**: Ctrl+C interrupts input, prints a new prompt. Ctrl+\ is ignored. Ctrl+D exits shell.
- **Heredoc**: Ctrl+C interrupts heredoc input, prints warning, sets status. Ctrl+D prints EOF warning.
- **Execution**: Signals are reset to default in child processes. Status is propagated to parent.

## Usage
1. Build with `make`.
2. Run with `./minishell`.
3. Type commands as in bash. Use pipes, redirections, and environment variables.
4. Use Ctrl+C, Ctrl+\, and Ctrl+D to test signal handling.

## File Structure
- `src/` - Source code
- `include/headers/` - Header files
- `lib/` - Libft and get_next_line
- `history.txt` - Command history
- `Makefile` - Build script

## Example
```sh
minishell$ echo Hello World
Hello World
minishell$ ls | grep minishell
minishell$ cat << EOF
heredoc test
EOF
heredoc test
minishell$ ^C
minishell$ echo $?
130
minishell$ sort | sort ^\
Quit (core dumped)
minishell$ echo $?
131
```

## Authors
- noavetis
- vmakarya

## Notes
- This project is for educational purposes and mimics bash behavior as closely as possible within the scope of the assignment.