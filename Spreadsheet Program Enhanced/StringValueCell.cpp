#include "StringValueCell.h"

namespace Spreadsheet {

StringValueCell::StringValueCell() : value("") {}

double StringValueCell::getValue() const {
    return 0.0; // Strings do not have a numeric value
}

void StringValueCell::setValue(double val) {}

void StringValueCell::setFormula(const std::string& formula) {
    value = formula;
}

std::string StringValueCell::getFormula() const {
    return value;
}

void StringValueCell::updateValue(const std::shared_ptr<std::shared_ptr<std::shared_ptr<Cell>[]>[]> &sheet) {}

} // namespace Spreadsheet
