#pragma once

#include <iostream>
#include <list>
#include <memory>
#include <string>

// include your other headers here
#include "AbstractWrapper.h"
#include "SPA.h"
#include "pkb/PKBStorageAPI.h"

class TestWrapper : public AbstractWrapper {
 public:
  // default constructor
  TestWrapper();

  // destructor
  ~TestWrapper();

  // method for parsing the SIMPLE source
  virtual void parse(std::string filename);

  // method for evaluating a query
  virtual void evaluate(std::string query, std::list<std::string>& results);

 private:
  SPA::SPA spa;
};
