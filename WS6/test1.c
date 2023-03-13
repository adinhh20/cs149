#include "apue.h"

int
main(void)
{
	pid_t	pid;

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid != 0) {		/* parent */
		sleep(2);
        printf("Parent pid: %d\n", pid);
		exit(2);				/* terminate with exit status 2 */
	}

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid != 0) {		/* first child */
		sleep(4);
        printf("First child pid: %d\n", pid);
		abort();				/* terminate with core dump */
	}

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid != 0) {		/* second child */
        printf("Second child pid: %d\n", pid);
		execl("/bin/dd", "dd", "if=/etc/passwd", "of=/dev/null", NULL);
		exit(7);				/* shouldn't get here */
	}

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid != 0) {		/* third child */
        printf("Third child pid: %d\n", pid);
		sleep(8);
		exit(0);				/* normal exit */
	}

	sleep(6);					/* fourth child */
    printf("Fourth child pid: %d\n", pid);
	kill(getpid(), SIGKILL);	/* terminate w/signal, no core dump */
	exit(6);					/* shouldn't get here */
}
