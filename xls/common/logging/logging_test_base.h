// Copyright 2020 The XLS Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef XLS_COMMON_LOGGING_LOGGING_TEST_BASE_H_
#define XLS_COMMON_LOGGING_LOGGING_TEST_BASE_H_

#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "absl/base/log_severity.h"
#include "absl/log/log_entry.h"
#include "absl/log/log_sink.h"

namespace xls {
namespace logging_internal {
namespace testing {

struct CapturedLogEntry {
  CapturedLogEntry();
  explicit CapturedLogEntry(const ::absl::LogEntry& entry);

  std::string text_message;
  absl::LogSeverity log_severity;
  int verbosity = 0;
  std::string source_filename;
  std::string source_basename;
  int source_line = 0;
  bool prefix = false;
};

class LoggingTestBase : public ::testing::Test, public ::absl::LogSink {
 public:
  LoggingTestBase();

  ~LoggingTestBase() override;

  void Send(const ::absl::LogEntry& entry) override;

  CapturedLogEntry GetSingleEntry();

 protected:
  std::vector<CapturedLogEntry> entries_;
};

}  // namespace testing
}  // namespace logging_internal
}  // namespace xls

#endif  // XLS_COMMON_LOGGING_LOGGING_TEST_BASE_H_
