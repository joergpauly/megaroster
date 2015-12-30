#ifndef CHOLIDAYEDIT_H
#define CHOLIDAYEDIT_H

#include <QDialog>

namespace Ui {
class CHolidayEdit;
}

class CHolidayEdit : public QDialog
{
    Q_OBJECT

public:
    explicit CHolidayEdit(QWidget *parent = 0);
    ~CHolidayEdit();

private:
    Ui::CHolidayEdit *ui;
};

#endif // CHOLIDAYEDIT_H
