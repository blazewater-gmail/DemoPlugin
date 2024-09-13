#pragma once

#include <QObject>
#include <QtQml/qqml.h>
#include <QColor>
#include <ExColors.h>
#include "stdafx.h"

/**
 * @brief The Color Pair class
 */

class ColorPair : public QObject {
    Q_OBJECT

    Q_PROPERTY(QColor background READ background WRITE setBackground NOTIFY backgroundChanged FINAL)
    Q_PROPERTY(QColor text READ text WRITE setText NOTIFY textChanged FINAL)
    QML_ANONYMOUS

public:
    using QObject::QObject;

    QColor background() const;
    void setBackground(const QColor &background);

    QColor text() const;
    void setText(const QColor &text);

    friend bool operator==(const ColorPair &lhs, const ColorPair &rhs)
    {
        return operatorEqualsImpl(lhs, rhs);
    }
    friend bool operator!=(const ColorPair &lhs, const ColorPair &rhs)
    {
        return !operatorEqualsImpl(lhs, rhs);
    }

signals:
    void backgroundChanged();
    void textChanged();
private: 
    static bool operatorEqualsImpl(const ColorPair &, const ColorPair &);
    QColor m_background = ExColors::getInstance()->Background();
    QColor m_text = ExColors::getInstance()->Primary();

};

/**
 * @brief The Segmented Control Button Colors class
 *        Example Usage in QML
 *
    colors: ExButtonColor {
        normal.background: "green"
        normal.text: "white"
    }
    colors: ExButtonColor {
        normal {
            background: "green"
            text: "white"
        }
        hovered {
            background: "white"
            text: "black"
        }
        clicked {
            background: "darkgreen"
            text: "white"
        }        
        checked {
            background: "blue"
            text: "white"
        }
        disabled {
            background: "gray"
            text: "gray"
        }
    }
 */

class ExButtonColor : public QObject {
    Q_OBJECT

    Q_PROPERTY(ColorPair *normal READ normal WRITE setNormal NOTIFY normalChanged FINAL)
    Q_PROPERTY(ColorPair *hovered READ hovered WRITE setHovered NOTIFY hoveredChanged FINAL)
    Q_PROPERTY(ColorPair *clicked READ clicked  WRITE setClicked NOTIFY clickedChanged FINAL)
    Q_PROPERTY(ColorPair *checked READ checked  WRITE setChecked NOTIFY checkedChanged FINAL)
    Q_PROPERTY(ColorPair *disabled READ disabled  WRITE setDisabled NOTIFY disabledChanged FINAL)
    QML_NAMED_ELEMENT(ExButtonColor)

public:
    using QObject::QObject;

    ExButtonColor(QObject *parent = nullptr);
    ~ExButtonColor() override;

    ColorPair * normal() const;
    void setNormal(ColorPair *normalColors);
    ColorPair * hovered() const;
    void setHovered(ColorPair *hoveredColors);
    ColorPair * clicked() const;
    void setClicked(ColorPair *clickedColors);
    ColorPair * checked() const;
    void setChecked(ColorPair *checkedColors);
    ColorPair * disabled() const;
    void setDisabled(ColorPair *disabledColors);

signals:
    void normalChanged();
    void hoveredChanged();
    void clickedChanged();
    void checkedChanged();
    void disabledChanged();

private: 
    ColorPair * m_normal{nullptr}, * m_hovered{nullptr}, * m_clicked{nullptr}, * m_checked{nullptr}, * m_disabled{nullptr};
};