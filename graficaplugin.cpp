#include "grafica.h"
#include "graficaplugin.h"

#include <QtPlugin>

GraficaPlugin::GraficaPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void GraficaPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;
    
    // Add extension registrations, etc. here
    
    m_initialized = true;
}

bool GraficaPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GraficaPlugin::createWidget(QWidget *parent)
{
    return new Grafica(parent);
}

QString GraficaPlugin::name() const
{
    return QLatin1String("Grafica");
}

QString GraficaPlugin::group() const
{
    return QLatin1String("");
}

QIcon GraficaPlugin::icon() const
{
    return QIcon();
}

QString GraficaPlugin::toolTip() const
{
    return QLatin1String("");
}

QString GraficaPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool GraficaPlugin::isContainer() const
{
    return false;
}

QString GraficaPlugin::domXml() const
{
    return QLatin1String("<widget class=\"Grafica\" name=\"grafica\">\n</widget>\n");
}

QString GraficaPlugin::includeFile() const
{
    return QLatin1String("grafica.h");
}

Q_EXPORT_PLUGIN2(graficaplugin, GraficaPlugin)
