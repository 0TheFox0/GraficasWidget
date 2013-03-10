#ifndef GRAFICA_H
#define GRAFICA_H

#include <QWidget>
#include <QFont>
#include <QList>
#include "nightcharts.h"
class Grafica : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(Tipos Tipo READ Tipo WRITE setTipo)
    Q_PROPERTY(bool Porcentual READ Porcentual WRITE setPorcentual)
    Q_PROPERTY(QFont Letra READ Letra WRITE setLetra)
    Q_PROPERTY(bool Sombra READ Sombra WRITE setSombra)
    Q_PROPERTY(bool Leyenda READ LeyendaEnabled WRITE EnableLeyenda)
    Q_PROPERTY(Tipo_leyenda TipoLeyenda READ TipoLeyenda WRITE setTipoleyenda)
    Q_PROPERTY(QFont LetraLeyenda READ LetraLeyenda WRITE setLetraLeyenda)
public:
    Grafica(QWidget *parent = 0);
    QSize minimumSizeHint() const;


    Q_ENUMS(Tipos)
    enum Tipos {Barras , Sectores_2D, Sectores_3D };
    Tipos Tipo(){return m_type;}
    void setTipo(Tipos t){m_type = t;
                          this->repaint();}

    bool Porcentual(){return m_perc;}
    void setPorcentual(bool b){m_perc = b;
                              this->repaint();}

    bool LeyendaEnabled(){return m_useLeyenda;}
    void EnableLeyenda(bool b){m_useLeyenda = b;
                               this->repaint();}
    Q_ENUMS(Tipo_leyenda)
    enum Tipo_leyenda {Vertical , Circular};

    Tipo_leyenda TipoLeyenda(){return m_tipoLeyenda;}
    void setTipoleyenda(Tipo_leyenda t){m_tipoLeyenda = t;
                                        this->repaint();}

    bool Sombra(){return m_sombra;}
    void setSombra(bool b){m_sombra = b;
                           this->repaint();}

    QFont LetraLeyenda(){return m_letraLeyenda;}
    void setLetraLeyenda(QFont f){m_letraLeyenda = f;
                                  this->repaint();}

    QFont Letra(){return m_letra;}
    void setLetra(QFont f){m_letra = f;
                           this->repaint();}

    QList<pieceNC> Items(){return m_items;}
    void setItems(QList<pieceNC> m){m_items = m;}

    void addItem(QString name, QColor color , float value);
    void addItem(QString name, Qt::GlobalColor color , float value);
    void addItem(QString name, float value);

    void removeItem(QString name);
protected:
    void paintEvent(QPaintEvent *);
    void setupBarras(Nightcharts * chart);
    void setup2DPie(Nightcharts * chart);
    void setup3DPie(Nightcharts * chart);
private:
    Tipos m_type;
    bool m_perc;

    bool m_useLeyenda;
    Tipo_leyenda m_tipoLeyenda;

    bool m_sombra;

    QFont m_letraLeyenda;
    QFont m_letra;

    QList<pieceNC> m_items;
};

#endif