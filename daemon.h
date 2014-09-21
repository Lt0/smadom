#ifndef DAEMON_H
#define DAEMON_H
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#define MAXFILE 65535
// volatile sig_atomic_t _running = 1;
int tmp_running;
int run_in_daemon();
int exit_servers (char *server_name);
void sigterm_handler(int arg);

#endif