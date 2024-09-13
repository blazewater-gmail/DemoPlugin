#pragma once

#include <QObject>
#include <QtQml/qqml.h>
#include <QColor>

#include "stdafx.h"
#include "singleton.h"

/**
 * @brief The ExColors class
 */
class ExColors : public QObject {
    Q_OBJECT

public:
    Q_INVOKABLE QColor dividerColor(const QColor& background, qreal alpha = 0.2, qreal beta = 0.8);
    Q_INVOKABLE QList<QColor> dividerColors(const QColor& background, qreal alpha = 0.2);

    Q_PROPERTY_AUTO(QColor, Transparent)
    Q_PROPERTY_AUTO(QColor, Black)
    Q_PROPERTY_AUTO(QColor, White)
    Q_PROPERTY_AUTO(QColor, Grey10)
    Q_PROPERTY_AUTO(QColor, Grey20)
    Q_PROPERTY_AUTO(QColor, Grey30)
    Q_PROPERTY_AUTO(QColor, Grey40)
    Q_PROPERTY_AUTO(QColor, Grey50)
    Q_PROPERTY_AUTO(QColor, Grey60)
    Q_PROPERTY_AUTO(QColor, Grey70)
    Q_PROPERTY_AUTO(QColor, Grey80)
    Q_PROPERTY_AUTO(QColor, Grey90)
    Q_PROPERTY_AUTO(QColor, Grey100)
    Q_PROPERTY_AUTO(QColor, Grey110)
    Q_PROPERTY_AUTO(QColor, Grey120)
    Q_PROPERTY_AUTO(QColor, Grey130)
    Q_PROPERTY_AUTO(QColor, Grey140)
    Q_PROPERTY_AUTO(QColor, Grey150)
    Q_PROPERTY_AUTO(QColor, Grey160)
    Q_PROPERTY_AUTO(QColor, Grey170)
    Q_PROPERTY_AUTO(QColor, Grey180)
    Q_PROPERTY_AUTO(QColor, Grey190)
    Q_PROPERTY_AUTO(QColor, Grey200)
    Q_PROPERTY_AUTO(QColor, Grey210)
    Q_PROPERTY_AUTO(QColor, Grey220)

    Q_PROPERTY_AUTO(QColor, SmokeWhite)

    Q_PROPERTY_AUTO(QColor, Primary)
    Q_PROPERTY_AUTO(QColor, Secondary)
    Q_PROPERTY_AUTO(QColor, Background)
    Q_PROPERTY_AUTO(QColor, Surface)
    Q_PROPERTY_AUTO(QColor, Error)

    QML_NAMED_ELEMENT(ExColors)
    QML_SINGLETON

    private:
    explicit ExColors(QObject *parent = nullptr);

    public:
    SINGLETON(ExColors)

    static ExColors *create(QQmlEngine *, QJSEngine *)
    {
        return getInstance();
    }
};
