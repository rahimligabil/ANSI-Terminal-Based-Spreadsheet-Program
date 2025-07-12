#ifndef FORMULAPARSER_H
#define FORMULAPARSER_H

#include <string>
#include <vector>
#include <memory>
#include "Cell.h"

class FormulaParser {
public:
    FormulaParser();
    double parseFormula(const std::string& formula, const std::shared_ptr<std::shared_ptr<std::shared_ptr<Spreadsheet::Cell>[]>[]> &sheet);

private:
    float parseAssignment(const std::string& formula, const std::shared_ptr<std::shared_ptr<std::shared_ptr<Spreadsheet::Cell>[]>[]> &sheet);
    double parseExpression(const std::string& formula, const std::shared_ptr<std::shared_ptr<std::shared_ptr<Spreadsheet::Cell>[]>[]> &sheet);
    float getCellValue(const std::string& token, const std::shared_ptr<std::shared_ptr<std::shared_ptr<Spreadsheet::Cell>[]>[]> &sheet);
    float parseFunction(const std::string& formula, const std::shared_ptr<std::shared_ptr<std::shared_ptr<Spreadsheet::Cell>[]>[]> &sheet, const std::string& function);
    double average(const std::string& range, const std::shared_ptr<std::shared_ptr<std::shared_ptr<Spreadsheet::Cell>[]>[]> &sheet);
    double sum(const std::string& range, const std::shared_ptr<std::shared_ptr<std::shared_ptr<Spreadsheet::Cell>[]>[]> &sheet);
    double minv(const std::string& range, const std::shared_ptr<std::shared_ptr<std::shared_ptr<Spreadsheet::Cell>[]>[]> &sheet);
    double stddev(const std::string& range, const std::shared_ptr<std::shared_ptr<std::shared_ptr<Spreadsheet::Cell>[]>[]> &sheet);
    double maxv(const std::string& range, const std::shared_ptr<std::shared_ptr<std::shared_ptr<Spreadsheet::Cell>[]>[]> &sheet);
};

#endif // FORMULAPARSER_H
