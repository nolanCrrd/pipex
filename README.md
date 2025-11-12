# Pipex

Pipex is one of medium project in 42 Curriculum. The objective is to reproduce the `pipe` usage in bash:

```bash
< infile command_1 | command_2 > outfile
```

How my pipex work:
```bash
./pipex "infile" "command_1" "command_2" "outfile"
```

## Particularities to check

During this project I discovers that bash have many specific case, here a list of examples:

|Command|Specific result|
|-------|---------------|
|< unknown_infile cmd_1 \| cmd_n > out|Make all command but not the first one (without the input)|
|< infile cmd_1 \| cmd_n > out|Exit code = Exit code of last command|
|< infile sleep x \| sleep y > out|Make all sleeps at the same time -> total time = time of the biggest|

## Learned here

- How start a child process with `fork()`
- How child process status work and how to handle it with `waitpid()`
- How to launch a command with `execve()`
- That there is specific code for each type of Errors
- How open work and bash's pipe work
- Project organization (Starting using `Jira`)