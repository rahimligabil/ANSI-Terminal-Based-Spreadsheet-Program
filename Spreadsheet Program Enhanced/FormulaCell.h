#ifndef FORMULACELL_H
#define FORMULACELL_H

#include "Cell.h"
#include "FormulaParser.h"
#include <memory>
#include <string>

namespace Spreadsheet {

class FormulaCell : public Cell {
public:
    FormulaCell();
    ~FormulaCell() override = default;

    double getValue() const override;
    void setValue(double val) override;
    void setFormula(const std::string& newFormula) override;
    std::string getFormula() const override;
    void updateValue(const std::shared_ptr<std::shared_ptr<std::shared_ptr<Cell>[]>[]> &sheet) override;

private:
    std::string formula;
    double value;
    FormulaParser parser;
};

} // namespace Spreadsheet

#endif // FORMULACELL_H
