#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
typedef int pipa[2];

char *cmd0[] = {"ls", 0}, *cmd1[] = {"wc", "-l", 0};
static char **cmds[] = {cmd0, cmd1};
static int ncmds = sizeof(cmds) / sizeof(cmds[0]);
static void exec_nth_command(int ncmds, char ***cmds);

static void exec_pipe_command(int ncmds, char ***cmds, pipa output) {
    dup2(output[1], 1); // 1 = stdout
    close(output[0]);
    close(output[1]);
    exec_nth_command(ncmds, cmds);
}

static void exec_nth_command(int ncmds, char ***cmds) {
    if (ncmds > 1) {
        pid_t pid;
        pipa input;
        if (pipe(input) != 0) exit(1);
        if ((pid = fork()) < 0) exit(1);
        if (pid == 0) exec_pipe_command(ncmds - 1, cmds, input);
        dup2(input[0], 0); // 0 = stdin
        close(input[0]);
        close(input[1]);
    }
    execvp(cmds[ncmds - 1][0], cmds[ncmds - 1]);
}

int main(int argc, char **argv) {
    exec_nth_command(ncmds, cmds);
    return(0);
}
