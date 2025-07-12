#include "FormulaParser.h"
#include <stdexcept>
#include <sstream>
#include <numeric>
#include <cmath>
#include <iostream>

using namespace std;
using namespace Spreadsheet;

FormulaParser::FormulaParser() {}

double FormulaParser::parseFormula(const string& formula, const std::shared_ptr<std::shared_ptr<std::shared_ptr<Cell>[]>[]> &sheet) {
    if (formula.empty()) return 0;

    if (formula[0] == '=') {
        return parseAssignment(formula.substr(1), sheet);
    }

    if (formula.find("MAX") != string::npos) {
        return parseFunction(formula, sheet, "MAX");
    }
    if (formula.find("AVER") != string::npos) {
        return parseFunction(formula, sheet, "AVER");
    }
    if (formula.find("SUM") != string::npos) {
        return parseFunction(formula, sheet, "SUM");
    }
    if (formula.find("STDDEV") != string::npos) {
        return parseFunction(formula, sheet, "STDDEV");
    }
    if (formula.find("MIN") != string::npos) {
        return parseFunction(formula, sheet, "MIN");
    }
    return parseExpression(formula, sheet);
}

float FormulaParser::parseAssignment(const string& formula,const std::shared_ptr<std::shared_ptr<std::shared_ptr<Cell>[]>[]> &sheet) {
    return parseExpression(formula, sheet);
}

double FormulaParser::parseExpression(const string& formula,const std::shared_ptr<std::shared_ptr<std::shared_ptr<Cell>[]>[]> &sheet) {
    istringstream ss(formula);
    string token;

    vector<double> values;
    vector<char> operators;

    while (ss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            operators.push_back(token[0]);
        } else {
            double value;
            if (isalpha(token[0]) && token.find('(') == string::npos) {
                value = getCellValue(token, sheet);
            } else if (token.find("SUM") != string::npos) {
                value = parseFunction(token, sheet, "SUM");
            } else if (token.find("AVER") != string::npos) {
                value = parseFunction(token, sheet, "AVER");
            } else if (token.find("MAX") != string::npos) {
                value = parseFunction(token, sheet, "MAX");
            } else if (token.find("MIN") != string::npos) {
                value = parseFunction(token, sheet, "MIN");
            } else if (token.find("STDDEV") != string::npos) {
                value = parseFunction(token, sheet, "STDDEV");
            } else {
                value = stod(token);
            }

            if (!operators.empty() && (operators.back() == '*' || operators.back() == '/')) {
                char op = operators.back();
                operators.pop_back();

                double lastValue = values.back();
                values.pop_back();

                if (op == '*') value = lastValue * value;
                else if (op == '/') {
                    if (value != 0) value = lastValue / value;
                    else {
                        cerr << "Error: Dividing by zero!" << endl;
                        return 0;
                    }
                }
            }
            values.push_back(value);
        }
    }

    double result = values[0];
    for (size_t i = 0; i < operators.size(); ++i) {
        if (operators[i] == '+') result += values[i + 1];
        else if (operators[i] == '-') result -= values[i + 1];
    }

    return result;
}

float FormulaParser::getCellValue(const string& token,const std::shared_ptr<std::shared_ptr<std::shared_ptr<Cell>[]>[]> &sheet) {
    int row = token[1] - '1';
    int col = token[0] - 'A';
    return sheet[row][col]->getValue();
}

float FormulaParser::parseFunction(const string& formula,const std::shared_ptr<std::shared_ptr<std::shared_ptr<Cell>[]>[]> &sheet, const string& function) {
    size_t start = formula.find("(");
    size_t end = formula.find(")");

    if (start == string::npos || end == string::npos) {
        throw invalid_argument("Invalid function format.");
    }

    string args = formula.substr(start + 1, end - start - 1);

    if (function == "MAX") {
        return maxv(args, sheet);
    } else if (function == "AVER") {
        return average(args, sheet);
    } else if (function == "SUM") {
        return sum(args, sheet);
    } else if (function == "MIN") {
        return minv(args, sheet);
    } else if (function == "STDDEV") {
        return stddev(args, sheet);
    }

    return 0;
}


