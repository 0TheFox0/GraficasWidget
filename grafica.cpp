#include "grafica.h"
#include <QTime>
Grafica::Grafica(QWidget *parent) :
    QWidget(parent)
{    
    m_useLeyenda = false;
    m_sombra = false;
    m_tipoLeyenda = Vertical;
    m_type = Barras;
    this->repaint();
    qsrand(QTime::currentTime().msec());
}

QSize Grafica::minimumSizeHint() const
{
    return QSize(200,100);
}

void Grafica::addItem(QString name, QColor color, float value)
{
    pieceNC p;
    p.pname = name;
    p.setColor(color);
    p.setCuanty(value);

    m_items.append(p);
    this->repaint();
}

void Grafica::addItem(QString name, Qt::GlobalColor color, float value)
{
    pieceNC p;
    p.pname = name;
    p.setColor(color);
    p.setCuanty(value);

    m_items.append(p);
    this->repaint();
}

void Grafica::addItem(QString name, float value)
{
    pieceNC p;
    p.pname = name;

    int r = qrand()%255;
    int g = qrand()%255;
    int b = qrand()%255;
    p.setColor(QColor(r,g,b));
    p.setCuanty(value);

    m_items.append(p);
    this->repaint();
}

void Grafica::removeItem(QString name)
{
    for (int i =0; i<m_items.size(); i++)
    {
        if(m_items.at(i).pname == name)
        {
            m_items.removeAt(i);
            break;
        }
    }
    this->repaint();
}

void Grafica::paintEvent(QPaintEvent * e)
{
    QWidget::paintEvent(e);
    QPainter painter;

    painter.begin(this);
    Nightcharts Chart;

    Chart.setIsPercent(m_perc);
    Chart.setShadows(m_sombra);
    Chart.setLegendFont(m_letraLeyenda);
    Chart.setChartFont(m_letra);

    switch (m_type) {
    case Barras:
        setupBarras(&Chart);
        break;
    case Sectores_2D:
        setup2DPie(&Chart);
        break;
    default://Sectores_3D
        setup3DPie(&Chart);
        break;
    }


    for (int i=0;i<m_items.size();i++)
    {
        Chart.addPiece(m_items.at(i));
    }

    Chart.addPiece("Item1",QColor(200,10,50),34);
    Chart.addPiece("Item2",Qt::green,27);
    Chart.addPiece("Item3",Qt::cyan,14);
    Chart.addPiece("Item4",Qt::yellow,7);
    Chart.addPiece("Item5",Qt::blue,4);

    Chart.draw(&painter);
    if(m_useLeyenda)
    {
        switch (m_tipoLeyenda) {
        case Vertical:
            Chart.setLegendType(Nightcharts::Vertical);
            break;
        default:
            Chart.setLegendType(Nightcharts::Round);
            break;
        }
        Chart.drawLegend(&painter);
    }
}

void Grafica::setupBarras(Nightcharts *chart)
{
    chart->setType(Nightcharts::Histogramm);
    if(!m_useLeyenda)
    {
         chart->setCords(5,5,this->width()-10,this->height()-10);
    }
    else
    {
        m_tipoLeyenda = Vertical;
        chart->setCords(5,5,this->width()/1.5,this->height()-10);
    }
}

void Grafica::setup2DPie(Nightcharts *chart)
{
    chart->setType(Nightcharts::Pie);
    if(!m_useLeyenda)
    {
        chart->setCords(5,5,this->width()-10,this->height()-10);
    }
    else
    {
        if(m_tipoLeyenda == Vertical)
        {
            int w = this->width()-10;
            int h = this->height()-10;
            int use = qMin(w,h);
            chart->setCords(5,5,use,use);
        }
        else
        {
            int use = qMin(this->width(),this->height());
            int start = use /8;
            int size = use * 3/4;
            chart->setCords(start,start,size,size);
        }
    }
}

void Grafica::setup3DPie(Nightcharts *chart)
{
    chart->setType(Nightcharts::Dpie);
    if(!m_useLeyenda)
    {
        chart->setCords(5,5,this->width(),this->height());
    }
    else
    {
        if(m_tipoLeyenda == Vertical)
        {
            int w = this->width()-10;
            int h = this->height()-10;
            int use = qMin(w,h);
            chart->setCords(5,5,use,use);
        }
        else
        {
            int use = qMin(this->width(),this->height());
            int start = use /8;
            int size = use * 3/4;
            chart->setCords(start,start,size,size);
        }
    }
}
