#include "Spreadsheet.h"
#include <iostream>
#include <sstream>
#include "FormulaParser.h"
#include "Cell.h"
#include <iomanip>
#include <fstream>

Spreadsheet::Spreadsheet(int rows, int cols) {//constructor
     row = rows;
     col = cols;
    for (int r = 0; r < rows; ++r) {
        std::vector<Cell> row;
        for (int c = 0; c < cols; ++c) {
            row.push_back(Cell(r, c));
        }
        sheet.push_back(row);
    }
}

Cell& Spreadsheet::getCell(int row, int col) {
    return sheet[row][col];
}

 void Spreadsheet::updateCellFormula(int row, int col, const std::string& input) {
    //check for formula or value 
    if (isNumber(input)) {
        double value = stod(input);
        sheet[row][col].setValue(value);

    } else {
        sheet[row][col].setFormula(input);  // if formul set
        sheet[row][col].updateValue(sheet, parser);
    }

    
 }


   bool Spreadsheet::isNumber(const std::string& str) {
    std::istringstream ss(str);
    double d;
    return (ss >> d) && ss.eof(); // it reads only number
}


void Spreadsheet:: printSheet(AnsiTerminal &terminal, Spreadsheet &sheet) {
      // col names (A, B, C, ..., Z)
    for (int i = 0; i < col; ++i) {
        char columnLabel = 'A' + (i % 26); // range from  A to Z
        terminal.printAt(1, 4 + i * 9, string(1, columnLabel)); // for cell head
    }

    // row number
    for (int i = 0; i < row; ++i) {
        terminal.printAt(2 + i, 1, to_string(i + 1));  
            }

    // for cell value
    
for (int r = 0; r < row; ++r) {
    for (int c = 0; c < col; ++c) {
        updateCellFormula(r, c, sheet.getCell(r, c).getformul());
        
        // it get cell value and use precision
        double cellValueDouble = sheet.getCell(r, c).getValue();
        std::ostringstream cellValueStream;
        cellValueStream << std::fixed << std::setprecision(2) << cellValueDouble;
        std::string cellValue = cellValueStream.str();
        
        // print cell and set | 
        terminal.printAt(2 + r, 4 + c * 9, cellValue); // print cell value
        if (c < 79) { // if not end set | 
            terminal.printAt(2 + r, 4 + (c + 1) * 9 - 1, "|");
        }
    }
}

}

bool Spreadsheet::saveToFile(const string& filename) const {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error opening file for writing: " << filename << endl;
        return false;
    }

    for (const auto& row : sheet) {
        for (size_t i = 0; i < row.size(); ++i) {
            if(!(row[i].getformul().empty())){
            outFile << row[i].getformul(); // if formul not empty getformul
            }
            else{
                 outFile << to_string(row[i].getValue()); // if it is value convert string
            }
            if (i != row.size() - 1) {
                outFile << ",";
            }
        }
        outFile << endl;
    }

    outFile.close(); // close file
    return true;
}

bool Spreadsheet::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);  // open file readmode
     if (!inFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::string line;
    int row1 = 0;
    while (std::getline(inFile, line) && row1 < row) {  //read from file col
        std::stringstream ss(line);
        std::string cellValue;
        int col1 = 0;  // for col number
        while (std::getline(ss, cellValue, ',') && col1 < col) {  // divide cell with ','
            // set cell values from file
            updateCellFormula(row1, col1, cellValue);
            col1++;
        }
        row1++;
    }

    inFile.close();  // close file
    return true;
}


