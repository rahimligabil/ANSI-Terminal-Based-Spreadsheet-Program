#ifndef INTVALUECELL_H
#define INTVALUECELL_H

#include "Cell.h"

namespace Spreadsheet {

class IntValueCell : public Cell {
    int value;
public:
    IntValueCell();
    double getValue() const override;
    void setValue(double val) override;
    void setFormula(const std::string& formula) override;
    std::string getFormula() const override;
    void updateValue(const std::shared_ptr<std::shared_ptr<std::shared_ptr<Cell>[]>[]> &sheet) override;
};

} // namespace Spreadsheet

#endif // INTVALUECELL_H
