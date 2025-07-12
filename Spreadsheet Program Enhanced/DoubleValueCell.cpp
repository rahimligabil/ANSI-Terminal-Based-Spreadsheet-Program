#include "DoubleValueCell.h"

namespace Spreadsheet {

DoubleValueCell::DoubleValueCell() : value(0.0) {}

double DoubleValueCell::getValue() const {
    return value;
}

void DoubleValueCell::setValue(double val) {
    value = val;
}

void DoubleValueCell::setFormula(const std::string& formula) {}

std::string DoubleValueCell::getFormula() const {
    return "";
}

void DoubleValueCell::updateValue(const std::shared_ptr<std::shared_ptr<std::shared_ptr<Cell>[]>[]> &sheet) {}

} // namespace Spreadsheet
