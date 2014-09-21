#include "daemon.h"


int run_in_daemon() {
  pid_t pid;
  
  //创建一个子进程，子进程返回0,父进程返回子进程ID，出错返回-1
  pid = fork();
  //退出父进程
  if (pid < 0) {
    perror("error fork");
    exit (1);
  } else if (pid > 0) {
    printf("exiting parent process\n");
    exit (0);
  }
  
  //此时父进程已退出，下面是子进程的执行语句
  printf("Child process is running....");
  //创建一个新的会话，并担任该会话组的组长，让进程摆脱原会话、原进程组和原控制终端的控制，是该进程成为一个守护进程
  pid = setsid();
  
  if (pid < 0) {
    perror("setsid");
  }
  
  //切换当前工作目录到/tmp，设置掩码为0，并关闭所有可能已打开的文件。
  chdir("/tmp");
//   umask(0);
  int i;
  for (i = 0; i < MAXFILE; i++) {
    close(i);
  }
  tmp_running = 1;
  //接收系统发送的信号并调用sigterm_handler函数
  signal(SIGKILL, sigterm_handler);
}

void sigterm_handler(int arg) {
  tmp_running = 0;
}

int exit_servers (char *server_name) {
  
}