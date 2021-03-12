#include "classunitwigget.h"
#include "ui_classunitwigget.h"

ClassUnitWigget::ClassUnitWigget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClassUnitWigget)
{
    ui->setupUi(this);
}

ClassUnitWigget::~ClassUnitWigget()
{
    delete ui;
}
