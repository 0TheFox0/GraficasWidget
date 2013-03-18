/*
 * NightCharts
 * Copyright (C) 2010 by Alexander A. Avdonin, Artem N. Ivanov / ITGears Co.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * Please contact gordos.kund@gmail.com with any questions on this license.
 */
#ifndef NIGHTCHARTS_H
#define NIGHTCHARTS_H
#define PerConst = 3.6;
#define _USE_MATH_DEFINES
#include <QObject>
#include <QPainter>
#include <QVector>
#include <QPair>
#include <QDebug>
#include <QLinearGradient>
#include <math.h>

class pieceNC
{
public:
    explicit pieceNC();
    void addName(QString name);
    void setColor(Qt::GlobalColor);
    void setColor(QColor color);
    void setPerc(float Percentage);
    void setCuanty(float f){cuanty = f;}

    QString pname;
    QColor rgbColor;
    float pPerc;
    float cuanty;

    QVector< QPair<float,float> >values;
    float maxValue;
    float minValue;

private:

};

class lineNC
{
public:
    QString name;
    QVector<float> points;
    QColor color;
};

class Nightcharts : public QObject
{
    Q_ENUMS(type)
public:    

    explicit Nightcharts(QObject* parent = 0);
    ~Nightcharts();
    enum type {  Histogramm , DoubleBar , Pie, Dpie , Lines };
    enum legend_type{ Vertical, Round };
    void addPiece(QString name,Qt::GlobalColor,float Percentage);
    void addPiece(QString name,QColor, float Percentage);

    void addPiece(QString name,Qt::GlobalColor,QVector<float>values);
    void addPiece(QString name,QColor, QVector<float>values);
    void addPiece(QString name,QColor, QVector< QPair <float, float > >values);

    void addPiece(pieceNC piece);
    void addPiece4Multi(pieceNC piece);

    void addLine(lineNC lNc);
    void addLines(QVector< lineNC> lines);
    void addLineStop(QString s){LinesStop.append(s);}
    void addLineStops(QStringList sl){LinesStop = sl;}

    void setCords(double x, double y, double w, double h);
    void setLegendCords(double x, double y);
    void setType(Nightcharts::type t);
    void setLegendType(Nightcharts::legend_type t);
    void setShadows(bool ok = true);
    void setLabels(bool ok = true);
    void setValues(bool ok = true);
    void setLegendFont(QFont f);
    void setChartFont(QFont f);
    void draw(QPainter *painter);
    void drawLegend(QPainter *painter);
    double palpha;
    void setIsPercent(bool b ){isPercent = b; m_total = 100;}
    void drawDPie(QPainter *painter);
    void drawPie(QPainter *painter);
    void drawHistogramm(QPainter *painter);
    void drawDoubleBar(QPainter *painter);
    void drawLines(QPainter *painter);

    void getPieceValue(float Percentage, pieceNC * piece);
    void getPieceMultiValues(pieceNC * piece);
    void addDoubleBarColor(QString,QColor);
    void addDoubleBarColor(QPair<QString,QColor> pair);
    void drawDoubleBarLegend(QPainter *painter);
    void drawLinesLegend(QPainter * painter);
    void drawYValues(QPainter * painter);
    void setYvalues(bool b);
private:

    double m_left,m_top,m_width,m_heigth,m_xAxisPos,pW,legend_X,legend_Y;
    bool shadows;
    bool labels;
    bool values;
    bool yValues;
    QVector<pieceNC> pieces;
    QVector<QPair<QString , QColor> >DoubleBarColors;

    QStringList LinesStop;
    QVector< lineNC > lineas;

    int ctype, cltype;
    QFont font;
    QFont chart_font;
    QPointF GetPoint(double angle, double R1 = 0, double R2 = 0);
    int GetQuater(double angle);
    double Angle360(double angle);

    bool isPercent;
    int m_total;
    float m_maxValue;
    float m_mayor;
    float m_menor;
signals:

public slots:

};


#endif // NIGHTCHARTS_H
