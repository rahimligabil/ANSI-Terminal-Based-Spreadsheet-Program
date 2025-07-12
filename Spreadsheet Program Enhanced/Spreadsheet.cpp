#include "Spreadsheet.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
using namespace std;

namespace Spreadsheet {

Spreadsheet::Spreadsheet(int rows, int cols) : rows(rows), cols(cols) {
    sheet = shared_ptr<shared_ptr<shared_ptr<Cell>[]>[]>(new shared_ptr<shared_ptr<Cell>[]>[rows]);
    for (int i = 0; i < rows; ++i) {
        sheet[i] = shared_ptr<shared_ptr<Cell>[]>(new shared_ptr<Cell>[cols]);
        for (int j = 0; j < cols; ++j) {
            sheet[i][j] = make_shared<IntValueCell>();
        }
    }
}

Cell& Spreadsheet::getCell(int row, int col) {
    return *sheet[row][col];
}

void Spreadsheet::updateCellFormula(int row, int col, const string& input) {
    // Eğer formül girilmişse
    if (input[0] == '=') {
        auto formulaCell = dynamic_pointer_cast<FormulaCell>(sheet[row][col]);
        if (!formulaCell) {
            // Hücreyi formül hücresine dönüştür
            formulaCell = make_shared<FormulaCell>();
            sheet[row][col] = formulaCell;
        }
        formulaCell->setFormula(input);
        formulaCell->updateValue(sheet);
    } 
    // Eğer sayı girilmişse
    else if (isNumber(input)) {
        auto valueCell =dynamic_pointer_cast<DoubleValueCell>(sheet[row][col]);
        if (!valueCell) {
            // Hücreyi sayı hücresine dönüştür
            valueCell = make_shared<DoubleValueCell>();
            sheet[row][col] = valueCell;
        }
        valueCell->setValue(stod(input));
    } 
    
    // Eğer string girilmişse
    else {
        auto stringCell = dynamic_pointer_cast<StringValueCell>(sheet[row][col]);
        if (!stringCell) {
            // Hücreyi string hücresine dönüştür
            stringCell = make_shared<StringValueCell>();
            sheet[row][col] = stringCell;
        }
        stringCell->setFormula(input); // String hücresinde değer tutmak için formül alanını kullanıyoruz
    }
}
bool Spreadsheet::isNumber(const string& str) {
    istringstream ss(str);
    double d;
    return (ss >> d) && ss.eof(); // Eğer sayı olarak okunabiliyorsa true döner
}

void Spreadsheet::updateAllFormulas() {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            auto formulaCell = dynamic_pointer_cast<FormulaCell>(sheet[row][col]);
            if (formulaCell) {
                formulaCell->updateValue(sheet); // Formülü yeniden hesapla
            }
        }
    }
}





void Spreadsheet::printSheet(AnsiTerminal& terminal) const {
    const_cast<Spreadsheet*>(this)->updateAllFormulas(); // Formülleri güncelle

    terminal.clearScreen();
        for (int i = 0; i < cols; ++i) {
        char columnLabel = 'A' + (i % 26); // Sütun isimleri A'dan Z'ye
        terminal.printAt(1, 4 + i * 9, string(1, columnLabel));
    }

    // Satır başlıklarını yazdır (1, 2, 3, ...)
    for (int i = 0; i < rows; ++i) {
        terminal.printAt(2 + i, 1, to_string(i + 1));
    }


    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            ostringstream cellValueStream;
            cellValueStream << fixed << setprecision(2) << sheet[row][col]->getValue();

            // Sabit genişlikte hücre yazdırma
            string cellValueStr = cellValueStream.str();
            terminal.printAt(2 + row, 4 + col * 9, cellValueStr); // 9 karakterlik aralık
        
            if (col < cols - 1) {
                terminal.printAt(2 + row, 4 + (col + 1) * 9 - 1, "|");
            }        
        }

    }
}

int Spreadsheet::getrow(){
    return rows;
}
int Spreadsheet::getcol(){
    return cols;
}

void Spreadsheet::addRows(int count) {
     auto newSheet = shared_ptr<shared_ptr<shared_ptr<Cell>[]>[]>(new shared_ptr<shared_ptr<Cell>[]>[rows + count]);
     for(int i=0;i<rows;i++){
        newSheet[i] = sheet[i];
     }
     for(int i=rows;i<rows + count;i++){
        newSheet[i] = shared_ptr<shared_ptr<Cell>[]>(new shared_ptr<Cell>[cols]);
        for (int j = 0; j < cols; ++j) {
            newSheet[i][j] = make_shared<IntValueCell>(); // Yeni hücreler oluştur
        }
     }
     sheet = move(newSheet);
     rows += count;
}
void Spreadsheet::addCols(int count){
    auto newSheet = shared_ptr<shared_ptr<shared_ptr<Cell>[]>[]>(new shared_ptr<shared_ptr<Cell>[]>[rows]);
    for(int i=0;i<rows;i++){
        newSheet[i] = shared_ptr<shared_ptr<Cell>[]>(new shared_ptr<Cell>[cols + count]);
    }
    for(int i=0;i<rows;i++){
        for (int j = 0; j < cols; ++j) {
            newSheet[i][j] = sheet[i][j];
        }
    }

for(int i=0;i<rows;i++){
    for (int j = cols; j < cols + count; ++j) {
            newSheet[i][j] = make_shared<IntValueCell>(); // Varsayılan hücre tipi
        }
}

    sheet = move(newSheet);
    cols += count;

    
}

bool Spreadsheet::saveToFile(const string& filename) const {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for writing: " << filename << endl;
        return false;
    }

    for (int i = 0; i < rows; ++i) { // Satırları gez
        for (int j = 0; j < cols; ++j) { // Sütunları gez
            const auto& cell = sheet[i][j];
            // Hücrenin formülü boşsa değerini yaz, aksi takdirde formülünü yaz
            outFile << (cell->getFormula().empty() ? to_string(cell->getValue()) : cell->getFormula());
            if (j != cols - 1) outFile << ","; // Hücreleri virgülle ayır
        }
        outFile << "\n"; // Satır sonu
    }
    return true;
}

bool Spreadsheet::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }

    string line;
    int rowIdx = 0;

    while (getline(inFile, line) && rowIdx < rows) { // Satırları oku
        stringstream ss(line);
        string cellValue;
        int colIdx = 0;

        while (getline(ss, cellValue, ',') && colIdx < cols) { // Hücreleri virgülle ayır
            updateCellFormula(rowIdx, colIdx, cellValue);
            ++colIdx;
        }
        ++rowIdx;
    }
    return true;
}


} // namespace Spreadsheet
