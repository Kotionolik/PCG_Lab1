#include "rgbxyzlab.h"
#include "ui_rgbxyzlab.h"

rgbxyzlab::rgbxyzlab(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::rgbxyzlab)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    setXYZ(0, 0, 0);
    setLab(0, 0, 0);
    img = new QPixmap(ui->label->size());
    ui->label->setPixmap(*img);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(colorpicker()));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), ui->horizontalSlider, SLOT(setValue(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->spinBox, SLOT(setValue(int)));
    connect(ui->spinBox_2, SIGNAL(valueChanged(int)), ui->horizontalSlider_2, SLOT(setValue(int)));
    connect(ui->horizontalSlider_2, SIGNAL(valueChanged(int)), ui->spinBox_2, SLOT(setValue(int)));
    connect(ui->spinBox_3, SIGNAL(valueChanged(int)), ui->horizontalSlider_3, SLOT(setValue(int)));
    connect(ui->horizontalSlider_3, SIGNAL(valueChanged(int)), ui->spinBox_3, SLOT(setValue(int)));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(changevaluergb(int)));
    connect(ui->spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(changevaluergb(int)));
    connect(ui->spinBox_3, SIGNAL(valueChanged(int)), this, SLOT(changevaluergb(int)));

    connect(ui->spinBox_4, SIGNAL(valueChanged(int)), ui->horizontalSlider_4, SLOT(setValue(int)));
    connect(ui->horizontalSlider_4, SIGNAL(valueChanged(int)), ui->spinBox_4, SLOT(setValue(int)));
    connect(ui->spinBox_5, SIGNAL(valueChanged(int)), ui->horizontalSlider_6, SLOT(setValue(int)));
    connect(ui->horizontalSlider_6, SIGNAL(valueChanged(int)), ui->spinBox_5, SLOT(setValue(int)));
    connect(ui->spinBox_6, SIGNAL(valueChanged(int)), ui->horizontalSlider_8, SLOT(setValue(int)));
    connect(ui->horizontalSlider_8, SIGNAL(valueChanged(int)), ui->spinBox_6, SLOT(setValue(int)));
    connect(ui->spinBox_4, SIGNAL(valueChanged(int)), this, SLOT(changevaluexyz(int)));
    connect(ui->spinBox_5, SIGNAL(valueChanged(int)), this, SLOT(changevaluexyz(int)));
    connect(ui->spinBox_6, SIGNAL(valueChanged(int)), this, SLOT(changevaluexyz(int)));

    connect(ui->spinBox_7, SIGNAL(valueChanged(int)), ui->horizontalSlider_5, SLOT(setValue(int)));
    connect(ui->horizontalSlider_5, SIGNAL(valueChanged(int)), ui->spinBox_7, SLOT(setValue(int)));
    connect(ui->spinBox_8, SIGNAL(valueChanged(int)), ui->horizontalSlider_7, SLOT(setValue(int)));
    connect(ui->horizontalSlider_7, SIGNAL(valueChanged(int)), ui->spinBox_8, SLOT(setValue(int)));
    connect(ui->spinBox_9, SIGNAL(valueChanged(int)), ui->horizontalSlider_9, SLOT(setValue(int)));
    connect(ui->horizontalSlider_9, SIGNAL(valueChanged(int)), ui->spinBox_9, SLOT(setValue(int)));
    connect(ui->spinBox_7, SIGNAL(valueChanged(int)), this, SLOT(changevaluelab(int)));
    connect(ui->spinBox_8, SIGNAL(valueChanged(int)), this, SLOT(changevaluelab(int)));
    connect(ui->spinBox_9, SIGNAL(valueChanged(int)), this, SLOT(changevaluelab(int)));
}

double rgbxyzlab::rec(double x)
{
    if (x >= 0.008856)
    {
        x = pow(x, 3);
    }
    else
    {
        x = (x - 16/116)/7.787;
    }
    return x;
}
double rgbxyzlab::recrev(double x)
{
    if (x >= 0.008856)
    {
        x = pow(x, 1/3.0);
    }
    else
    {
        x = 7.787*x + 16/116;
    }
    return x;
}

