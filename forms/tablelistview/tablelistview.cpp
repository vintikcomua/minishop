#include "tablelistview.h"
#include "ui_tablelistview.h"

TableListView::TableListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableListView)
{
    ui->setupUi(this);
}

TableListView::~TableListView()
{
    delete ui;
}
