#include<iostream>
#include<unistd.h>
#include"Logger.h"
#include<string>
#include<sstream>
int main()
{
  Logger log("MyLogger");
  int pid = fork();
  int i = 10;
  int myPid = getpid();
  enum logType logT = DEBUG;
  std::stringstream str;
  str << "This is written by process" << myPid;  
  for (;i > 0; i--)
    log.write(logT,str.str().c_str());
  return 0;
}
