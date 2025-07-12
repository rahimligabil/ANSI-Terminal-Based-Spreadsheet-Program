#ifndef STRINGVALUECELL_H
#define STRINGVALUECELL_H

#include "Cell.h"

namespace Spreadsheet {

class StringValueCell : public Cell {
    std::string value;
public:
    StringValueCell();
    double getValue() const override;
    void setValue(double val) override;
    void setFormula(const std::string& formula) override;
    std::string getFormula() const override;
    void updateValue(const std::shared_ptr<std::shared_ptr<std::shared_ptr<Cell>[]>[]> &sheet) override;
};

} // namespace Spreadsheet

#endif // STRINGVALUECELL_H
