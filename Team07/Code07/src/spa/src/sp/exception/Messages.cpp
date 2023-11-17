#include "Messages.h"

namespace SP {

extern const std::string TOKENIZER_INVALID_OPERATION =
    "Invalid operation! Valid operations are && || >= <= == !=";
extern const std::string TOKENIZER_INVALID_SPECIAL_TOKEN =
    "Invalid special token! Valid special tokens are { } ( ) ; % + - * / > < = "
    "! & |";

extern const std::string PARSER_NO_INPUT = "Input file is empty";
extern const std::string PARSER_INVALID_STMT_START =
    "Statement list must start with a name!";
extern const std::string PARSER_INVALID_STMT_ENTITY =
    "Invalid statement entity! Valid statement entities are read, print, "
    "assign, call, while, if";
extern const std::string PARSER_NO_STMT =
    "Statement list must contain at least 1 statement!";
extern const std::string PARSER_NO_ASSIGN_RHS =
    "RHS of assign statement cannot be empty!";
extern const std::string PARSER_INVALID_CONDITIONAL =
    "Conditional expression is invalid!";

extern const std::string SP_MANAGER_INVALID_FILE = "Invalid input file!";

extern const std::string DUPLICATED_PROCEDURE = "Duplicated procedure name!";
extern const std::string CALL_NON_EXSISTENT_PROCEDURE =
    "Called non-existent procedure!";
extern const std::string RECURSIVE_OR_CYCLIC_CALL =
    "Recursive/Cyclic call detected!";
}  // namespace SP
