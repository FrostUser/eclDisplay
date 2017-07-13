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
   * It is mostly necessary not for initial loading (BASF2 already
   * handles this) but for dynamic alteration of parameters during
   * runtime of EclDisplay.
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

    template <typename T>
    T get(const std::string &name);

    template <typename T>
    void set(const std::string &name, const T &newval);

    bool getBool(const std::string &name);
    int getInt(const std::string &name);
    double getDouble(const std::string &name);
    std::string getString(const std::string &name);

  private:
    std::map<std::string, std::string> values;
  };

  /********************************************/
  /***        TEMPLATE DEFINITIONS          ***/
  /********************************************/

  template <typename T>
  void EclDisplayConfig::set(const std::string &name, const T &newval)
  {
    std::ostringstream convert;
    convert << newval;

    values[name] = convert.str();
  }

  template <typename T>
  T EclDisplayConfig::get(const std::string &name)
  {
    std::istringstream convert(values[name]);
    T ret;
    convert >> ret;
    return ret;
  }
}

#endif // ECLDISPLAYCONFIG_H
