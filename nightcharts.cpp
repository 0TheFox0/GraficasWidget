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
#include "nightcharts.h"
#include <QGraphicsScene>

Nightcharts::Nightcharts(QObject *parent):
    QObject(parent)

{
    font.setFamily("verdana");
    font.setPixelSize(15);
    ctype = Nightcharts::Dpie;
    cltype = Nightcharts::Vertical;
    m_left = 0;
    m_top = 0;
    m_width = 100;
    m_xAxisPos = 100;
    legend_X = m_left+m_width+20;
    legend_Y = m_top;
    shadows = true;
    m_total = 100;
    m_mayor = 0;
    m_menor = 0;
}
Nightcharts::~Nightcharts()
{
    pieces.clear();
}

void Nightcharts::getPieceValue(float Percentage, pieceNC *piece)
{
    m_menor = qMin(m_menor,Percentage);
    m_mayor = qMax(m_mayor, Percentage);

    if(Percentage >=0)
        m_maxValue = qMax(m_maxValue,Percentage);
    else
         m_maxValue = qMax(m_maxValue,-Percentage);

    if(isPercent)
    {
        for (int i = 0; i< pieces.size();i++)
            pieces[i].setPerc(pieces.at(i).cuanty*100/m_maxValue);
        piece->setPerc(Percentage*100/m_maxValue);
        piece->setCuanty(Percentage);
        m_total = 100;
        m_xAxisPos = m_top + m_heigth - 15;
        pieces.append(*piece);
    }
    else
    {
        int range = m_mayor;

        if(m_menor < 0)
            range -= m_menor;

        for (int i = 0; i< pieces.size();i++)
        {
            if(pieces.at(i).cuanty >0 )
                pieces[i].setPerc(pieces.at(i).cuanty*100/range);
            else
                pieces[i].setPerc(-pieces.at(i).cuanty*100/range);
        }

        if(Percentage > 0)
            piece->setPerc(Percentage*100/range);
        else
            piece->setPerc(-Percentage*100/range);

        piece->setCuanty(Percentage);
        pieces.append(*piece);

        if(m_mayor == m_maxValue)
        {
            for(int i=0;i<pieces.size();i++)
            {
                if(pieces.at(i).cuanty == m_mayor)
                {
                    double x = pieces.at(i).pPerc/100;
                    int y = m_heigth*x;
                    m_xAxisPos = m_top + y -12;
                    break;
                }
            }
        }
        else
        {
            for(int i=0;i<pieces.size();i++)
            {
                if(pieces.at(i).cuanty == m_menor)
                {
                    double x = pieces.at(i).pPerc/100;
                    int y = m_heigth*x;
                    m_xAxisPos = m_top + m_heigth - y - 5;
                    break;
                }
            }
        }
    }
}

