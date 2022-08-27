#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int StringToInt(char* s){
  int num = 0;
  for(int i = 0; i < strlen(s); i++){
    num *= 10;
    num += s[i] - '0';
  }
  return num;
}

int
main(int argc, char *argv[])
{

  int x = StringToInt(argv[1]);
  //printf("USER -  %d\n", x);
  sleep(x);

  exit(0);
}
