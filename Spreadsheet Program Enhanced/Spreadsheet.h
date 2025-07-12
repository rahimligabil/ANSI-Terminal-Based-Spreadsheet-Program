#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <vector>
#include <string>
#include <memory>
#include "Cell.h"
#include "AnsiTerminal.h"
#include "FormulaCell.h"
#include "IntValueCell.h"
#include "DoubleValueCell.h"
#include "StringValueCell.h"
#include <memory>
using namespace std;
namespace Spreadsheet {

class Spreadsheet {
    int rows, cols;
    shared_ptr<shared_ptr<shared_ptr<Cell>[]>[]> sheet;

public:
    bool isNumber(const std::string& str);
    Spreadsheet(int rows, int cols);
    Cell& getCell(int row, int col);
    void updateAllFormulas();
    int getrow();
    int getcol();
    void addRows(int count);
    void addCols(int count);
    void updateCellFormula(int row, int col, const std::string& input);
    void printSheet(AnsiTerminal& terminal) const; 
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
};

} // namespace Spreadsheet

#endif // SPREADSHEET_H
