#ifndef ECLDISPLAYCONFIG_H
#define ECLDISPLAYCONFIG_H

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace Belle2 {
  /**
   * Class to store configuration of EclDisplayModule.
   */
  class EclDisplayConfig
  {
  public:
    /**
     * Default constructor, creates standard configuration.
     */
    EclDisplayConfig();
    /**
     * Constructor to load configuration from file.
     */
    EclDisplayConfig(const char* fname);

    void parseLine(std::string line);

    int getInt(const std::string &name);

    template <typename T>
    T get(const std::string &name);

  private:
    std::map<std::string, std::string> values;
  };
}

#endif // ECLDISPLAYCONFIG_H
