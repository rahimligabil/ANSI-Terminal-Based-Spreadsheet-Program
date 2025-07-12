#include "IntValueCell.h"

namespace Spreadsheet {

IntValueCell::IntValueCell() : value(0) {}

double IntValueCell::getValue() const {
    return value;
}

void IntValueCell::setValue(double val) {
    value = static_cast<int>(val);
}

void IntValueCell::setFormula(const std::string& formula) {}

std::string IntValueCell::getFormula() const {
    return "";
}

void IntValueCell::updateValue(const std::shared_ptr<std::shared_ptr<std::shared_ptr<Cell>[]>[]> &sheet) {}

} // namespace Spreadsheet
