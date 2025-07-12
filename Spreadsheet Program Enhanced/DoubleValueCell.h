#ifndef DOUBLEVALUECELL_H
#define DOUBLEVALUECELL_H

#include "Cell.h"

namespace Spreadsheet {

class DoubleValueCell : public Cell {
    double value;
public:
    DoubleValueCell();
    double getValue() const override;
    void setValue(double val) override;
    void setFormula(const std::string& formula) override;
    std::string getFormula() const override;
    void updateValue(const std::shared_ptr<std::shared_ptr<std::shared_ptr<Cell>[]>[]> &sheet) override;
};

} // namespace Spreadsheet

#endif // DOUBLEVALUECELL_H