void rgbxyzlab::colorpicker()
{
    QColor clr;
    clr = QColorDialog::getColor();
    if(clr.isValid() == false)
    {
        return;
    }
    ui->spinBox->setValue(clr.red());
    ui->spinBox_2->setValue(clr.green());
    ui->spinBox_3->setValue(clr.blue());
    img->fill(clr);
    ui->label->setPixmap(*img);
}
void rgbxyzlab::changevaluergb(int)
{
    if(!rgbchecker)
    {
        ui->label_5->setText("");
        xyzchecker = 1;
        labchecker = 1;
        QColor clr;
        clr.setRed(ui->spinBox->value());
        clr.setGreen(ui->spinBox_2->value());
        clr.setBlue(ui->spinBox_3->value());
        setXYZ(ui->spinBox->value(), ui->spinBox_2->value(), ui->spinBox_3->value());
        setLab(ui->spinBox->value(), ui->spinBox_2->value(), ui->spinBox_3->value());
        img->fill(clr);
        ui->label->setPixmap(*img);
        xyzchecker = 0;
        labchecker = 0;
    }
}
void rgbxyzlab::changevaluexyz(int)
{
    if(!xyzchecker)
    {
        rgbchecker = 1;
        labchecker = 1;
        QColor clr;
        clr = XYZColor(ui->spinBox_4->value(), ui->spinBox_5->value(), ui->spinBox_6->value());
        setLab(ui->spinBox->value(), ui->spinBox_2->value(), ui->spinBox_3->value());
        img->fill(clr);
        ui->label->setPixmap(*img);
        rgbchecker = 0;
        labchecker = 0;
    }
}
void rgbxyzlab::changevaluelab(int)
{
    if(!labchecker)
    {
        rgbchecker = 1;
        xyzchecker = 1;
        QColor clr;
        clr = LabColor(ui->spinBox_7->value(), ui->spinBox_8->value(), ui->spinBox_9->value());
        setXYZ(ui->spinBox->value(), ui->spinBox_2->value(), ui->spinBox_3->value());
        img->fill(clr);
        ui->label->setPixmap(*img);
        rgbchecker = 0;
        xyzchecker = 0;
    }
}

void rgbxyzlab::setXYZ(double r, double g, double b)
{
    r /= 255;
    g /= 255;
    b /= 255;
    if(r > 0.04045){
        r = pow((r + 0.055) / 1.055, 2.4);
    }else{
        r /= 12.92;
    }
    if(g>0.04045){
        g = pow((g + 0.055) / 1.055, 2.4);
    }else{
        g /= 12.92;
    }
    if(b>0.04045){
        b = pow((b + 0.055) / 1.055, 2.4);
    }else{
        b /= 12.92;
    }
    r *= 100;
    g *= 100;
    b *= 100;
    int x =(int)(r * 0.4124 + g * 0.3576 + b * 0.1805);
    int y = (int)(r * 0.2126 + g * 0.7152 + b * 0.0722);
    int z = (int)(r * 0.0193 + g * 0.1192 + b * 0.9505);
    ui->spinBox_4->setValue(x);
    ui->spinBox_5->setValue(y);
    ui->spinBox_6->setValue(z);
}
void rgbxyzlab::setLab(double r, double g, double b)
{
    double xw = 95.047, yw = 100, zw = 108.883;
    r /= 255;
    g /= 255;
    b /= 255;
    if(r > 0.04045){
        r = pow((r+0.055)/1.055, 2.4);
    }
    else
    {
        r /= 12.92;
    }
    if(g > 0.04045){
        g = pow((g + 0.055) / 1.055, 2.4);
    }
    else
    {
        g /= 12.92;
    }
    if(b > 0.04045){
        b = pow((b + 0.055) / 1.055, 2.4);
    }
    else
    {
        b /= 12.92;
    }
    r *= 100;
    g *= 100;
    b *= 100;
    double x = (int)(r * 0.4124 + g * 0.3576 + b * 0.1805), y = (int)(r * 0.2126 + g * 0.7152 + b * 0.0722), z = (int)(r * 0.0193 + g * 0.1192 + b * 0.9505);
    ui->spinBox_7->setValue((int)(116*recrev(y/yw) - 16));
    ui->spinBox_8->setValue((int)(500*(recrev(x/xw) - recrev(y/yw))));
    ui->spinBox_9->setValue((int)(200*(recrev(y/yw) - recrev(z/zw))));
}

