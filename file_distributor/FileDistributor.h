#pragma once 

#include <vector>
#include <string>

namespace boost { namespace program_options {
  class options_description;
}}

namespace gobjfs { 

/**
 * Filesytems slow down if you store millions of files
 * in a single directory.
 * This class written to prevent that.
 * Given a list of mountpoints, it creates subdirectories
 * and it hashes the filename to decide which subdir
 * the file should be stored/retrieved from
 */

class FileDistributor
{
  public:

  struct Config
  {
    // total slots across mountPoints
    size_t slots_{0};

    // mountpoints in which subdirectories are created
    std::vector<std::string> mountPoints_;

    int32_t addOptions(boost::program_options::options_description& desc);
  };

  Config config_;

  // actual list of sub-directories
  std::vector<std::string> dirs_; 

  static FileDistributor instance_;

  int32_t initDirectories(const Config& config, bool createFlag);

  const std::string& getDir(const std::string& fileName) const;

  static int32_t removeDirectories(const std::vector<std::string> &mountPoints);

  // add options needed by IOExecutor to parser config
  int32_t addOptions(boost::program_options::options_description& desc);
};

}