void Nightcharts::getPieceMultiValues(pieceNC *piece)
{
    for(int i=0;i<piece->values.size();i++)
    {
        float Percentage = piece->values.at(i).first;
        m_menor = qMin(m_menor,Percentage);
        m_mayor = qMax(m_mayor, Percentage);

        piece->minValue = qMin(piece->minValue, Percentage);
        piece->maxValue = qMax(piece->maxValue, Percentage);

        if(Percentage >=0)
        {
            m_maxValue = qMax(m_maxValue,Percentage);
            piece->maxValue = qMax(piece->maxValue,Percentage);
        }
        else
        {
            m_maxValue = qMax(m_maxValue,-Percentage);
            piece->maxValue = qMax(piece->maxValue,-Percentage);
        }
    }
    int range = m_mayor;

    if(m_menor < 0)
        range -= m_menor;

    for (int i = 0; i< pieces.size();i++)
    {
        for(int a=0; a<pieces.at(i).values.size();a++)
        {
            if(pieces.at(i).values.at(a).first > 0 )
                pieces[i].values[a].second =   pieces.at(i).values.at(a).first*100/range;
            else
                pieces[i].values[a].second = -pieces.at(i).values.at(a).first*100/range;
        }
    }

    for (int i=0; i < piece->values.size();i++)
    {
        if(piece->values.at(i).first > 0)
            piece->values[i].second = piece->values.at(i).first*100/range;
        else
            piece->values[i].second = -piece->values.at(i).first*100/range;
    }

    pieces.append(*piece);

    if(m_mayor == m_maxValue)
    {
        for(int i=0;i<pieces.size();i++)
        {
            for(int a=0;a<pieces.at(i).values.size();a++)
            {
                if(pieces.at(i).values.at(a).first == m_mayor)
                {
                    double x = pieces.at(i).values.at(a).second/100;
                    int y = m_heigth*x;
                    m_xAxisPos = m_top + y -12;
                    return;
                }
            }
        }
    }
    else
    {
        for(int i=0;i<pieces.size();i++)
        {
            for(int a=0;a<pieces.at(i).values.size();a++)
            {
                if(pieces.at(i).values.at(a).first == m_menor)
                {
                    double x = pieces.at(i).values.at(a).second/100;
                    int y = m_heigth*x;
                    m_xAxisPos = m_top + m_heigth - y + 12;
                    break;
                }
            }
        }
    }
}

void Nightcharts::addDoubleBarColor(QString s , QColor c)
{
    QPair<QString,QColor> par;
    par.first = s;
    par.second = c;
    DoubleBarColors.append(par);
}

void Nightcharts::addDoubleBarColor(QPair<QString, QColor> pair)
{
    DoubleBarColors.append(pair);
}

void Nightcharts::addPiece(QString name,Qt::GlobalColor color,float Percentage)
{
    pieceNC piece;
    piece.addName(name);
    piece.setColor(color);
    getPieceValue(Percentage, &piece);
}
void Nightcharts::addPiece(QString name, QColor color, float Percentage)
{
    pieceNC piece;
    piece.addName(name);
    piece.setColor(color);
    getPieceValue(Percentage, &piece);
}

void Nightcharts::addPiece(QString name, Qt::GlobalColor color, QVector<float> values)
{
    pieceNC piece;
    piece.addName(name);
    piece.setColor(color);
    for(int i=0;i<values.size();i++)
    {
        QPair<float,float> par;
        par.first = values.at(i);
        par.second = 0;
        piece.values.append(par);
    }
    getPieceMultiValues(&piece);
}

void Nightcharts::addPiece(QString name, QColor color, QVector<float> values)
{
    pieceNC piece;
    piece.addName(name);
    piece.setColor(color);
    for(int i=0;i<values.size();i++)
    {
        QPair<float,float> par;
        par.first = values.at(i);
        par.second = 0;
        piece.values.append(par);
    }
    getPieceMultiValues(&piece);
}

void Nightcharts::addPiece(QString name, QColor color, QVector<QPair<float, float> > values)
{
    pieceNC piece;
    piece.addName(name);
    piece.setColor(color);
    piece.values = values;
    getPieceMultiValues(&piece);
}

void Nightcharts::addPiece(pieceNC piece)
{
    addPiece(piece.pname,piece.rgbColor,piece.cuanty);
}

void Nightcharts::addPiece4Multi(pieceNC piece)
{
    addPiece(piece.pname,piece.rgbColor,piece.values);
}
void Nightcharts::setCords(double x, double y, double w, double h)
{
    this->m_left = x+5;
    this->m_top = y+15;
    this->m_width = w-20;
    this->m_heigth = h-45;

    this->m_xAxisPos = h/2;

    this->legend_X = m_left+m_width+20;
    this->legend_Y = m_top;
}
void Nightcharts::setLegendCords(double x, double y)
{
    this->legend_X = x;
    this->legend_Y = y;
}

void Nightcharts::setType(Nightcharts::type t)
{
    this->ctype = t;
}

