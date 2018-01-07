#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <signal.h>

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ASK         "DO you want another transaction"
#define TRIES       3
#define SLEEPTIME   2
#define BEEP        putchar('\a')

char get_ok_char() {
    int c;
    while ((c = getchar() != EOF && strchr("yYnN", c) == NULL))
        ;
    return c;
}

int get_response(const char* question, int maxtries) {

    while (1) {
        /* simulate O_NONBLOCK mode */
        /* sleep(SLEEPTIME); */
        printf("%s(y/n)?", question);
        printf("\n");
        fflush(stdout);
        
        int input = tolower(get_ok_char());
        if (input == 'y')
            return 0;
        if (input == 'n')
            return 1;
        if (--maxtries == 0)
            return 2;
        BEEP; /* warning: has been waste one time */
    }
}

void set_cr_noecho_mode() {
    struct termios ttystate;

    tcgetattr(STDIN_FILENO, &ttystate);
    ttystate.c_lflag &= ~ICANON;        /* no buffering */
    ttystate.c_lflag &= ~ECHO;          /* no echo */
    ttystate.c_cc[VMIN] = 1;            /* get only 1 char at a time */
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

void set_nodelay_mode() {
    int termflags;

    termflags = fcntl(STDIN_FILENO, F_GETFL);
    termflags |= O_NONBLOCK;
    fcntl(STDIN_FILENO, F_SETFL, termflags);
}

void tty_mode(int how) {
    static struct termios original_mode;
    static int original_flags;
    static int stored = 0;

    if (how == 0) {
        tcgetattr(STDIN_FILENO, &original_mode);
        original_flags = fcntl(STDIN_FILENO, F_GETFL);
        stored = 1;
    } else if (stored) {
        tcsetattr(STDIN_FILENO, TCSANOW, &original_mode);
        fcntl(STDIN_FILENO, F_SETFL, original_flags);
    }
}

void ctrl_c_handler(int signum) {
    tty_mode(1);
    exit(1);
}

int main() {
    tty_mode(0);                    /* store original modes */
    set_cr_noecho_mode();
    /* set_nodelay_mode(); */
    signal(SIGINT, ctrl_c_handler);
    signal(SIGQUIT, SIG_IGN);       /* ignore SIGQUIT signal, such as Ctrl+\ */
    
    int response = get_response(ASK, TRIES);
    tty_mode(1);                    /* restore all modes */
    if (response == 2) {
        fprintf(stderr, "we have use all %d times to receive inputs.\n", TRIES);
    }
    return response;
}
