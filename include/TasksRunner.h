#pragma once

#include <filesystem>
#include <future>
#include <string>
#include <map>

#include "ITask.h"


namespace UbiTasks
{
  struct TaskResult
  {
    bool IsValid; // set to false if there is no result
    bool ErrorTriggered; // set to false if there is no result
    std::filesystem::path InputFilePath; // the path to the file the task were done on
    std::string Output; // the result to be displayed / the error in case of ErrorTriggered = false;
  };
  
  struct TasksRunner
  {
    TasksRunner(ITask & task);

    /// @brief main method of the runner to start a specific task on a directory
    /// @param the path to the folder containing the filed to run the task on
    void RunOnInputDir(std::filesystem::path dir);

    /// @brief check this to know if there is remaining task still running
    /// @return true if there is, false else
    bool IsEmpty();

    /// @brief Pop one result, removing the task from the running tasks queue
    /// @return the Result, please see TaskResult documentation for more details
    TaskResult PopResult();

  private:
    ITask & mTask;
    std::mutex mMutex;
    std::map<std::string, std::future<std::string>> mAsyncTasks;
  };
}
