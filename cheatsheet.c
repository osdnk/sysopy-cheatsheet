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

// sigaction

void intHandler(int signum, siginfo_t *info, void *context) {
    WRITE_MSG("\rMother: Received SIGINT\n");

}

void sigationer() {
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;

    act.sa_sigaction = intHandler;
    if (sigaction(SIGINT, &act, NULL) == -1) FAILURE_EXIT(1, "Can't catch SIGINT\n");


    // sending value
    union sigval sv;
    sv.sival_int=2137;
    // int kill(pid_t pid, int sig) -- that seems to easier
    sigqueue(child, SIGUSR1, sv);
};

// receiving extra data
void sighandler (int signo, siginfo_t * t, void * c) {
    printf("%d", t->si_value.sival_int);
}

// masking signals
void masker() {
    sigset_t s;
    sigfillset(&s);
    sigdelset(&s, SIGUSR1);
    sigprocmask(SIG_BLOCK, &s, NULL);
};


// times works like
//    clock_t times(struct tms *buf);


// checking types of files
// Do not forget about S_ISREG, S_ISLINK


void piper() {

        int toChildFD[2];
        int toParentFD[2];

        pipe(toChildFD);
        pipe(toParentFD);

        int val1,val2,val3 = 0;

        pid_t pid;
        if((pid = fork()) == 0) {

            read(toChildFD[0], &val2, sizeof(int));

            val2 = val2 * val2;

            write(toParentFD[1], &val2, sizeof(int));

        } else {

            val1 = atoi(argv[1]);
            write(toChildFD[1], &val1, sizeof(int));

            sleep(1);

            read(toParentFD[0], &val3, sizeof(int));


            printf("%d square is: %d\n",val1, val3);
        }

}

// in order to exec file
if(pid == 0) {
execvp(parameters[0], parameters);
exit(1);
}


//handle dir like
void diro(char *path, char *operant, time_t date) {
    if (path == NULL)
        return;
    DIR *dir = opendir(path);


    if (dir == NULL) {
        printf("%s\n", "error!");
        return;
    }

    struct dirent *rdir = readdir(dir);
    struct stat file_stat;

    char new_path[PATH_MAX];

    while (rdir != NULL) {
        strcpy(new_path, path);
        strcat(new_path, "/");
        strcat(new_path, rdir->d_name);


        lstat(new_path, &file_stat); // with symlinks

        if (strcmp(rdir->d_name, ".") == 0 || strcmp(rdir->d_name, "..") == 0) {
            rdir = readdir(dir);
            continue;
        }
        //...
    }
    closedir(dir);
}