QColor rgbxyzlab::XYZColor(double x, double y, double z)
{
    QColor color;
    double r, g, b;
    x /= 100;
    y /= 100;
    z /= 100;
    r = 3.2404542 * x - 0.4985314 * y - 0.4985314 * z;
    g = -0.9692660 * x + 1.8760108 * y + 0.0415560 * z;
    b = 0.0556434 * x - 0.2040259 * y + 1.0572252 * z;
    if(r >= 0.0031308){
        r = pow(r, 1 / 2.4) * 1.055 - 0.055;
    }
    else
    {
        r *= 12.92;
    }
    if(g >= 0.0031308){
        g = pow(g, 1 / 2.4) * 1.055 - 0.055;
    }
    else
    {
        g *= 12.92;
    }
    if(b >= 0.0031308){
        b = pow(b, 1 / 2.4) * 1.055 - 0.055;
    }
    else
    {
        b *= 12.92;
    }
    r = (int)(r * 255);
    g = (int)(g * 255);
    b = (int)(b * 255);
    if(r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
    {
        ui->label_5->setText("");
    }
    else
    {
        if(r < 0)
        {
            r = 0;
            ui->label_5->setText("Внимание: одна из величин превысила допустимое значение");
        }
        else if (r > 255)
        {
            r = 255;
            ui->label_5->setText("Внимание: одна из величин превысила допустимое значение");
        }
        if(g < 0)
        {
            g = 0;
            ui->label_5->setText("Внимание: одна из величин превысила допустимое значение");
        }
        else if (g > 255)
        {
            g = 255;
            ui->label_5->setText("Внимание: одна из величин превысила допустимое значение");
        }
        if(b < 0)
        {
            b = 0;
            ui->label_5->setText("Внимание: одна из величин превысила допустимое значение");
        }
        else if (b > 255)
        {
            b = 255;
            ui->label_5->setText("Внимание: одна из величин превысила допустимое значение");
        }
    }
    ui->spinBox->setValue(r);
    ui->spinBox_2->setValue(g);
    ui->spinBox_3->setValue(b);
    color.setRgb(r, g, b);
    return color;
}
QColor rgbxyzlab::LabColor(double l, double a, double b)
{
    QColor color;
    double xw = 95.047, yw = 100, zw = 108.883;
    double x = rec(a / 500 + ((l + 16) / 116)) * yw, y = rec((l + 16) / 116) * xw, z = rec((l + 16) / 116 - b / 200) * zw;
    double r, g, bl;
    x/=100;
    y/=100;
    z/=100;
    r = 3.2404542 * x - 0.4985314 * y - 0.4985314 * z;
    g = -0.9692660 * x + 1.8760108 * y + 0.0415560 * z;
    bl = 0.0556434 * x - 0.2040259 * y + 1.0572252 * z;
    if(r >= 0.0031308){
        r = pow(r, 1 / 2.4) * 1.055 - 0.055;
    }
    else
    {
        r *= 12.92;
    }
    if(g >= 0.0031308){
        g = pow(g, 1 / 2.4) * 1.055 - 0.055;
    }
    else
    {
        g *=12.92;
    }
    if(b >= 0.0031308){
        bl= pow(b, 1 / 2.4) * 1.055 - 0.055;
    }
    else
    {
        bl *= 12.92;
    }
    r = (int)(r * 255);
    g = (int)(g * 255);
    bl = (int)(bl * 255);
    if(r >= 0 && r <= 255 && g >= 0 && g <= 255 && bl >= 0 && bl <= 255)
    {
        ui->label_5->setText("");
    }
    else
    {
        if(r < 0)
        {
            r = 0;
            ui->label_5->setText("Внимание: одна из величин превысила допустимое значение");
        }
        else if (r > 255)
        {
            r = 255;
            ui->label_5->setText("Внимание: одна из величин превысила допустимое значение");
        }
        if(g < 0)
        {
            g = 0;
            ui->label_5->setText("Внимание: одна из величин превысила допустимое значение");
        }
        else if (g > 255)
        {
            g = 255;
            ui->label_5->setText("Внимание: одна из величин превысила допустимое значение");
        }
        if(bl < 0)
        {
            bl = 0;
            ui->label_5->setText("Внимание: одна из величин превысила допустимое значение");
        }
        else if (bl > 255)
        {
            bl = 255;
            ui->label_5->setText("Внимание: одна из величин превысила допустимое значение");
        }
    }
    ui->spinBox->setValue(r);
    ui->spinBox_2->setValue(g);
    ui->spinBox_3->setValue(bl);
    color.setRgb(r, g, bl);
    return color;
}

rgbxyzlab::~rgbxyzlab()
{
    delete ui;
}
