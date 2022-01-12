
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "nethogs/src/libnethogs.h"


int pid;
int bw;
char* cmd;
char cmd_full[512];
int triggered = 0;

void cb(int action, NethogsMonitorRecord const *data) {

  if(action != NETHOGS_APP_ACTION_SET) return;
  if(data->pid != pid) return;
  
  printf("Called: %d - PID: %d - kbps: %f\n", action, data->pid, data->recv_kbs);

  if(!triggered) {
    if(data->recv_kbs >= (float) bw) {

      triggered = 1;
      strcpy(cmd_full, cmd);
      strcat(cmd_full, " above");
      system(cmd_full);
    }
  } else {
    if(data->recv_kbs < (float) bw) {
      triggered = 0;
      strcpy(cmd_full, cmd);
      strcat(cmd_full, " below");
      system(cmd_full);
    }
  }
}



void usage(char* cmdname) {
  fprintf(stderr, "Usage: %s <pid> <bw> <cmd>\n", cmdname);
  fprintf(stderr, "  <pid> is the process id of the process to monitor for bandwidth usage\n");
  fprintf(stderr, "  <bw> is the bandwidth at which to trigger the command in kilobits per second\n");
  fprintf(stderr, "  <cmd> is the command to run when the bandwidth usage of <pid> rises above\n");
  fprintf(stderr, "        or drops below <bw>. The argument 'above' or 'below' is given to <cmd>\n");
          
}


int main(int argc, char *argv[]) {
  
  if(argc != 4) {
    usage(argv[0]);
    return -1;
  }

  if(sscanf(argv[1], "%i", &pid) != 1) {
    fprintf(stderr, "PID must be an integer");
    usage(argv[0]);
    return -1;
  }

  if(sscanf(argv[2], "%i", &bw) != 1) {
    fprintf(stderr, "Bandwidth must be an integer");
    usage(argv[0]);
    return -1;
  }

  cmd = argv[3];
  
  nethogsmonitor_loop(*cb, NULL, 200);
  
  return 0;
}
