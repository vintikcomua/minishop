#ifndef TABLELISTVIEW_H
#define TABLELISTVIEW_H

#include <QWidget>

namespace Ui {
class TableListView;
}

class TableListView : public QWidget
{
    Q_OBJECT

public:
    explicit TableListView(QWidget *parent = nullptr);
    ~TableListView();

private:
    Ui::TableListView *ui;
};

#endif // TABLELISTVIEW_H
