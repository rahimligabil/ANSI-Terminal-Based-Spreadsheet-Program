#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <vector>
#include "Cell.h"
#include "FormulaParser.h"
#include "AnsiTerminal.h"

class Spreadsheet {
private:
    int row,col;
    std::vector<std::vector<Cell>> sheet;  // 2D cell matric
    FormulaParser parser;  // Formula parser object

public:
    Spreadsheet(int rows, int cols);
    Cell& getCell(int row, int col);
    bool isNumber(const std::string& str);
    void updateCellFormula(int row, int col, const std::string& formula);
    void printSheet(AnsiTerminal &terminal, Spreadsheet &sheet) ;
    bool saveToFile(const string& filename) const;
    bool loadFromFile(const std::string& filename);
};

#endif // SPREADSHEET_H
