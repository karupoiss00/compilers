#include "GetDirectionSymbols.h"

//Добавление новых направляющих символов
bool AddNewSymbols(std::vector<Symbol>& currentDirectionSymbols, const std::vector<Symbol>& newDirectionSymbols)
{
    bool hasChange = false;

    for (const Symbol& dirSymbol : newDirectionSymbols)
    {
        if (std::find(currentDirectionSymbols.begin(), currentDirectionSymbols.end(), dirSymbol) == currentDirectionSymbols.end())
        {
            currentDirectionSymbols.insert(currentDirectionSymbols.end(), dirSymbol);
            hasChange = true;
        }
    }

    return hasChange;
}

//Получение всех направляющих символов у нетерминала
std::vector<Symbol> DefineNonTerminalDirectionSymbols(const std::string& nonTerminalName, const std::vector<Rule>& rules)
{
    std::vector<Symbol> directionSymbols;
    //Проходится по всем правилам заданного нетерминала
    //и добавяляет его направляющие символы
    for (const Rule& rule : rules)
    {
        if (rule.nonTerminal == nonTerminalName)
        {
            directionSymbols.insert(directionSymbols.end(), rule.directionSymbols.begin(), rule.directionSymbols.end());
        }
    }

    return directionSymbols;
}

//Определение символов, которые используюся после заданного нетерминала в правиле
std::vector<Symbol> GetDirectionSymbolsAfterNonTerminal(const Rule& rule, size_t numOfRule, const std::string& nonTerminalName, const std::vector<Rule>& rules, std::set<size_t> checkedRulesIndexes)
{
    std::vector<Symbol> directionSymbols;
    //Определение позиции нетерминала в правиле
    auto it = std::find(rule.rightPart.begin(), rule.rightPart.end(), nonTerminalName);
    //Обход всех позиций заданного нетерминала в правиле
    while (it != rule.rightPart.end())
    {
        it++;
        //Если нетерминал вызывается в конце правила,
        //то определяются символы, вызывающиеся после нетерминала,
        //в правиле которого используется заданный нетерминал
        if (it == rule.rightPart.end())
        {
            std::vector<Symbol> symbols = DefineDirectionSymbolsAfterNonTerminal(checkedRulesIndexes, rule.nonTerminal, rules);
            directionSymbols.insert(directionSymbols.end(), symbols.begin(), symbols.end());
            continue;
        }
        // Если следующий элемент - нетерминал,
        //то находим направляющие символы этого нетерминала
        if (IsNonTerminal(*it, rules))     {
            std::vector<Symbol> symbols = DefineNonTerminalDirectionSymbols(*it, rules);
            directionSymbols.insert(directionSymbols.end(), symbols.begin(), symbols.end());
        }
        //Добавляем этот элемент в направляющие символы
        Symbol symbol;
        symbol.name = *it;
        symbol.numOfRule = numOfRule;
        symbol.numOfRightPart = it - rule.rightPart.begin();
        directionSymbols.insert(directionSymbols.end(), symbol);
        //Определяем используется ли еще заданный нетерминал в этом правиле
        it = std::find(it, rule.rightPart.end(), nonTerminalName);
    }
    return directionSymbols;
}

//Нахождение символов, которые находятся после нетерминала в грамматике
std::vector<Symbol> DefineDirectionSymbolsAfterNonTerminal(std::set<size_t> checkedRulesIndexes, const std::string& nonTerminalName, const std::vector<Rule>& rules)
{
    std::vector<Symbol> directionSymbols;
    //Обход правил в грамматике
    for (size_t i = 0; i < rules.size(); i++)
    {
        //Проверка на то, что правило под этим номером проверено
        if (checkedRulesIndexes.find(i) != checkedRulesIndexes.end())
        {
            continue;
        }
        //Опредление символов, которые находятся после вызова нетерминала в правиле
        std::set<size_t> newCheckedRulesIndexes = checkedRulesIndexes;
        newCheckedRulesIndexes.insert(i);
        const Rule& rule = rules[i];
        std::vector<Symbol> symbols = GetDirectionSymbolsAfterNonTerminal(rule, i, nonTerminalName, rules, newCheckedRulesIndexes);
        directionSymbols.insert(directionSymbols.end(), symbols.begin(), symbols.end());
    }

    return directionSymbols;
}

void DefineDirectionSymbols(std::vector<Rule>& rules)
{
    bool hasChanges = false;
    // Обход правил в грамматике
    for (size_t i = 0; i < rules.size(); i++)
    {
        Rule& rule = rules[i];
        //Проверка на то, что правило не имеет элементов
        if (rule.rightPart.size() == 0)
        {
            throw std::logic_error("right part is empty");
        }
        //Проверка на то, что правило пустое
        if (rule.rightPart.size() == 1 && rule.rightPart[0] == EMPTY_SYMBOL)
        {
            //Опредление символов, которые находятся после вызова нетерминала с пустым правилом в грамматике
            std::vector<Symbol> directionSymbols = DefineDirectionSymbolsAfterNonTerminal({}, rule.nonTerminal, rules);
            hasChanges = hasChanges ? true : AddNewSymbols(rule.directionSymbols, directionSymbols);
            continue;
        }
        // Проверка первого элемента правила на нетерминал
        if (IsNonTerminal(rule.rightPart[0], rules))
        {
            // Нахождение направляющих символов первого элемента правила
            std::vector<Symbol> directionSymbols = DefineNonTerminalDirectionSymbols(rule.rightPart[0], rules);
            hasChanges = hasChanges ? true : AddNewSymbols(rule.directionSymbols, directionSymbols);
        }
        // Первый элемент является направляющим символом
        size_t sizeBefore = rule.directionSymbols.size();
        Symbol symbol;
        symbol.name = rule.rightPart[0];
        symbol.numOfRule = i;
        symbol.numOfRightPart = 0;
        hasChanges = hasChanges ? true : AddNewSymbols(rule.directionSymbols, { symbol });
    }

    // Если найдены новые направляющие символы для нетерминалов в грамматике,
    //то производится повторное нахождение направляющих символов
    if (hasChanges)
    {
        DefineDirectionSymbols(rules);
    }
}