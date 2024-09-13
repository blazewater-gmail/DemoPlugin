#include "ExButtonColor.h"
#include <plog/Log.h>

QColor ColorPair::background() const
{
    return m_background;
}

QColor ColorPair::text() const
{
    return m_text;
}

void ColorPair::setBackground(const QColor &background)
{
    if (m_background != background) {
        m_background = background;
        emit backgroundChanged();
    }
}

void ColorPair::setText(const QColor &text)
{
    if (m_text != text) {
        m_text = text;
        emit textChanged();
    }
}

bool ColorPair::operatorEqualsImpl(const ColorPair &lhs, const ColorPair &rhs)
{
    return lhs.m_text == rhs.m_text && lhs.m_background == rhs.m_background;
}

ExButtonColor::ExButtonColor(QObject *parent) 
    : QObject(parent),
      m_normal(new ColorPair(this)),
      m_hovered(new ColorPair(this)),
      m_clicked(new ColorPair(this)),
      m_checked(new ColorPair(this)),
      m_disabled(new ColorPair(this))
{
    PLOGV << "ExButtonColor::ExButtonColor(QObject *parent)";
    m_normal->setBackground(ExColors::getInstance()->Background()); // white;
    m_normal->setText(ExColors::getInstance()->Primary()); // black;
    m_hovered->setBackground(QColor(91, 91, 87)); // grey
    m_hovered->setText(ExColors::getInstance()->Secondary()); // white;
    m_clicked->setBackground(QColor(0, 66, 115)); // blue
    m_clicked->setText(ExColors::getInstance()->Secondary()); // white;
    m_checked->setBackground(QColor(0, 66, 115)); // blue
    m_checked->setText(ExColors::getInstance()->Secondary()); // white;
    m_disabled->setBackground(QColor(0x30, 0x3D, 0x4B)); // grey
    m_disabled->setText(ExColors::getInstance()->SmokeWhite()); // smoke white;
}

ExButtonColor::~ExButtonColor()
{
    PLOGV << "ExButtonColor::~ExButtonColor()";
}

ColorPair* ExButtonColor::normal() const {
    return m_normal;
}

void ExButtonColor::setNormal(ColorPair *normalColors) {
    if (!m_normal) {
        return;
    }
    if (*m_normal != *normalColors) {
        m_normal = normalColors;
        emit normalChanged();
    }
}

ColorPair* ExButtonColor::hovered() const {
    return m_hovered;
}

void ExButtonColor::setHovered(ColorPair *hoveredColors) {
    if (!m_hovered) {
        return;
    }
    if (*m_hovered != *hoveredColors) {
        m_hovered = hoveredColors;
        emit hoveredChanged();
    }
}

ColorPair* ExButtonColor::clicked() const {
    return m_clicked;
}

void ExButtonColor::setClicked(ColorPair *clickedColors) {
    if (!m_clicked) {
        return;
    }
    if (*m_clicked != *clickedColors) {
        m_clicked = clickedColors;
        emit clickedChanged();
    }
}

ColorPair* ExButtonColor::checked() const {
    return m_checked;
}

void ExButtonColor::setChecked(ColorPair *checkedColors) {
    if (!m_checked) {
        return;
    }
    if (*m_checked != *checkedColors) {
        m_checked = checkedColors; 
        emit checkedChanged();
    }
}

ColorPair* ExButtonColor::disabled() const {
    return m_disabled;
}

void ExButtonColor::setDisabled(ColorPair *disabledColors) {
    if (!m_disabled) {
        return;
    }
    if (*m_disabled != *disabledColors) {
        m_disabled = disabledColors;
        emit disabledChanged();
    }
}