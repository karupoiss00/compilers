#pragma once
#include "Rule.h"
#include "TableRow.h"
#include "GetDirectionSymbols.h"

bool HasNonTerminal(size_t beginIndex, const std::vector<Rule>& rules, const std::string& nonTerminalName);

int GetCountOfIdenticalNonterminals(const std::vector<Rule>& rules, const std::string& nonTerminal);

void AddNonterminals(const std::vector<Rule>& rules, std::vector<TableRow>& table);

std::set<std::string> GetTerminalDirectionSymbols(const std::vector<Rule>& rules, const std::string& terminalName, const std::string& nonTerminalName);

void AddOtherTableStrFromRightPart(const std::vector<Rule>& rules, std::vector<TableRow>& table, const Rule& rule);

std::vector<TableRow> CreateTable(const std::vector<Rule>& rules);