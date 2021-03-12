#ifndef CLASSUNITWIGGET_H
#define CLASSUNITWIGGET_H

#include <QWidget>

namespace Ui {
class ClassUnitWigget;
}

class ClassUnitWigget : public QWidget
{
    Q_OBJECT

public:
    explicit ClassUnitWigget(QWidget *parent = nullptr);
    ~ClassUnitWigget();

private:
    Ui::ClassUnitWigget *ui;
};

#endif // CLASSUNITWIGGET_H
