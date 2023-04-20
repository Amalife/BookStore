#ifndef REPORTWINDOW_H
#define REPORTWINDOW_H

#include <QWidget>

#include "report.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ReportWindow; }
QT_END_NAMESPACE

class ReportWindow : public QWidget
{
    Q_OBJECT
public:
    ReportWindow(QWidget *parent = nullptr);
    ~ReportWindow();

    void setReport(Report *report);

private:
    Ui::ReportWindow *ui;
};

#endif // REPORTWINDOW_H