void Nightcharts::setLegendType(Nightcharts::legend_type t)
{
    this->cltype = t;
}
void Nightcharts::setLegendFont(QFont f)
{
    this->font = f;
}

void Nightcharts::setChartFont(QFont f)
{
    this->chart_font = f;
}

void Nightcharts::setShadows(bool ok)
{
    this->shadows = ok;
}

void Nightcharts::setLabels(bool ok)
{
    labels = ok;
}

void Nightcharts::setValues(bool ok)
{
    values = ok;
}

void Nightcharts::drawPie(QPainter *painter)
{
    pW = 0;
    double pdegree = 0;

    //Options
    QLinearGradient gradient(m_left+0.5*m_width,m_top,m_left+0.5*m_width,m_top+m_xAxisPos*2.5);
    gradient.setColorAt(1,Qt::black);


    //Draw
    //pdegree = (360/100)*pieces[i].pPerc;
    if (shadows)
    {
        double sumangle = 0;
        for (int i=0;i<pieces.size();i++)
        {
            sumangle += 3.6*pieces[i].pPerc;
        }
        painter->setBrush(Qt::darkGray);
        painter->drawPie(m_left,m_top+pW+5,m_width,m_xAxisPos,palpha*16,sumangle*16);
    }

    QPen pen;
    pen.setWidth(2);

    for (int i=0;i<pieces.size();i++)
    {
      gradient.setColorAt(0,pieces[i].rgbColor);
      painter->setBrush(gradient);
      pen.setColor(pieces[i].rgbColor);
      painter->setPen(pen);
      pdegree = 3.6*pieces[i].pPerc;
      painter->drawPie(m_left,m_top,m_width,m_xAxisPos,palpha*16,pdegree*16);
      palpha += pdegree;
    }
}

