#include "Cell.h"
#include "FormulaParser.h"
#include <iostream>

Cell::Cell(int r, int c) : row(r), col(c), value(0), formula("") {} // constructor

void Cell::setFormula(const std::string& formula) { // set formuk
    this->formula = formula;
}

void Cell::updateValue(const std::vector<std::vector<Cell>>& sheet, FormulaParser& parser) {
    if (!formula.empty()) {
        value = parser.parseFormula(formula, sheet);  //if new formula given
    }
}
std::string Cell::getformul()const{

    return formula;
}

void Cell::setValue(double newValue) {
        value = newValue;
        formula = "";  // if formul set ""
    }

double Cell::getValue() const {
    return value;
}

int Cell::getrow()const{
    return row;
} 
int Cell::getcol()const{
    return col;
}