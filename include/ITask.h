#pragma once

#include <string>
#include <istream>

namespace UbiTasks
{
  struct ITask
  {
    virtual ~ITask() = default;
    virtual std::string Execute(const std::istream &) = 0;
  };
}