void Nightcharts::drawDPie(QPainter *painter)
{
    pW = 50;
    double pdegree = 0;
    QPointF p;

    QLinearGradient gradient(m_left-0.5*m_width,m_top+m_xAxisPos/2,m_left+1.5*m_width,m_top+m_xAxisPos/2);
    gradient.setColorAt(0,Qt::black);
    gradient.setColorAt(1,Qt::white);
    QLinearGradient gradient_side(m_left,m_top+m_xAxisPos,m_left+m_width,m_top+m_xAxisPos);
    gradient_side.setColorAt(0,Qt::black);

    double sumangle = 0;
    for (int i=0;i<pieces.size();i++)
    {
        sumangle += 3.6*pieces[i].pPerc;
    }
    if (shadows)
    {
        painter->setBrush(Qt::darkGray);
        painter->drawPie(m_left,m_top+pW+5,m_width,m_xAxisPos,palpha*16,sumangle*16);
    }
    int q = GetQuater(palpha+sumangle);

    if (q ==2 || q==3)
    {
        QPointF p = GetPoint(palpha+sumangle);
        QPointF points[4] =
        {
            QPointF(p.x(),p.y()),
            QPointF(p.x(),p.y()+pW),
            QPointF(m_left+m_width/2,m_top+m_xAxisPos/2+pW),
            QPointF(m_left+m_width/2,m_top+m_xAxisPos/2)
        };
        gradient_side.setColorAt(1,pieces[pieces.size()-1].rgbColor);
        painter->setBrush(gradient_side);
        painter->drawPolygon(points,4);
    }
    p = GetPoint(palpha);
    q = GetQuater(palpha);
    if (q ==1 || q==4)
    {
        QPointF points[4] =
        {
            QPointF(p.x(),p.y()),
            QPointF(p.x(),p.y()+pW),
            QPointF(m_left+m_width/2,m_top+m_xAxisPos/2+pW),
            QPointF(m_left+m_width/2,m_top+m_xAxisPos/2)
        };
        gradient_side.setColorAt(1,pieces[0].rgbColor);
        painter->setBrush(gradient_side);
        painter->drawPolygon(points,4);
    }

    for (int i=0;i<pieces.size();i++)
    {
      gradient.setColorAt(0.5,pieces[i].rgbColor);
      painter->setBrush(gradient);
      pdegree = 3.6*pieces[i].pPerc;
      painter->drawPie(m_left,m_top,m_width,m_xAxisPos,palpha*16,pdegree*16);

      double a_ = Angle360(palpha);
      int q_ = GetQuater(palpha);

      palpha += pdegree;

      double a = Angle360(palpha);
      int q = GetQuater(palpha);

      QPainterPath path;
      p = GetPoint(palpha);

      if((q == 3 || q == 4) && (q_ == 3 || q_ == 4))
      {
          // 1)
          if (a>a_)
          {
              QPointF p_old = GetPoint(palpha-pdegree);
              path.moveTo(p_old.x()-1,p_old.y());
              path.arcTo(m_left,m_top,m_width,m_xAxisPos,palpha-pdegree,pdegree);
              path.lineTo(p.x(),p.y()+pW);
              path.arcTo(m_left,m_top+pW,m_width,m_xAxisPos,palpha,-pdegree);
          }
          // 2)
          else
          {
              path.moveTo(m_left,m_top+m_xAxisPos/2);
              path.arcTo(m_left,m_top,m_width,m_xAxisPos,180,Angle360(palpha)-180);
              path.lineTo(p.x(),p.y()+pW);
              path.arcTo(m_left,m_top+pW,m_width,m_xAxisPos,Angle360(palpha),-Angle360(palpha)+180);
              path.lineTo(m_left,m_top+m_xAxisPos/2);

              path.moveTo(p.x(),p.y());
              path.arcTo(m_left,m_top,m_width,m_xAxisPos,palpha-pdegree,360-Angle360(palpha-pdegree));
              path.lineTo(m_left+m_width,m_top+m_xAxisPos/2+pW);
              path.arcTo(m_left,m_top+pW,m_width,m_xAxisPos,0,-360+Angle360(palpha-pdegree));
          }

      }
      // 3)
      else if((q == 3 || q == 4) && (q_ == 1 || q_ == 2) && a>a_ )
      {
          path.moveTo(m_left,m_top+m_xAxisPos/2);
          path.arcTo(m_left,m_top,m_width,m_xAxisPos,180,Angle360(palpha)-180);
          path.lineTo(p.x(),p.y()+pW);
          path.arcTo(m_left,m_top+pW,m_width,m_xAxisPos,Angle360(palpha),-Angle360(palpha)+180);
          path.lineTo(m_left,m_top+m_xAxisPos/2);
      }
      // 4)
      else if((q == 1 || q == 2) && (q_ == 3 || q_ == 4) && a<a_)
      {
          p = GetPoint(palpha-pdegree);
          path.moveTo(p.x(),p.y());
          path.arcTo(m_left,m_top,m_width,m_xAxisPos,palpha-pdegree,360-Angle360(palpha-pdegree));
          path.lineTo(m_left+m_width,m_top+m_xAxisPos/2+pW);
          path.arcTo(m_left,m_top+pW,m_width,m_xAxisPos,0,-360+Angle360(palpha-pdegree));
      }
      // 5)
      else if((q ==1 || q==2) && (q_==1 || q_==2) && a<a_)
      {
          path.moveTo(m_left,m_top+m_xAxisPos/2);
          path.arcTo(m_left,m_top,m_width,m_xAxisPos,180,180);
          path.lineTo(m_left+m_width,m_top+m_xAxisPos/2+pW);
          path.arcTo(m_left,m_top+pW,m_width,m_xAxisPos,0,-180);
          path.lineTo(m_left,m_top+m_xAxisPos/2);
      }
      if (!path.isEmpty())
      {
          gradient_side.setColorAt(1,pieces[i].rgbColor);
          painter->setBrush(gradient_side);
          painter->drawPath(path);
      }
    }
}

