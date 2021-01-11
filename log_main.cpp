#include <iostream>
#include <sstream>
#include <unistd.h>
#include "Logger.h"

using namespace std;
using namespace CPlusPlusLogging;

int count_ = 100;
// test multithread log
void *workthread(void *arg)
{
	pthread_t	tid;
	tid = pthread_self();

    char szLog[256] = {0};
    int ntemp = count_;
    //LOG_TYPE(CONSOLE);

    while (ntemp--)
    {
        snprintf(szLog, 256, "pthread id = %ld, ntemp = %d", tid, ntemp);
        LOG_INFO(szLog);
    }

    return 0;
}

void test_log_multithread()
{
    pthread_t ntid;

    int thread_num = 10;
    while (thread_num--)
    {
        int err = pthread_create(&ntid, NULL, workthread, NULL);
        if (err != 0)
        {
            cout << "create thread error" << endl;
        }
        else 
        {
            /* code */
            cout << "--finish--" << endl;
        }  
    }	
}

void test_log_normal()
{
 LOG_TYPE(CONSOLE);
   LOG_ALWAYS("<=============================== START OF PROGRAM ===============================>");
   // Log message using Direct Interface
   // Log Level: LOG_ERROR
   LOG_ERROR("Message Logged using Direct Interface, Log level: LOG_ERROR");
   LOG_ALARM("Message Logged using Direct Interface, Log level: LOG_ALARM");
   LOG_ALWAYS("Message Logged using Direct Interface, Log level: LOG_ALWAYS");
   LOG_INFO("Message Logged using Direct Interface, Log level: LOG_INFO");
   LOG_BUFFER("Message Logged using Direct Interface, Log level: LOG_BUFFER");
   LOG_TRACE("Message Logged using Direct Interface, Log level: LOG_TRACE");
   LOG_DEBUG("Message Logged using Direct Interface, Log level: LOG_DEBUG");

   // Log message C++ Interface
   Logger* pLogger = NULL; // Create the object pointer for Logger Class
   pLogger = Logger::getInstance();

   pLogger->error("Message Logged using C++ Interface, Log level: LOG_ERROR");
   pLogger->alarm("Message Logged using C++ Interface, Log level: LOG_ALARM");
   pLogger->always("Message Logged using C++ Interface, Log level: LOG_ALWAYS");
   pLogger->buffer("Message Logged using C++ Interface, Log level: LOG_INFO");
   pLogger->info("Message Logged using C++ Interface, Log level: LOG_BUFFER");
   pLogger->trace("Message Logged using C++ Interface, Log level: LOG_TRACE");
   pLogger->debug("Message Logged using C++ Interface, Log level: LOG_DEBUG");

   // Log Variables
   std::string name = "Pankaj Choudhary";
   std::string address = "Delhi, India";
   int age = 26;

   std::ostringstream ss;
   ss << endl;
   ss << "\t" << "My Contact Details:" << endl;
   ss << "\t" << "Name: " << name << endl;
   ss << "\t" << "Address: " << address << endl;
   ss << "\t" << "Age: " << age << endl << endl;

   //pLogger->enableConsoleLogging();
   pLogger->updateLogLevel(LOG_LEVEL_INFO);

   // Log ostringstream ss to all the log levels
   LOG_ALWAYS("Logging ostringstream using Direct Interface");
   LOG_ERROR(ss);
   LOG_ALARM(ss);
   LOG_ALWAYS(ss);
   LOG_INFO(ss);
   LOG_BUFFER(ss);
   LOG_TRACE(ss);
   LOG_DEBUG(ss);

   Logger::getInstance()->buffer("Logging ostringstream using C++ Interface");
   Logger::getInstance()->error(ss);
   Logger::getInstance()->alarm(ss);
   Logger::getInstance()->always(ss);
   Logger::getInstance()->buffer(ss);
   Logger::getInstance()->info(ss);
   Logger::getInstance()->trace(ss);
   Logger::getInstance()->debug(ss);
   
   LOG_ALWAYS("<=============================== END OF PROGRAM ===============================>");
}

int main()
{
    test_log_multithread();

    sleep(1);
    return 0;
}