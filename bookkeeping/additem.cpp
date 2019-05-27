#include "additem.h"
#include "ui_additem.h"
#include<QTime>
#include<QDebug>
#include<QDate>
#include<QString>
#include<QMessageBox>
addItem::addItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addItem)
{
    ui->setupUi(this);

    MoneyFromGroup = new QButtonGroup(this);
    MoneyFromGroup -> QButtonGroup::addButton( ui -> huabei_rbtn,0 );
    MoneyFromGroup ->addButton(this -> ui -> bank_rbtn,1);
    ui->huabei_rbtn->setChecked(true);
    MoneyFromGroup ->setExclusive(true);;

    MoneyToGroup = new QButtonGroup(this);
    MoneyToGroup -> addButton(ui->bus_rbtn,0);
    MoneyToGroup ->addButton(ui->book_rbtn,1);
    MoneyToGroup ->addButton(ui->snack_rbtn,2);
    MoneyToGroup ->addButton(ui->stucard_rbtn,3);
    MoneyToGroup ->addButton(ui->wearing_rbtn,4);
    MoneyToGroup ->addButton(ui->school_rbtn,5);
    MoneyToGroup ->addButton(ui->film_rbtn,6);
    MoneyToGroup ->addButton(ui->dinner_rbtn,7);
    MoneyToGroup ->addButton(ui->sports_rbtn,8);
    MoneyToGroup ->addButton(ui->turism_rbtn,9);
    ui -> stucard_rbtn-> setChecked(true);
    MoneyToGroup ->setExclusive(true);

    this->ui->lineedit_money->setPlaceholderText("请输入花费￥");
    this -> ui->lineedit_money->setFocus();
    QDate todayDate=QDate::currentDate();
    QString dateformat="dd.MM.yyyy";
    QString str_date=todayDate.QDate::toString(dateformat);
    //str_date="今天 "+str_date;
    this->ui->cbb_date->setItemText(1,str_date);
    qint64 ndays=1;
    QDate tomorrowDate = todayDate.QDate::addDays(ndays);
    str_date=tomorrowDate.QDate::toString(dateformat);
    //str_date="明天 "+str_date;
    this->ui->cbb_date->setItemText(0,str_date);
    ndays=-1;
    QDate yesterdayDate = todayDate.QDate::addDays(ndays);
    str_date=yesterdayDate.QDate::toString(dateformat);
    //str_date="昨天 "+str_date;
    this->ui->cbb_date->setItemText(2,str_date);
    qDebug()<<ui->cbb_date->currentText();

    connect(this->ui->close_btn,SIGNAL(clicked()),this,SLOT(addItemClose()));
    connect(this ->ui->confirm_btn,SIGNAL(clicked()),this,SLOT(addItemConfirm()));

}

addItem::~addItem()
{
    delete ui;
}
void addItem::addItemConfirm()
{
    QString itemdate = ui -> cbb_date -> currentText();
    QString itemmoney = ui->lineedit_money ->text();
    QString itemmoneyfrom = MoneyFromGroup->checkedButton()->text();
    QString itemmoneyto = MoneyToGroup->checkedButton()->text();
    QDate todayDate=QDate::currentDate();
    QString dateformat="dd.MM.yyyy";
    QString str_date=todayDate.QDate::toString(dateformat);
    QString content = "today:"+str_date + '\n'+"the item date:"+itemdate+'\n'+"money:"+itemmoney+'\n'+"money from:"+itemmoneyfrom+'\n'+"money to:"+ itemmoneyto +'\n';
    QString ins = itemdate + ' ' +itemmoney+' '+itemmoneyfrom+' '+itemmoneyto+'\n';
    if(itemmoney.length()<1||itemmoney.length()>8)
    {
        QMessageBox::critical(this,"ERROR","INFORMATION IS NOT COMPLETE","CONFIRM");
    }
    else {
        int ret=QMessageBox::question(this,"PLEASE CONFIRM INFORMATION",content,"CONFIRM","CANCEL");
        if(ret==0)
            clearAddItem();
        writeToFile(ins);
    }

}
void addItem :: writeToFile(QString cnt)
{
    QFile file("moneybook.txt");
    if(!file.open(QIODevice::Append|QIODevice::Text))
    {
        QMessageBox::critical(this,"error","con not open file","information not save","confirm");
        return;
    }
    QTextStream out(&file);
    out<<cnt;
    file.close();

}
void addItem::clearAddItem()
{
    ui->stucard_rbtn->setChecked(true);
    ui->huabei_rbtn->setChecked(true);
    ui->cbb_date->setCurrentIndex(1);
    ui->lineedit_money->clear();
    ui->lineedit_money->setFocus();
}

void addItem::addItemClose()
{
    this->close();
}
