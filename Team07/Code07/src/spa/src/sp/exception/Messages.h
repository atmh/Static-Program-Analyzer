#pragma once

#include <string>

namespace SP {
extern const std::string TOKENIZER_INVALID_OPERATION;
extern const std::string TOKENIZER_INVALID_SPECIAL_TOKEN;

extern const std::string PARSER_NO_INPUT;
extern const std::string PARSER_INVALID_STMT_START;
extern const std::string PARSER_INVALID_STMT_ENTITY;
extern const std::string PARSER_NO_STMT;
extern const std::string PARSER_NO_ASSIGN_RHS;
extern const std::string PARSER_INVALID_CONDITIONAL;

extern const std::string SP_MANAGER_INVALID_FILE;

extern const std::string DUPLICATED_PROCEDURE;
extern const std::string CALL_NON_EXSISTENT_PROCEDURE;
extern const std::string RECURSIVE_OR_CYCLIC_CALL;
}  // namespace SP
