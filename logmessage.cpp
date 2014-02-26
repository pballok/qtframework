#include "logmessage.h"
#include "logger.h"

LogMessage::LogMessage(const Severity severity)
  : severity_(severity), message_("") {
  message_stream_.setString(&message_);
}

LogMessage::LogMessage(const LogMessage& that) {
  severity_ = that.severity_;
  message_ = that.message_;
  message_stream_.setString(&message_);
}

LogMessage::~LogMessage() {
  if (message_ != "") Logger::instance().writeMessage(severity_, message_);
}

LogMessage& LogMessage::operator<<(const LoggerManip manipulator) {
  switch (manipulator) {
    case LoggerManip::EOM:   Logger::instance().writeMessage(severity_, message_);
                             // There's no 'break' here because the EOM manipulator
                             // needs to do a 'CLEAR' as well
    case LoggerManip::CLEAR: message_="";
                             break;
    default:                 Logger::instance().writeMessage(Severity::ERROR, "Invalid LoggerManip value in LogMessage");
  }

  return *this;
}
