#include<iostream>
#include<fstream>
#include<string>
#include<mutex>
#include<time.h>
#include <unistd.h>
#ifndef LOGGER_H
#define LOGGER_H

#define LOG_FILE_CREATION_FAILED 0
enum logType { INFO, DEBUG, WARN, ERROR };

class Logger
{
 private:

  bool open();
  void getCurrentTime(char *buf);
  void close();

  std::string m_logFileName;
  std::ofstream m_logStream;
  std::mutex m_logFileWriteLock;

 public:
  void write (enum logType flag,
	      const char *messagexo);
  Logger(
	 const char *fileName
	 );
  ~Logger();
};

#endif //LOGGER_H
