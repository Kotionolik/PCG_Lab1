#ifndef RGBXYZLAB_H
#define RGBXYZLAB_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <cmath>
#include <QColor>
#include <QColorDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class rgbxyzlab;
}
QT_END_NAMESPACE

class rgbxyzlab : public QWidget
{
    Q_OBJECT

public slots:
    void colorpicker();
    void changevaluergb(int);
    void changevaluexyz(int);
    void changevaluelab(int);

public:
    rgbxyzlab(QWidget *parent = nullptr);
    ~rgbxyzlab();
    QColor XYZColor(double x, double y, double z);
    QColor LabColor(double l, double a, double b);
    void setXYZ(double r, double g, double b);
    void setLab(double r, double g, double b);
    double rec(double x);
    double recrev(double x);

private:
    Ui::rgbxyzlab *ui;
    QPixmap* img;
    bool xyzchecker = 0, labchecker = 0, rgbchecker = 0;
};
#endif // RGBXYZLAB_H
