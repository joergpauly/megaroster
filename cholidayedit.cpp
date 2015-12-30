#include "cholidayedit.h"
#include "ui_cholidayedit.h"

CHolidayEdit::CHolidayEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CHolidayEdit)
{
    ui->setupUi(this);
}

CHolidayEdit::~CHolidayEdit()
{
    delete ui;
}
