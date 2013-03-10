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

private:

};

class Nightcharts : public QObject
{
    Q_ENUMS(type)
public:    

    explicit Nightcharts(QObject* parent = 0);
    ~Nightcharts();
    enum type { Histogramm , Pie, Dpie };
    enum legend_type{ Vertical, Round };
    void addPiece(QString name,Qt::GlobalColor,float Percentage);
    void addPiece(QString name,QColor, float Percentage);
    void addPiece(pieceNC piece);
    void setCords(double x, double y, double w, double h);
    void setLegendCords(double x, double y);
    void setType(Nightcharts::type t);
    void setLegendType(Nightcharts::legend_type t);
    void setShadows(bool ok = true);
    void setLegendFont(QFont f);
    void setChartFont(QFont f);
    void draw(QPainter *painter);
    void drawLegend(QPainter *painter);
    double palpha;
    void setIsPercent(bool b ){isPercent = b;}
private:
    double cX,cY,cW,cH,pW,lX,lY;
    bool shadows;
    QVector<pieceNC> pieces;
    int ctype, cltype;
    QFont font;
    QFont chart_font;
    //QPainter *cpainter;
    QPointF GetPoint(double angle, double R1 = 0, double R2 = 0);
    int GetQuater(double angle);
    double Angle360(double angle);

    bool isPercent;
signals:

public slots:

};


#endif // NIGHTCHARTS_H