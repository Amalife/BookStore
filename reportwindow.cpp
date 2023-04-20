#include "reportwindow.h"
#include "ui_reportwindow.h"

ReportWindow::ReportWindow(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::ReportWindow)
{
    ui->setupUi(this);
    connect(ui->closeButton, &QPushButton::pressed, this, &ReportWindow::close);
}

ReportWindow::~ReportWindow()
{
    delete ui;
}

void ReportWindow::setReport(Report *report)
{
    ui->booksSold->setText(QString::fromUtf8(std::to_string(report->getSoldBooks()).c_str()));
    ui->ordersMade->setText(QString::fromUtf8(std::to_string(report->getMadeOrders()).c_str()));
    ui->requestMade->setText(QString::fromUtf8(std::to_string(report->getMadeRequest()).c_str()));
    ui->income->setText(QString::fromUtf8(std::to_string(report->getIncome()).c_str()));
    ui->consumption->setText(QString::fromUtf8(std::to_string(report->getConsum()).c_str()));
    ui->profit->setText(QString::fromUtf8(std::to_string(report->getIncome() - report->getConsum()).c_str()));
}
