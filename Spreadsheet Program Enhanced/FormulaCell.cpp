#include "FormulaCell.h"

namespace Spreadsheet {

FormulaCell::FormulaCell() : formula(""), value(0.0) {}

double FormulaCell::getValue() const {
    return value;
}

void FormulaCell::setValue(double val) {
    value = val;
}

void FormulaCell::setFormula(const std::string& newFormula) {
    formula = newFormula;
}

std::string FormulaCell::getFormula() const {
    return formula;
}

void FormulaCell::updateValue(const std::shared_ptr<std::shared_ptr<std::shared_ptr<Cell>[]>[]> &sheet) {
    if (!formula.empty() && formula[0] == '=') {
        value = parser.parseFormula(formula, sheet);
    }
}

} // namespace Spreadsheet
