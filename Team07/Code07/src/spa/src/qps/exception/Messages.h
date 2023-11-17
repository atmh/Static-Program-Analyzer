#pragma once

#include <string>

namespace QPS {
static inline const std::string INVALID_TOKEN =
    "Invalid special token! Valid special tokens are ( ) _ \" + - * / % , ; < "
    "> .";
static inline const std::string INVALID_DECLARATION = "Invalid Declaration!";
static inline const std::string INVALID_CLAUSE = "Invalid Clause!";
static inline const std::string INVALID_SELECT_CLAUSE =
    "Invalid Select Clause!";
static inline const std::string INVALID_SUCH_THAT_CLAUSE =
    "Invalid Such That Clause!";
static inline const std::string INVALID_PATTERN_CLAUSE =
    "Invalid Pattern Clause!";
static inline const std::string INVALID_STMT_REF =
    "Invalid Statement Reference!";
static inline const std::string INVALID_ENT_REF = "Invalid Entity Reference!";
static inline const std::string INVALID_REF = "Invalid Reference!";
static inline const std::string INVALID_EXPRESSION = "Invalid Expression!";
static inline const std::string INVALID_ATTR_NAME = "Invalid Attribute!";
static inline const std::string REPEATED_DECLARATION = "Repeated Declaration!";
}  // namespace QPS
