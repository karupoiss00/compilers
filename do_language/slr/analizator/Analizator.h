#pragma once
#include <istream>
#include <string>
#include <sstream>
#include <iostream>

#include "Table.h"
#include "Rule.h"
#include "StringHelpers.h"

void Analyze(const Table& table, const std::vector<Rule>& grammar, std::istream& input);