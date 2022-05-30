#pragma once

#include "ITask.h"


namespace UbiTasks
{
  enum class OpusMode
  {
    VoIP,
    Audio,
    LowDelay
  };

  struct OpusTask : ITask
  {
    OpusTask(std::string outputFolder, OpusMode mode);
    std::string Execute(const std::istream & is, const std::string & inputFilePath) override;

  private:
    std::string GetOutputPath(const std::string & inputFilePath) const;
    const std::string mOutputFolder;
    const OpusMode mOpusMode;
  };
}
