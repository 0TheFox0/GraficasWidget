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
    Q_PROPERTY(bool Sombra READ Sombra WRITE verSombra)
    Q_PROPERTY(bool Etiquetas READ Etiquetas WRITE verEtiquetas)
    Q_PROPERTY(bool Valores READ Valores WRITE verValores)
    Q_PROPERTY(bool ValoresEjeY READ ValoresEjeY WRITE verValoresEjeY)
    Q_PROPERTY(bool Leyenda READ LeyendaEnabled WRITE EnableLeyenda)
    Q_PROPERTY(Tipo_leyenda TipoLeyenda READ TipoLeyenda WRITE setTipoleyenda)
    Q_PROPERTY(QFont LetraLeyenda READ LetraLeyenda WRITE setLetraLeyenda)

public:
    Grafica(QWidget *parent = 0);
    QSize minimumSizeHint() const;


    Q_ENUMS(Tipos)
    enum Tipos {Barras , DobleBarra , Sectores_2D, Sectores_3D , Lineas};
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
    void verSombra(bool b){m_sombra = b;
                           this->repaint();}

    bool Etiquetas(){return m_labels;}
    void verEtiquetas(bool b){m_labels = b;
                              this->repaint();}

    bool Valores(){return m_values;}
    void verValores(bool b){m_values = b;
                            this->repaint();}

    bool ValoresEjeY(){return m_valuesEnY;}
    void verValoresEjeY(bool b){m_valuesEnY = b;
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

    void addItem(QString name, QColor color , QVector<float> value);
    void addItem(QString name, Qt::GlobalColor color , QVector<float> value);
    void addItem(QString name, QVector<float> value);
    void addColorMultibarras(QString nombre, QColor  color);

    void addLinea(QString nombre, QVector<float> points , QColor color);
    void addLinea(QString nombre, QVector<float> points);
    void addLineaStop(QString s){m_lineStops.append(s);}
    void addLineaStops(QStringList ls){m_lineStops.append(ls);}

    void removeItem(QString name);
    void clear(){m_items.clear(); m_lines.clear(); m_lineStops.clear();this->repaint();}
protected:
    void paintEvent(QPaintEvent *);
    void setupBarras(Nightcharts * chart);
    void setupDobleBarras(Nightcharts * chart);
    void setup2DPie(Nightcharts * chart);
    void setup3DPie(Nightcharts * chart);
    void setupLineas(Nightcharts * chart);
private:
    Tipos m_type;
    bool m_perc;

    bool m_useLeyenda;
    Tipo_leyenda m_tipoLeyenda;

    bool m_sombra;
    bool m_labels;
    bool m_values;
    bool m_valuesEnY;

    QFont m_letraLeyenda;
    QFont m_letra;

    QList<pieceNC> m_items;
    QVector<QPair<QString , QColor> >m_DoubleBarColors;

    QVector< lineNC >m_lines;
    QStringList m_lineStops;
};

#endif
