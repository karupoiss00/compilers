#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <format>

#include "TableRow.h"
#include "StringHelpers.h"

void Analyze(const std::vector<TableRow> table, const std::string& inputFileName);