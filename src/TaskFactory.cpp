#include "TaskFactory.h"

#include "Crc32Task.h"
#include "cxxopts.hpp"
#include "OpusTask.h"


namespace UbiTasks
{
  TaskEnvironment TaskFactory::CreateTask(int argc, char** argv)
  {
    TaskEnvironment ret{false};

    cxxopts::Options options(
      "Ubi-Tasks",
      "Tool to run tasks concurrently on a specific folder (given as parameter), "
      "can handle both CRC32 computing task (hash) and encoding raw data to opus format task (opus)\n");

    options.add_options()
      ("i,input", "MANDATORY -- input directory path", cxxopts::value<std::filesystem::path>())
      ("t,type", "MANDATORY -- the type of task to execute (opus / hash)", cxxopts::value<std::string>())
      ("o,output", "(opus only) output directory path", cxxopts::value<std::filesystem::path>()->default_value("./OPUS_OUTPUT"))
      ("m,mode", "(opus only) opus mode (voip, audio or lowdelay)", cxxopts::value<std::string>()->default_value("audio"))
      ("s,seed", "(hash only) the CRC32 seed", cxxopts::value<uint32_t>()->default_value("0"))
      ("h,help", "Print usage");

    const auto result = options.parse(argc, argv);

    if(result.count("help"))
    {
      std::cout << options.help() << std::endl;
      return ret;
    }

    if(result.count("input") == 0 || result.count("type") == 0)
    {
      std::cerr << "Missing parameters!" << std::endl << std::endl;
      std::cout << options.help() << std::endl;
      return ret;
    }

    ret.InputDir = result["input"].as<std::filesystem::path>();
    if(exists(ret.InputDir) == false || is_empty(ret.InputDir) || is_directory(ret.InputDir) == false)
    {
      std::cerr << "Wrong directory as input parameter (empty or does not exist)" << std::endl;
      std::cerr << "Received: " << ret.InputDir << std::endl;
      return ret;
    }

    const auto& task_type = result["type"].as<std::string>();
    if(task_type != std::string("opus") && task_type != std::string("hash"))
    {
      std::cerr << "Wrong task type (only 'opus' or 'hash' are expected)" << std::endl;
      std::cerr << "Received: " << task_type << std::endl;
      return ret;
    }

    if(const auto opus = task_type == std::string("opus"))
    {
      OpusMode mode = OpusMode::Audio;
      const auto& mode_param = result["mode"].as<std::string>();

      if(mode_param == std::string("voip"))
      {
        mode = OpusMode::VoIP;
      }
      else if(mode_param == std::string("audio"))
      {
        mode = OpusMode::Audio;
      }
      else if(mode_param == std::string("lowdelay"))
      {
        mode = OpusMode::LowDelay;
      }
      else
      {
        std::cout << " !! wrong opus mode -> assuming audio !!" << std::endl << std::endl;
      }

      ret.Task = std::make_unique<OpusTask>(result["output"].as<std::filesystem::path>(), mode);
      std::cout << "### OPUS TASK STARTING ###" << std::endl << std::endl;
    }
    else
    {
      ret.Task = std::make_unique<Crc32Task>(result["seed"].as<uint32_t>());
      std::cout << "### CRC32 TASK STARTING ###" << std::endl << std::endl;
    }

    std::cout << "### Running on input : " << absolute(ret.InputDir) << std::endl << std::endl;
    ret.IsValid = true;
    return ret;
  }
}
