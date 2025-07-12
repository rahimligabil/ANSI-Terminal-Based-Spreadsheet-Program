#ifndef CELL_H
#define CELL_H

#include <string>
#include <memory>

namespace Spreadsheet {

class Cell {
public:
    virtual ~Cell() = default;
    virtual double getValue() const = 0;
    virtual void setValue(double value) = 0;
    virtual void setFormula(const std::string& formula) = 0;
    virtual std::string getFormula() const = 0;
    virtual void updateValue(const std::shared_ptr<std::shared_ptr<std::shared_ptr<Cell>[]>[]> &sheet) = 0;
};

} // namespace Spreadsheet

#endif // CELL_H