void Nightcharts::drawHistogramm(QPainter *painter)
{
    double pDist = 15;
    double pieceWidth = (m_width-(pieces.size())*pDist)/pieces.size();

    QPen pen;
    pen.setWidth(3);

    if(isPercent)
    {
        for (int i=0;i<pieces.size();i++)
        {
            int pieceXPos = pDist+i*(pieceWidth + pDist);
            int h = -m_xAxisPos/100*pieces[i].pPerc;
            h+=12;
            if (shadows)
            {
                painter->setPen(Qt::NoPen);
                painter->setBrush(Qt::darkGray);
                painter->drawRect(m_left+pieceXPos-pDist/2,m_top+m_xAxisPos-1,pieceWidth,h+pDist/2-5);
            }
            QLinearGradient gradient(m_left+m_width/2,h-5,m_left+m_width/2,m_top+m_xAxisPos);
            gradient.setColorAt(0,Qt::black);
            gradient.setColorAt(1,pieces[i].rgbColor);
            painter->setBrush(gradient);

            pen.setColor(pieces[i].rgbColor);
            painter->setPen(pen);
            painter->drawRect(m_left+pieceXPos , m_top+m_xAxisPos-2 , pieceWidth , h);

            QString label = QString::number(pieces[i].cuanty);
            label.append("%");
            painter->setPen(Qt::SolidLine);            
            painter->drawText(m_left+pieceXPos+pieceWidth/2-painter->fontMetrics().width(label)/2,m_top+m_xAxisPos+11-m_xAxisPos/100*pieces[i].pPerc-painter->fontMetrics().height()/2,label);
            painter->drawText(m_left+pieceXPos+pieceWidth/2-painter->fontMetrics().width(pieces.at(i).pname)/2,m_top+m_xAxisPos+12,pieces.at(i).pname);
        }
    }
    else
    {
        for (int i=0;i<pieces.size();i++)
        {
            bool isPositive = pieces[i].cuanty >=0;

            double p = pieces[i].pPerc/100.0;
            double pieceHeigth = m_heigth*p;

            //pieceHeigth-=12;

            int pieceXPos = pDist+i*(pieceWidth + pDist);

            if (shadows)
            {
                painter->setPen(Qt::NoPen);
                painter->setBrush(Qt::darkGray);

                if(isPositive)
                    painter->drawRect(m_left+pieceXPos-pDist/2,m_top+m_xAxisPos-1,pieceWidth,(pieceHeigth>0)?-pieceHeigth+pDist/2-5:1);
                else
                    painter->drawRect(m_left+pieceXPos-pDist/2,m_top+m_xAxisPos+1,pieceWidth,(pieceHeigth-pDist/2>0)?pieceHeigth-pDist/2:1);
            }

            if(pieces.at(i).cuanty >=0)
            {
                QLinearGradient gradient(m_left+m_width/2,m_top+m_xAxisPos-pieceHeigth-80,m_left+m_width/2,m_top+m_xAxisPos);
                gradient.setColorAt(0,Qt::black);
                gradient.setColorAt(1,pieces[i].rgbColor);
                painter->setBrush(gradient);
            }
            else
            {
                QLinearGradient gradientNeg(m_left+m_width/2,m_top+m_xAxisPos,m_left+m_width/2,m_top+m_xAxisPos+pieceHeigth+80);
                gradientNeg.setColorAt(1,Qt::black);
                gradientNeg.setColorAt(0,pieces[i].rgbColor);
                painter->setBrush(gradientNeg);
            }

            pen.setColor(pieces[i].rgbColor);
            painter->setPen(pen);

            if(isPositive)
                painter->drawRect(m_left+pieceXPos , m_top+m_xAxisPos-2 , pieceWidth , (pieceHeigth>0)?-pieceHeigth:1);
            else
                painter->drawRect(m_left+pieceXPos , m_top+m_xAxisPos+2 , pieceWidth , (pieceHeigth>0)?pieceHeigth:-1);

            QString label = QString::number(pieces[i].cuanty);

            painter->setPen(Qt::SolidLine);
            int fontHeigth = painter->fontMetrics().height();
            if(labels)
            {
                if(isPositive)
                    painter->drawText(m_left+pieceXPos+pieceWidth/2-painter->fontMetrics().width(pieces.at(i).pname)/2,m_top+m_xAxisPos+fontHeigth,pieces.at(i).pname);
                else
                    painter->drawText(m_left+pieceXPos+pieceWidth/2-painter->fontMetrics().width(pieces.at(i).pname)/2,m_top+m_xAxisPos-fontHeigth/2,pieces.at(i).pname);
            }
            if(values)
            {
                if(isPositive)
                    painter->drawText(m_left+pieceXPos+pieceWidth/2-painter->fontMetrics().width(label)/2,
                                      (pieceHeigth>0) ? m_top+m_xAxisPos-pieceHeigth-fontHeigth/2 : m_top+m_xAxisPos-fontHeigth/2,
                                      label);
                else
                    painter->drawText(m_left+pieceXPos+pieceWidth/2-painter->fontMetrics().width(label)/2,
                                      (pieceHeigth>0) ? m_top+m_xAxisPos+pieceHeigth+fontHeigth : m_top+m_xAxisPos+fontHeigth,
                                      label);
            }
        }
    }

    //Axis
    painter->setPen(Qt::SolidLine);

    painter->drawLine(m_left,m_top+m_heigth+25,m_left,m_top-15);

    if(m_mayor >0 )
    {
        painter->drawLine(m_left,m_top-15,m_left+4,m_top-5);
        painter->drawLine(m_left,m_top-15,m_left-4,m_top-5);
    }
    if(m_menor < 0)
    {
        painter->drawLine(m_left,m_top+m_heigth+25,m_left+4,m_top+m_heigth+15);
        painter->drawLine(m_left,m_top+m_heigth+25,m_left-4,m_top+m_heigth+15);
    }
    painter->drawLine(m_left,m_top+m_xAxisPos,m_left+m_width,m_top+m_xAxisPos);
    //End Axis
}

