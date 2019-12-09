#ifndef DEBUG_HPP
#define DEBUG_HPP
#include <fstream>
#include <iostream>
#include <cstdarg>
#include <chrono>

namespace game {

  namespace debug {
    static std::ofstream out("jqLog.log",std::ios::app);
    static bool time_stamp = false;
    void print() { time_stamp = false; }  // base case for vardiac template
    template <typename T, typename... Types> 
    void print(T var1, Types... var2) { 
      if(!time_stamp) {
        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::string tsString = std::ctime(&time);
        tsString.erase(tsString.length()-1);
        tsString = "[" + tsString + "]  ";
        out << tsString;
        time_stamp = true;
      }
      std::clog << var1;
      out << var1;
      print(var2...);
    }
  }

}

#endif
