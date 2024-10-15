# Minishell

[![C CI](https://github.com/Dmusulas/42_minishell/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/Dmusulas/42_minishell/actions/workflows/c-cpp.yml)

## Table of contents

1. [Minishell](#minishell)
   1. [Contribution](#contribution)
      1. [Compilation](#compilation)
      2. [Style](#style)
      3. [Pull requests](#pull-requests)
   2. [TODO (continiously updated)](<#todo-(continiously-updated)>)
      1. [built ins](#built-ins)
      2. [lexer](#lexer)
      3. [lexer/parsing syntax error handling](#lexer/parsing-syntax-error-handling)

## Contribution

### Compilation

For development it is advised to use [compiledb](https://github.com/nickdiego/compiledb) this creates JSON file so all that linter and Clangd LSP (language server protocol) can pick up where all the files are. This has several advantages:

1. Jump to definition works;
2. Errors are actually proper;
3. More...

### Style

Adhere to norminette style as well as make sure that before merging to main the project compiles.

### Pull requests

To avoid merge conflicts make sure to:

1. `git pull origin main` (origin or whatever this github repo is name in your remote check with `git remote -v`).
2. Solve any merge conflicts in your editor.
3. Push to your branch.
4. Create pull request.

## TODO (continiously updated)

- [x] Main loop which displays prompt and waits;
- [x] add_history implemented
- [x] Signal handling (sigint)ctrl+C, (EOF exit shell)ctrl+D
- [ ] Sigquit, ctrl+\ to be implemented with execution
- [ ] Research best way how to split up work;
- [ ] Simple executor which picks up arguments from prompts and executes them (adapt PIPEX).

### built ins

- [ ] echo with option -n
- [ ] cd
- [ ] pwd
- [ ] export
- [ ] unset
- [ ] env
- [ ] exit

### lexer

- [x] tokenize in lexer struct (linked list)
- [x] pre parse info processing/labeling

### lexer/parsing syntax error handling

- [x] check for quotes and find match
- [ ] redir token used without specifying target file
- [ ] invalid use of pipe (no command, pipe at end)
- [ ] ambiguous redirs (attempt to redir input and output at same time)
- [ ] redir without command
- [ ] incorrect builtin use (incorrect syntax/unsupporeted context)
- [ ] heredoc '<<' without specifying delimeter str
- [ ] undefined env_vars (bash expands into empty string)
- [ ] empty command/argument
- [ ] special characters without escape.