void Nightcharts::drawDoubleBar(QPainter *painter)
{
    double pDist = 15;
    double iDist = 3;
    double pieceWidth = (m_width-(pieces.size())*pDist)/pieces.size();

    QPen pen;
    pen.setWidth(3);

    for (int i=0;i<pieces.size();i++)
    {
        double subWidth = pieceWidth/pieces.at(i).values.size() - ((pieces.at(i).values.size()-1)*iDist);

        for(int a=pieces.at(i).values.size()-1;a>-1;a--)
        {
            bool isPositive = pieces.at(i).values.at(a).first >=0;

            double p = pieces.at(i).values.at(a).second/100.0;
            double pieceHeigth = (m_heigth-15)*p;

            int pieceXPos = pDist+i*(pieceWidth + pDist) + a*(iDist + subWidth);

            int blockXPos = pDist+i*(pieceWidth + pDist);

            if (shadows)
            {
                painter->setPen(Qt::NoPen);
                painter->setBrush(Qt::darkGray);

                if(isPositive)
                    painter->drawRect(m_left+pieceXPos-pDist/2,m_top+m_xAxisPos-1,subWidth,(pieceHeigth>0)?-pieceHeigth+pDist/2-5:1);
                else
                    painter->drawRect(m_left+pieceXPos-pDist/2,m_top+m_xAxisPos+1,subWidth,(pieceHeigth-pDist/2>0)?pieceHeigth-pDist/2:1);
            }

            if(isPositive)
            {
                QLinearGradient gradient(m_left+m_width/2,m_top+m_xAxisPos-pieceHeigth-80,m_left+m_width/2,m_top+m_xAxisPos);
                gradient.setColorAt(0,Qt::black);
                gradient.setColorAt(1,DoubleBarColors.at(a).second);
                painter->setBrush(gradient);
            }
            else
            {
                QLinearGradient gradientNeg(m_left+m_width/2,m_top+m_xAxisPos,m_left+m_width/2,m_top+m_xAxisPos+pieceHeigth+80);
                gradientNeg.setColorAt(1,Qt::black);
                gradientNeg.setColorAt(0,DoubleBarColors.at(a).second);
                painter->setBrush(gradientNeg);
            }

            pen.setColor(DoubleBarColors.at(a).second);
            painter->setPen(pen);

            if(isPositive)
                painter->drawRect(m_left+pieceXPos , m_top+m_xAxisPos-2 , subWidth , (pieceHeigth>0)?-pieceHeigth:1);
            else
                painter->drawRect(m_left+pieceXPos , m_top+m_xAxisPos+2 , subWidth , (pieceHeigth>0)?pieceHeigth:-1);

            QString label = QString::number(pieces.at(i).values.at(a).first);

            painter->setPen(Qt::SolidLine);
            int fontHeigth = painter->fontMetrics().height();

            if(values)
            {
                if(isPositive)
                    painter->drawText(m_left+pieceXPos+subWidth/2-painter->fontMetrics().width(label)/2,
                                      (pieceHeigth>0) ? m_top+m_xAxisPos-pieceHeigth-fontHeigth/2 : m_top+m_xAxisPos-fontHeigth/2,
                                      label);
                else
                    painter->drawText(m_left+pieceXPos+subWidth/2-painter->fontMetrics().width(label)/2,
                                      (pieceHeigth>0) ? m_top+m_xAxisPos+pieceHeigth+fontHeigth : m_top+m_xAxisPos+fontHeigth,
                                      label);
            }
            if(labels)
            {
                if(m_mayor<=0)
                    painter->drawText(m_left+blockXPos+pieceWidth/2-painter->fontMetrics().width(pieces.at(i).pname)/2,m_top+fontHeigth,pieces.at(i).pname);
                else
                    painter->drawText(m_left+blockXPos+pieceWidth/2-painter->fontMetrics().width(pieces.at(i).pname)/2,m_top+m_heigth+30+fontHeigth,pieces.at(i).pname);
            }
        }
    }
    //Axis
    painter->setPen(Qt::SolidLine);

    painter->drawLine(m_left,m_top+m_heigth+25,m_left,m_top-15);

    if(m_mayor >0 )
    {
        painter->drawLine(m_left,m_top-15,m_left+4,m_top-5);
        painter->drawLine(m_left,m_top-15,m_left-4,m_top-5);
    }
    if(m_menor < 0)
    {
        painter->drawLine(m_left,m_top+m_heigth+25,m_left+4,m_top+m_heigth+15);
        painter->drawLine(m_left,m_top+m_heigth+25,m_left-4,m_top+m_heigth+15);
    }
    painter->drawLine(m_left,m_top+m_xAxisPos,m_left+m_width,m_top+m_xAxisPos);
    //End Axis
}

