#include "SixCatsLogger.h"

#include <iostream> // cout
using namespace std;

#define LOCAL_C6_DEBUG 1

// --- ------------------------------------------------------------------------

SixCatsLogger::SixCatsLogger() {
  selfSetup();
}

// --- ------------------------------------------------------------------------

SixCatsLogger::SixCatsLogger(LogLevel inLogLevel) {
  selfSetup();
  logLevel = inLogLevel;
}

// --- ------------------------------------------------------------------------

SixCatsLogger::~SixCatsLogger() {
  #ifdef LOCAL_C6_DEBUG
  cout << "SixCatsLogger obj destroyed" << endl;
  #endif // ifdef LOCAL_C6_DEBUG
}

// --- ------------------------------------------------------------------------

void SixCatsLogger::selfSetup() {
  setLogLevel(SixCatsLogger::Critical);
}

// --- ------------------------------------------------------------------------

void SixCatsLogger::setLogLevel(LogLevel inLogLevel) {
  logLevel = inLogLevel; //
}

// --- ------------------------------------------------------------------------

void SixCatsLogger::write(LogLevel messageLevel, const string str) {
  if (messageLevel > logLevel) {
    return;
  }

  cout << str << endl;
}

// --- ------------------------------------------------------------------------

string SixCatsLogger::composeLine(const string& metaInfo, const string& message) const {
  const string tmps = metaInfo + " >> " + message;

  return tmps;
}

// --- ------------------------------------------------------------------------

void SixCatsLogger::c(const string& message) {
  write(Critical, message);
}

// --- ------------------------------------------------------------------------

void SixCatsLogger::c(const string& metaInfo, const string& message) {
  write(Critical, composeLine(metaInfo, message));
}

// --- ------------------------------------------------------------------------

void SixCatsLogger::w(const string& message) {
  write(Warning, message);
}

// --- ------------------------------------------------------------------------

void SixCatsLogger::w(const string& metaInfo, const string& message) {
  write(Warning, composeLine(metaInfo, message));
}

// --- ------------------------------------------------------------------------

void SixCatsLogger::i(const string& message) {
  write(Info, message);
}

// --- ------------------------------------------------------------------------

void SixCatsLogger::i(const string& metaInfo, const string& message) {
  write(Info, composeLine(metaInfo, message));
}

// --- ------------------------------------------------------------------------

void SixCatsLogger::d(const string& message) {
  write(Debug, message);
}

// --- ------------------------------------------------------------------------

void SixCatsLogger::d(const string& metaInfo, const string& message) {
  write(Debug, composeLine(metaInfo, message));
}

// --- ------------------------------------------------------------------------

void SixCatsLogger::t(const string& metaInfo, const string& message) {
  write(Trace, composeLine(metaInfo, message));
}

// --- ------------------------------------------------------------------------

void SixCatsLogger::t(const string& message) {
  write(Trace, message);
}

// --- ------------------------------------------------------------------------

void SixCatsLogger::f(const string& metaInfo, const string& message) {
  write(Flood, composeLine(metaInfo, message));
}

// --- ------------------------------------------------------------------------

void SixCatsLogger::f(const string& message) {
  write(Flood, message);
}

// --- ------------------------------------------------------------------------

void SixCatsLogger::writeL(LogLevel                                messageLevel,
                           std::function<void(std::ostringstream&)>makeMessage) {
  if (messageLevel > logLevel) {
    return;
  }

  ostringstream s;
  makeMessage(s);
  write(messageLevel, s.str());
}

void SixCatsLogger::writeL(LogLevel                                messageLevel,
                           const string                          & metaInfo,
                           std::function<void(std::ostringstream&)>makeMessage) {
  if (messageLevel > logLevel) {
    return;
  }

  ostringstream s;
  makeMessage(s);

  write(messageLevel, composeLine(metaInfo, s.str()));
}

// --- ------------------------------------------------------------------------

void SixCatsLogger::c(std::function<void(std::ostringstream&)>makeMessage) {
  writeL(Critical, makeMessage);
}

void SixCatsLogger::w(std::function<void(std::ostringstream&)>makeMessage) {
  writeL(Warning, makeMessage);
}

void SixCatsLogger::i(std::function<void(std::ostringstream&)>makeMessage) {
  writeL(Info, makeMessage);
}

void SixCatsLogger::d(std::function<void(std::ostringstream&)>makeMessage) {
  writeL(Debug, makeMessage);
}

void SixCatsLogger::t(std::function<void(std::ostringstream&)>makeMessage) {
  writeL(Trace, makeMessage);
}

void SixCatsLogger::f(std::function<void(std::ostringstream&)>makeMessage) {
  writeL(Flood, makeMessage);
}

// --- ------------------------------------------------------------------------

void SixCatsLogger::c(const string                          & metaInfo,
                      std::function<void(std::ostringstream&)>makeMessage) {
  writeL(Critical, metaInfo, makeMessage);
}

void SixCatsLogger::w(const string                          & metaInfo,
                      std::function<void(std::ostringstream&)>makeMessage) {
  writeL(Warning, metaInfo, makeMessage);
}

void SixCatsLogger::i(const string                          & metaInfo,
                      std::function<void(std::ostringstream&)>makeMessage) {
  writeL(Info, metaInfo, makeMessage);
}

void SixCatsLogger::d(const string                          & metaInfo,
                      std::function<void(std::ostringstream&)>makeMessage) {
  writeL(Debug, metaInfo, makeMessage);
}