double FormulaParser:: maxv(const string& range,const std::shared_ptr<std::shared_ptr<std::shared_ptr<Cell>[]>[]> &sheet) {
    char startCol = range[0];
    int startRow = stoi(range.substr(1, range.find("..") - 1)) - 1;
    char endCol = range[range.find("..") + 2];
    int endRow = stoi(range.substr(range.find("..") + 3)) - 1;

    // find max in range
    double maxVal = -100000000; // first minimum value
    for (int row = startRow; row <= endRow; ++row) {
        for (char col = startCol; col <= endCol; ++col) {
            int colIndex = col - 'A';
            if(maxVal < sheet[row][colIndex]->getValue()){
                maxVal = sheet[row][colIndex]->getValue();
            }
        }
    }

    return maxVal;
}

double FormulaParser::average(const string& range,const std::shared_ptr<std::shared_ptr<std::shared_ptr<Cell>[]>[]> &sheet) {
    char startCol = range[0];
    int startRow = stoi(range.substr(1, range.find("..") - 1)) - 1;
    char endCol = range[range.find("..") + 2];
    int endRow = stoi(range.substr(range.find("..") + 3)) - 1; // formula parse
    double sum = 0.0;
    int count = 0;
    // find average in range
    for (char col = startCol; col <= endCol; ++col) {
        for (int row = startRow; row <= endRow; ++row){
            int colIndex = col - 'A';
            sum = sum + sheet[row][colIndex]->getValue();
            count++;
}
    }
    sum = sum / count; //divide sum with couunt
    cout << sum;
    return sum;
}

double FormulaParser::sum(const string& range,const std::shared_ptr<std::shared_ptr<std::shared_ptr<Cell>[]>[]> &sheet) {
     char startCol = range[0];
    int startRow = stoi(range.substr(1, range.find("..") - 1)) - 1;
    char endCol = range[range.find("..") + 2];
    int endRow = stoi(range.substr(range.find("..") + 3)) - 1;
    double sum = 0.0;
    // find sum in range
    for (char col = startCol; col <= endCol; ++col) {
        for (int row = startRow; row <= endRow; ++row){
            int colIndex = col - 'A';
            sum = sum + sheet[row][colIndex]->getValue(); //get cell value
}
    }
    return sum;
}

double FormulaParser::stddev(const string& range,const std::shared_ptr<std::shared_ptr<std::shared_ptr<Cell>[]>[]> &sheet) {
    double mean = average(range,sheet); //get average
    char startCol = range[0];
    int startRow = stoi(range.substr(1, range.find("..") - 1)) - 1;
    char endCol = range[range.find("..") + 2];
    int endRow = stoi(range.substr(range.find("..") + 3)) - 1;
    double sum = 0.0;
    //find standart deviation
    int count = 0;
    for (int row = startRow; row <= endRow; ++row) {
        for (char col = startCol; col <= endCol; ++col) {
            int colIndex = col - 'A';
            sum = sum + ((sheet[row][colIndex]->getValue() - mean) * (sheet[row][colIndex]->getValue() - mean));
            count++;
}
    }
    sum = sum / count; //divide sum with member count
    return sqrt(sum);
}

double FormulaParser::minv(const string& range,const std::shared_ptr<std::shared_ptr<std::shared_ptr<Cell>[]>[]> &sheet) {
    char startCol = range[0];
    int startRow = stoi(range.substr(1, range.find("..") - 1)) - 1;
    char endCol = range[range.find("..") + 2];
    int endRow = stoi(range.substr(range.find("..") + 3)) - 1;


    double minVal = 100000; // big value first
    for (int row = startRow; row <= endRow; ++row) {
        for (char col = startCol; col <= endCol; ++col) {
            int colIndex = col - 'A';
            if(minVal > sheet[row][colIndex]->getValue()){ //find min in range
                minVal = sheet[row][colIndex]->getValue();
            }

        }
    }
    return minVal;
}
