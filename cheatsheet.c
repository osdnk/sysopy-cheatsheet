/*SIGACTION(2)                                                                  Linux Programmer's Manual

NAME
        sigaction, rt_sigaction - examine and change a signal action

        SYNOPSIS
#include <signal.h>

int sigaction(int signum, const struct sigaction *act,
              struct sigaction *oldact);

Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

sigaction(): _POSIX_C_SOURCE >= 1 || _XOPEN_SOURCE || _POSIX_SOURCE

        siginfo_t: _POSIX_C_SOURCE >= 199309L

DESCRIPTION

This inctoduction was made to made this file similat to manual xD
        The sigaction() system call is used to change the action taken by a process on receipt of a specific signal.  (See signal(7) for an overview of signals.)

signum specifies the signal and can be any valid signal except SIGKILL and SIGSTOP.

If act is non-NULL, the new action for signal signum is installed from act.  If oldact is non-NULL, the previous action is saved in oldact.

The sigaction structure is defined as something like:

struct sigaction {
    void     (*sa_handler)(int);
    void     (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t   sa_mask;
    int        sa_flags;
    void     (*sa_restorer)(void);
};

On some architectures a union is involved: do not assign to both sa_handler and sa_sigaction.

The  sa_restorer  field  is  not  intended  for application use.  (POSIX does not specify a sa_restorer field.)  Some further details of purpose of this field can be found in
        sigreturn(2).


*/


// malloc && calloc

void mallocer () {
    int ** a = malloc(sizeof (int*) * N);
    for (i = 0; i < N; i++) {
        a[i] = malloc((sizeof(int)) * M);
    }

    for (i = 0; i < N; i++) {
        free(a[i]);
    }
    free(a);
}


// file handling
void filer () {
    int source = open("s", O_RDONLY);
    int target = open("t", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR); // create ifne, wr only, trunc to 0, args with OCR
    char *tmp = malloc(len * sizeof(char));

    for (int i = 0; i < amount; i++){
        if(read(source, tmp, (size_t) (len + 1) * sizeof(char)) != (len + 1)) {
            return 1;
        }

        if(write(target, tmp, (size_t) (len + 1) * sizeof(char)) != (len + 1)) {
            return 1;
        }
    }
    close(source);
    close(target);
    free(tmp);
    return 0;

}



