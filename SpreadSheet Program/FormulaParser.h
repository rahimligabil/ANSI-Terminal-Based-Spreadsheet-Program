#ifndef FORMULAPARSER_H
#define FORMULAPARSER_H

#include <string>
#include <vector>
#include "Cell.h"
using namespace std;
class FormulaParser {
public:
    FormulaParser();
    double parseFormula(const std::string& formula, const std::vector<std::vector<Cell>>& sheet);
private:
    float parseAssignment(const std::string& formula, const std::vector<std::vector<Cell>>& sheet);
    double parseExpression(const std::string& formula, const std::vector<std::vector<Cell>>& sheet);
    float getCellValue(const std::string& token, const std::vector<std::vector<Cell>>& sheet);
    float parseFunction(const std::string& formula, const std::vector<std::vector<Cell>>& sheet, const std::string& function);
    double average(const string& formula, const vector<vector<Cell>>& sheet);
    double sum(const string& formula, const vector<vector<Cell>>& sheet);
    double minv(const std::string& formula, const std::vector<std::vector<Cell>>& sheet);
    double stddev(const string& formula, const vector<vector<Cell>>& sheet);
    double maxv(const string& formula, const vector<vector<Cell>>& sheet);
};


#endif // FORMULAPARSER_H
