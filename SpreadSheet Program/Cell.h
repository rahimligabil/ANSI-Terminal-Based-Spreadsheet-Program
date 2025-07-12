#ifndef CELL_H
#define CELL_H

#include <string>
#include <vector>

class FormulaParser;  // forward declaration
class Cell {
private:
    int row, col; // row and col
    std::string formula;  //formul of cell
    double value;  // value of cell
public:
    void updateValue(const std::vector<std::vector<Cell>>& sheet, FormulaParser& parser);
    void setValue(double newValue);
    Cell(int r, int c);
    void setFormula(const std::string& formula);
    double getValue() const;
    std::string getformul()const;
    int getrow() const;
    int getcol() const;
};

#endif // CELL_H