void Nightcharts::draw(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::NoPen);
    painter->setFont(chart_font);

    switch (this->ctype) {
    case Pie:
        drawPie(painter);
        break;
    case Dpie:
        drawDPie(painter);
        break;
    case Histogramm:
        drawHistogramm(painter);
        break;
    case DoubleBar:
        drawDoubleBar(painter);
        break;
    default:
        break;
    }
}

void Nightcharts::drawLegend(QPainter *painter)
{
    //double ptext = 25;
    if(this->ctype == DoubleBar)
    {
        int dist = 5;
        painter->setBrush(Qt::white);
        for (int i=DoubleBarColors.size()-1;i>=0;i--)
        {
            painter->setBrush(DoubleBarColors.at(i).second);
            float x = legend_X+dist;
            float y = legend_Y+dist+i*(painter->fontMetrics().height()+2*dist);
            painter->drawRect(x,y,painter->fontMetrics().height(),painter->fontMetrics().height());
            QString s = DoubleBarColors.at(i).first;
            painter->drawText(x+painter->fontMetrics().height()+dist,y+painter->fontMetrics().height()/2+dist,s);
        }
    }
    else
    {
        double angle = palpha;
        painter->setPen(Qt::SolidLine);

        painter->setFont(this->font);
        switch(cltype)
        {
        case Nightcharts::Vertical:
        {
            int dist = 5;
            painter->setBrush(Qt::white);
            //painter->drawRoundRect(cX+cW+20,cY,dist*2+200,pieces.size()*(painter->fontMetrics().height()+2*dist)+dist,15,15);
            for (int i=pieces.size()-1;i>=0;i--)
            {
                painter->setBrush(pieces[i].rgbColor);
                float x = legend_X+dist;
                float y = legend_Y+dist+i*(painter->fontMetrics().height()+2*dist);
                painter->drawRect(x,y,painter->fontMetrics().height(),painter->fontMetrics().height());
                QString s = pieces[i].pname + " - " + QString::number(pieces[i].cuanty);
                if(isPercent)
                    s.append("%");
                painter->drawText(x+painter->fontMetrics().height()+dist,y+painter->fontMetrics().height()/2+dist,s);
            }
            break;
        }
        case Nightcharts::Round:
            for (int i=pieces.size()-1;i>=0;i--)
            {
                float len = 100;
                double pdegree = 3.6*pieces[i].pPerc;
                angle -= pdegree/2;
                QPointF p = GetPoint(angle);
                QPointF p_ = GetPoint(angle, m_width+len,m_xAxisPos+len);
                int q = GetQuater(angle);
                if (q == 3 || q == 4)
                {
                    p.setY(p.y()+pW/2);
                    p_.setY(p_.y()+pW/2);
                }
                painter->drawLine(p.x(),p.y(),p_.x(),p_.y());
                QString label = pieces[i].pname + " - " + QString::number(pieces[i].cuanty);
                if(isPercent)
                    label.append("%");
                float recW = painter->fontMetrics().width(label)+10;
                float recH = painter->fontMetrics().height()+10;
                p_.setX(p_.x()-recW/2 + recW/2*cos(angle*M_PI/180));
                p_.setY(p_.y()+recH/2 + recH/2*sin(angle*M_PI/180));
                painter->setBrush(Qt::white);
                painter->drawRoundRect(p_.x() ,p_.y(), recW, -recH);
                painter->drawText(p_.x()+5, p_.y()-recH/2+5, label);
                angle -= pdegree/2;
            }
            break;
        }
    }
}

