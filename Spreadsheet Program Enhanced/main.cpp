#include "AnsiTerminal.h"
#include "Spreadsheet.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

using namespace std;
using namespace Spreadsheet;

int main() {
    AnsiTerminal terminal;
    int rows = 24; // Başlangıç satır sayısı
    int cols = 10; // Başlangıç sütun sayısı
    Spreadsheet::Spreadsheet sheet(rows, cols);
    int row = 0, col = 0;

    // Terminal renklerini ayarla (arka plan siyah, yazı rengi yeşil)
    cout << "\033[40m\033[32m"; // Siyah arka plan, yeşil yazı
    terminal.clearScreen();
    sheet.printSheet(terminal);

    while (true) {
        // Geçerli hücreyi vurgula
        std::ostringstream cellValueStream;
        double currentValue = sheet.getCell(row, col).getValue();
        cellValueStream << std::fixed << std::setprecision(2) << currentValue;
        std::string currentValueStr = cellValueStream.str();

        cout << "\033[102m\033[30m"; // İmleç için açık yeşil arka plan, siyah yazı
        terminal.printAt(2 + row, 4 + col * 9, currentValueStr);

        cout << "\033[40m\033[32m"; // Varsayılan renkler

        char key = terminal.getSpecialKey();
        if (key == 'q') break; // Çıkış

        // Önceki hücreyi eski rengine döndür
        terminal.printAt(2 + row, 4 + col * 9, currentValueStr);

        // İmleç hareketi veya işlem seçimi
        switch (key) {
            case 'U': 
                row = (row > 0) ? row - 1 : row; 
                break; // Yukarı
            case 'D': 
                row++;
                if (row >= rows) {
                    sheet.addRows(1); // Dinamik satır ekleme
                    rows++;
                    terminal.clearScreen();
                    sheet.printSheet(terminal);
                }
                break; // Aşağı
            case 'L': 
                col = (col > 0) ? col - 1 : col; 
                break; // Sol
            case 'R': 
                col++;
                if (col >= cols) {
                   sheet.addCols(1); // Dinamik sütun ekleme
                    cols++;
                    terminal.clearScreen();
                    sheet.printSheet(terminal);
                }
                break; // Sağ
            case 'J': { // Hücreye değer gir
                terminal.printAt(sheet.getrow() + 2, 1, "Enter value (press Enter to save): ");
                string input = "";
                char ch;
                while (true) {
                    ch = getchar(); // Karakter oku
                    if (ch == '\n') break; // Enter basıldığında çık
                    if (ch == 127 || ch == 8) { // Backspace için
                        if (!input.empty()) {
                            input.pop_back();
                            terminal.printAt(sheet.getrow() + 2, 35, string(input.size() + 1, ' ')); // Önceki metni sil
                            terminal.printAt(sheet.getrow() + 2, 35, input); // Yeni metni yazdır
                        }
                    } else {
                        input += ch; // Karakteri ekle
                        terminal.printAt(sheet.getrow() + 2, 35, input);
                    }
                }

                sheet.updateCellFormula(row, col, input);
                terminal.clearScreen();
                sheet.printSheet(terminal);
                terminal.printAt(sheet.getrow() + 2, 1, string(50, ' ')); // Mesaj alanını temizle
                break;
            }
            case 's': { // CSV'ye kaydet
                terminal.printAt(26, 1, "Enter file name to save (e.g., data.csv): ");
                string filename;
                getline(cin, filename);
                if (sheet.saveToFile(filename)) {
                    terminal.printAt(26, 1, "File saved successfully!");
                } else {
                    terminal.printAt(26, 1, "Error saving file.");
                }
                break;
            }
            case 'l': { // CSV'den yükle
                terminal.printAt(26, 1, "Enter file name to load (e.g., data.csv): ");
                string filename;
                getline(cin, filename);
                if (sheet.loadFromFile(filename)) {
                    terminal.clearScreen();
                    sheet.printSheet(terminal);
                    terminal.printAt(26, 1, "File loaded successfully!");
                } else {
                    terminal.printAt(26, 1, "Error loading file.");
                }
                break;
            }
        }
    }

    // Çıkışta terminal renklerini sıfırla
    cout << "\033[0m"; // Renkleri varsayılan hale döndür
    terminal.clearScreen(); // Ekranı temizle
    return 0;
}
