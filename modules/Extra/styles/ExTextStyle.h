#pragma once

#include <QObject>
#include <QtQml/qqml.h>
#include <QFont>
#include "stdafx.h"
#include "singleton.h"

/**
 * @brief The ExTextStyle class
 */
class ExTextStyle : public QObject {
    Q_OBJECT

public:
    Q_PROPERTY_AUTO(QString, family) // default font family
    Q_PROPERTY_AUTO(QStringList, families) // available font families
    Q_PROPERTY_AUTO(QFont, Caption)
    Q_PROPERTY_AUTO(QFont, Body)
    Q_PROPERTY_AUTO(QFont, BodyStrong)
    Q_PROPERTY_AUTO(QFont, Subtitle)
    Q_PROPERTY_AUTO(QFont, Title)
    Q_PROPERTY_AUTO(QFont, TitleLarge)
    Q_PROPERTY_AUTO(QFont, Display)
    Q_PROPERTY_AUTO(QFont, Button) // Button Fonts Style
    Q_PROPERTY_AUTO(QFont, ButtonStrong) // Button (Checked) Fonts Style
    QML_NAMED_ELEMENT(ExTextStyle)
    QML_SINGLETON

private:
    explicit ExTextStyle(QObject *parent = nullptr);

public:
    SINGLETON(ExTextStyle)

    static ExTextStyle *create(QQmlEngine *, QJSEngine *) {
        return getInstance();
    }
};