QPointF Nightcharts::GetPoint(double angle, double R1, double R2)
{
    if (R1 == 0 && R2 == 0)
    {
        R1 = m_width;
        R2 = m_xAxisPos;
    }
    QPointF point;
    double x = R1/2*cos(angle*M_PI/180);
    x+=m_width/2+m_left;
    double y = -R2/2*sin(angle*M_PI/180);
    y+=m_xAxisPos/2+m_top;
    point.setX(x);
    point.setY(y);
    return point;
}

int Nightcharts::GetQuater(double angle)
{
    angle = Angle360(angle);

    if(angle>=0 && angle<90)
        return 1;
    if(angle>=90 && angle<180)
        return 2;
    if(angle>=180 && angle<270)
        return 3;
    if(angle>=270 && angle<360)
        return 4;
}

double Nightcharts::Angle360(double angle)
{
    int i = (int)angle;
    double delta = angle - i;
    return (i%360 + delta);
}

pieceNC::pieceNC()
{
    maxValue = 0;
    minValue = 0;
}
void pieceNC::addName(QString name)
{
    pname = name;
}
void pieceNC::setColor(Qt::GlobalColor color)
{
    rgbColor = color;
}
void pieceNC::setColor(QColor color)
{
    rgbColor = color;
}


void pieceNC::setPerc(float Percentage)
{
    pPerc = Percentage;
}
