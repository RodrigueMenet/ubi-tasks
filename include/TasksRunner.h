#pragma once

#include <filesystem>
#include <future>
#include <string>
#include <map>


namespace UbiTasks
{
  struct TaskResult
  {
    bool IsValid; // set to false if there is no result
    std::string InputFilePath; // the path to the file the task were done on
    std::string Output; // the result to be displayed
  };


  struct TasksRunner
  {
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
    std::mutex mMutex;
    std::map<std::string, std::future<std::string>> mTasks;
  };
}
