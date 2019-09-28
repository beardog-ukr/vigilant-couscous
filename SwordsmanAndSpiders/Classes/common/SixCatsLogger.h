#pragma once

#include <string>
#include <sstream> // std::ostringstream
#include <functional>

#include "cocos2d.h"

class SixCatsLogger {
public:

  enum LogLevel {
    Critical = 0,
    Warning,
    Info,
    Debug,
    Trace,
    Flood
  };

  SixCatsLogger();
  SixCatsLogger(LogLevel logLevel);
  virtual ~SixCatsLogger();

  void setLogLevel(LogLevel logLevel);

  void c(const std::string& message);
  void w(const std::string& message);
  void i(const std::string& message);
  void d(const std::string& message);
  void t(const std::string& message);
  void f(const std::string& message);

  void c(const std::string& metaInfo,
         const std::string& message);
  void w(const std::string& metaInfo,
         const std::string& message);
  void i(const std::string& metaInfo,
         const std::string& message);
  void d(const std::string& metaInfo,
         const std::string& message);
  void t(const std::string& metaInfo,
         const std::string& message);
  void f(const std::string& metaInfo,
         const std::string& message);

  void c(std::function<void(std::ostringstream&)>makeMessage);
  void w(std::function<void(std::ostringstream&)>makeMessage);
  void i(std::function<void(std::ostringstream&)>makeMessage);
  void d(std::function<void(std::ostringstream&)>makeMessage);
  void t(std::function<void(std::ostringstream&)>makeMessage);
  void f(std::function<void(std::ostringstream&)>makeMessage);

  void c(const std::string                     & metaInfo,
         std::function<void(std::ostringstream&)>makeMessage);
  void w(const std::string                     & metaInfo,
         std::function<void(std::ostringstream&)>makeMessage);
  void i(const std::string                     & metaInfo,
         std::function<void(std::ostringstream&)>makeMessage);
  void d(const std::string                     & metaInfo,
         std::function<void(std::ostringstream&)>makeMessage);
  void t(const std::string                     & metaInfo,
         std::function<void(std::ostringstream&)>makeMessage);
  void f(const std::string                     & metaInfo,
         std::function<void(std::ostringstream&)>makeMessage);

protected:

  void selfSetup();

  LogLevel logLevel;

  void        write(LogLevel          messageLevel,
                    const std::string str);
  void        writeL(LogLevel                                messageLevel,
                     std::function<void(std::ostringstream&)>makeMessage);
  void        writeL(LogLevel                                messageLevel,
                     const std::string                     & metaInfo,
                     std::function<void(std::ostringstream&)>makeMessage);
  void        writeFile(const std::string& metaInfo,
                        const std::string& message);

  std::string composeLine(const std::string& metaInfo,
                          const std::string& message) const;
};

// --- -----------------------------------------------------------------------

void c6c(SixCatsLogger    *logger,
         const std::string message);
void c6w(SixCatsLogger    *logger,
         const std::string message);
void c6i(SixCatsLogger    *logger,
         const std::string message);
void c6d(SixCatsLogger    *logger,
         const std::string message);
void c6t(SixCatsLogger    *logger,
         const std::string message);
void c6f(SixCatsLogger    *logger,
         const std::string message);

void c6c(SixCatsLogger    *logger,
         const std::string metaInfo,
         const std::string message);
void c6w(SixCatsLogger    *logger,
         const std::string metaInfo,
         const std::string message);
void c6i(SixCatsLogger    *logger,
         const std::string metaInfo,
         const std::string message);
void c6d(SixCatsLogger    *logger,
         const std::string metaInfo,
         const std::string message);
void c6t(SixCatsLogger    *logger,
         const std::string metaInfo,
         const std::string message);
void c6f(SixCatsLogger    *logger,
         const std::string metaInfo,
         const std::string message);

void c6c(SixCatsLogger                          *logger,
         std::function<void(std::ostringstream&)>makeMessage);
void c6w(SixCatsLogger                          *logger,
         std::function<void(std::ostringstream&)>makeMessage);
void c6i(SixCatsLogger                          *logger,
         std::function<void(std::ostringstream&)>makeMessage);
void c6d(SixCatsLogger                          *logger,
         std::function<void(std::ostringstream&)>makeMessage);
void c6t(SixCatsLogger                          *logger,
         std::function<void(std::ostringstream&)>makeMessage);
void c6f(SixCatsLogger                          *logger,
         std::function<void(std::ostringstream&)>makeMessage);

void c6c(SixCatsLogger                          *logger,
         const std::string                       metaInfo,
         std::function<void(std::ostringstream&)>makeMessage);
void c6w(SixCatsLogger                          *logger,
         const std::string                       metaInfo,
         std::function<void(std::ostringstream&)>makeMessage);
void c6i(SixCatsLogger                          *logger,
         const std::string                       metaInfo,
         std::function<void(std::ostringstream&)>makeMessage);
void c6d(SixCatsLogger                          *logger,
         const std::string                       metaInfo,
         std::function<void(std::ostringstream&)>makeMessage);
void c6t(SixCatsLogger                          *logger,
         const std::string                       metaInfo,
         std::function<void(std::ostringstream&)>makeMessage);
void c6f(SixCatsLogger                          *logger,
         const std::string                       metaInfo,
         std::function<void(std::ostringstream&)>makeMessage);

// === ========================================================================
// this came from http://stackoverflow.com/questions/1666802/is-there-a-class-macro-in-c
inline std::string c6_methodName(const std::string& prettyFunction) {
  size_t colons = prettyFunction.find("::");
  size_t begin  = prettyFunction.substr(0, colons).rfind(" ") + 1;
  size_t end    = prettyFunction.rfind("(") - begin;

  const std::string ss = prettyFunction.substr(begin, end) + "()";

  return ss;
}

#define __c6_MN__ c6_methodName(__PRETTY_FUNCTION__)
