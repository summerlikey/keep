#ifndef ADDITEM_H
#define ADDITEM_H

#include <QDialog>
#include<QString>
#include<QButtonGroup>
#include<QAbstractButton>
#include<QFile>
namespace Ui {
class addItem;
}

class addItem : public QDialog
{
    Q_OBJECT

public:
    explicit addItem(QWidget *parent = nullptr);
    ~addItem();
    void clearAddItem();
    void writeToFile(QString cnt);

private:
    Ui::addItem *ui;
    QButtonGroup *MoneyToGroup;
    QButtonGroup *MoneyFromGroup;

private slots:
    void addItemClose();
    void addItemConfirm();
};

#endif // ADDITEM_H