void SixCatsLogger::t(const string                          & metaInfo,
                      std::function<void(std::ostringstream&)>makeMessage) {
  writeL(Trace, metaInfo, makeMessage);
}

void SixCatsLogger::f(const string                          & metaInfo,
                      std::function<void(std::ostringstream&)>makeMessage) {
  writeL(Flood, metaInfo, makeMessage);
}

// --- ------------------------------------------------------------------------

void c6c(SixCatsLogger *logger, const string message) {
  if (logger == 0) {
    return;
  }

  logger->c(message);
}

// --- ------------------------------------------------------------------------

void c6c(SixCatsLogger *logger, const string metaInfo, const string message)  {
  if (logger == 0) {
    return;
  }

  logger->c(metaInfo, message);
}

// --- ------------------------------------------------------------------------

void c6w(SixCatsLogger *logger, const string message) {
  if (logger == 0) {
    return;
  }

  logger->w(message);
}

// --- ------------------------------------------------------------------------

void c6w(SixCatsLogger *logger, const string metaInfo, const string message)  {
  if (logger == 0) {
    return;
  }

  logger->w(metaInfo, message);
}

// --- ------------------------------------------------------------------------

void c6i(SixCatsLogger *logger, const string message) {
  if (logger == 0) {
    return;
  }

  logger->i(message);
}

// --- ------------------------------------------------------------------------

void c6i(SixCatsLogger *logger, const string metaInfo, const string message)  {
  if (logger == 0) {
    return;
  }

  logger->i(metaInfo, message);
}

// --- ------------------------------------------------------------------------

void c6d(SixCatsLogger *logger, const string message) {
  if (logger == 0) {
    return;
  }

  logger->d(message);
}

// --- ------------------------------------------------------------------------

void c6d(SixCatsLogger *logger, const string metaInfo, const string message)  {
  if (logger == 0) {
    return;
  }

  logger->d(metaInfo, message);
}

// --- ------------------------------------------------------------------------

void c6t(SixCatsLogger *logger, const string message) {
  if (logger == 0) {
    return;
  }

  logger->t(message);
}

// --- ------------------------------------------------------------------------

void c6t(SixCatsLogger *logger, const string metaInfo, const string message)  {
  if (logger == 0) {
    return;
  }

  logger->t(metaInfo, message);
}

// --- ------------------------------------------------------------------------

void c6f(SixCatsLogger *logger, const string message) {
  if (logger == 0) {
    return;
  }

  logger->f(message);
}

// --- ------------------------------------------------------------------------

void c6f(SixCatsLogger *logger, const string metaInfo, const string message)  {
  if (logger == 0) {
    return;
  }

  logger->f(metaInfo, message);
}

// --- ------------------------------------------------------------------------

void c6c(SixCatsLogger                          *logger,
         std::function<void(std::ostringstream&)>makeMessage) {
  if (logger == 0) {
    return;
  }

  logger->c(makeMessage);
}

void c6w(SixCatsLogger *logger, std::function<void(std::ostringstream&)>makeMessage) {
  if (logger == 0) {
    return;
  }

  logger->w(makeMessage);
}

void c6i(SixCatsLogger *logger, std::function<void(std::ostringstream&)>makeMessage) {
  if (logger == 0) {
    return;
  }

  logger->i(makeMessage);
}

void c6d(SixCatsLogger *logger, std::function<void(std::ostringstream&)>makeMessage) {
  if (logger == 0) {
    return;
  }

  logger->d(makeMessage);
}

void c6t(SixCatsLogger *logger, std::function<void(std::ostringstream&)>makeMessage) {
  if (logger == 0) {
    return;
  }

  logger->t(makeMessage);
}

void c6f(SixCatsLogger *logger, std::function<void(std::ostringstream&)>makeMessage) {
  if (logger == 0) {
    return;
  }

  logger->f(makeMessage);
}

// --- ------------------------------------------------------------------------

void c6c(SixCatsLogger *logger, const string metaInfo,
         std::function<void(std::ostringstream&)>makeMessage) {
  if (logger == 0) {
    return;
  }

  logger->c(metaInfo, makeMessage);
}

void c6w(SixCatsLogger *logger, const string metaInfo,
         std::function<void(std::ostringstream&)>makeMessage) {
  if (logger == 0) {
    return;
  }

  logger->w(metaInfo, makeMessage);
}

void c6i(SixCatsLogger *logger, const string metaInfo,
         std::function<void(std::ostringstream&)>makeMessage) {
  if (logger == 0) {
    return;
  }

  logger->i(metaInfo, makeMessage);
}

void c6d(SixCatsLogger *logger, const string metaInfo,
         std::function<void(std::ostringstream&)>makeMessage) {
  if (logger == 0) {
    return;
  }

  logger->d(metaInfo, makeMessage);
}

void c6t(SixCatsLogger *logger, const string metaInfo,
         std::function<void(std::ostringstream&)>makeMessage) {
  if (logger == 0) {
    return;
  }

  logger->t(metaInfo, makeMessage);
}

void c6f(SixCatsLogger *logger, const string metaInfo,
         std::function<void(std::ostringstream&)>makeMessage) {
  if (logger == 0) {
    return;
  }

  logger->f(metaInfo, makeMessage);
}

// --- ------------------------------------------------------------------------
// --- ------------------------------------------------------------------------
