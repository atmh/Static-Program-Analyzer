//
// Created by Ramapriyan Srivatsan PD on 12/11/23.
//

namespace PKB {
class PKBStorageType {
 public:
  enum class Type {
    FOLLOWS,
    PARENT,
    MODIFIES_PROCEDURE,
    MODIFIES_STATEMENT,
    USES_PROCEDURE,
    USES_STATEMENT,
    CALLS,
    NEXT,
    ASSIGN,
    CALL_STATEMENT,
    CONSTANT,
    IF,
    PRINT_STATEMENT,
    PROCEDURE,
    READ_STATEMENT,
    VARIABLE,
    WHILE
  };
};
}  // namespace PKB
