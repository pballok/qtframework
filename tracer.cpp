#include "severity.h"
#include "tracer.h"
#include "logmessage.h"

unsigned int Tracer::indent_ = 0;

Tracer::Tracer(const QString& func_name, const QString& params)
    : func_name_(func_name), out_param_("") {
  param_stream_.setString(&out_param_);
  LOG(DEBUG) << QString(indent_++, ' ') << func_name << "(" << params << ") >";
}

Tracer::~Tracer() {
  LOG(DEBUG) << QString(--indent_, ' ') << func_name_ << "(" << out_param_ << ") <";
}
