#pragma once

#include <mutex>

#include "ITask.h"

struct OpusEncoder;

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
    OpusTask(std::filesystem::path outputFolder, OpusMode mode);
    std::string Execute(std::istream & is, const std::filesystem::path & inputFilePath) override;
    
    ~OpusTask() override;

  private:
    std::filesystem::path GetOutputPath(const std::filesystem::path & inputFilePath) const;
    const std::filesystem::path mOutputFolder;
    const OpusMode mOpusMode;

    mutable std::mutex mEncoderMutex;
    OpusEncoder * mOpusEncoder;
  };
}
