#include"Logger.h"

Logger::Logger::Logger(const char *fileName) 
{
  m_logFileName = fileName;
  bool ret = open();
  if (ret < 0)
    throw LOG_FILE_CREATION_FAILED;
}

Logger::Logger::~Logger()
{
  m_logStream.close();
}

bool Logger::Logger::open()
{
  m_logStream.open(m_logFileName, std::ofstream::out|std::ofstream::trunc);
  if (m_logStream.is_open())
    return true;
  else
    return false;
}

void Logger::Logger::getCurrentTime(char *buf)
{
  time_t     now;
  struct tm  *tstruct;
  tstruct = localtime(&now);
  time (&now);
  tstruct = localtime(&now);
  // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
  // for more information about date/time format
  strftime(buf, 80 , "[ %X ]:[ %d-%m-%Y ]", tstruct);
}

void Logger::Logger::close()
{
  m_logStream.close();
}

void Logger::Logger::write(enum logType flag, const char* message)
{
  std::string logFlag;
  char buf [80];
  switch(flag) {
  case INFO:
    logFlag = "[ INFO ]:";
    break;
  case DEBUG:
    logFlag = "[ DEBUG ]:";
    break;
  case WARN:
    logFlag = "[ WARN ]:";
    break;
  case ERROR:
    logFlag = "[ ERROR ]:";
    break;
  }

  //sleep till you acquire lock on mutex
  while (!m_logFileWriteLock.try_lock()) {
    //sleep in microseconds.
    usleep(1000);
  }
  Logger::Logger::getCurrentTime(buf);
  std::string dateString(buf);
  m_logStream << logFlag.c_str()  << dateString.c_str() << ":[ " << message << " ]" << std::endl;
  m_logStream.flush();
  m_logFileWriteLock.unlock();
}
