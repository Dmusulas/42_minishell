# Minishell

<!--toc:start-->

- [Minishell](#minishell)
  - [Compilation](#compilation)
  - [TODO (continously updated)](#todo-continously-updated)
  <!--toc:end-->

## Compilation

For development it is advised to use [compiledb](https://github.com/nickdiego/compiledb) this creates JSON file so all that linter and Clangd LSP (language server protocol) can pick up where all the files are. This has several advantages:

1. Jump to definition works;
2. Errors are actually proper;
3. More...

## TODO (continiously updated)

- [x] Main loop which displays prompt and waits;
- [x] add_history implemented
- [x] Signal handling (sigint)ctrl+C, (EOF exit shell)ctrl+D
- [ ] Sigquit, ctrl+\ to be implemented with execution
- [ ] Research best way how to split up work;
- [ ] Simple executor which picks up arguments from prompts and executes them (adapt PIPEX).

## built ins
- [ ] echo with option -n
- [ ] cd
- [ ] pwd
- [ ] export
- [ ] unset
- [ ] env
- [ ] exit

## lexer/parser
- [ ] set up struct to build parser tree
- [ ] tokenizer / tree
- [ ] check if pipe token
