#include "ExColors.h"
#include <plog/Log.h>

ExColors::ExColors(QObject *parent)
        : QObject{parent}
{
    m_Transparent = QColor(0, 0, 0, 0);
    m_Black = QColor(0, 0, 0);
    m_White = QColor(255, 255, 255);
    m_Grey10 = QColor(250, 249, 248);
    m_Grey20 = QColor(243, 242, 241);
    m_Grey30 = QColor(237, 235, 233);
    m_Grey40 = QColor(225, 223, 221);
    m_Grey50 = QColor(210, 208, 206);
    m_Grey60 = QColor(200, 198, 196);
    m_Grey70 = QColor(190, 185, 184);
    m_Grey80 = QColor(179, 176, 173);
    m_Grey90 = QColor(161, 159, 157);
    m_Grey100 = QColor(151, 149, 146);
    m_Grey110 = QColor(138, 136, 134);
    m_Grey120 = QColor(121, 119, 117);
    m_Grey130 = QColor(96, 94, 92);
    m_Grey140 = QColor(72, 70, 68);
    m_Grey150 = QColor(59, 58, 57);
    m_Grey160 = QColor(50, 49, 48);
    m_Grey170 = QColor(41, 40, 39);
    m_Grey180 = QColor(37, 36, 35);
    m_Grey190 = QColor(32, 31, 30);
    m_Grey200 = QColor(27, 26, 25);
    m_Grey210 = QColor(22, 21, 20);
    m_Grey220 = QColor(17, 16, 15);

    m_SmokeWhite = QColor(245, 245, 245);

    m_Primary = QColor(51, 51, 51);
    m_Secondary = QColor(255, 255, 255);
    m_Background = QColor(255, 255, 255);
    m_Surface = QColor(100, 100, 100);
    m_Error = QColor(255, 0, 0);
}

// Function to generate a darker divider color based on the background color
QColor ExColors::dividerColor(const QColor &background, qreal alpha, qreal beta)
{
    // Ensure alpha and beta are within [0, 1] range
    alpha = qBound(0.0, alpha, 1.0);
    beta = qBound(0.0, beta, 1.0);
    
    // Extract the RGBA components of the background color
    int r_bg = background.red();
    int g_bg = background.green();
    int b_bg = background.blue();
    int a_bg = background.alpha();

    // Calculate the RGBA components of the divider color
    int r_div = static_cast<int>(r_bg * (1 - alpha));
    int g_div = static_cast<int>(g_bg * (1 - alpha));
    int b_div = static_cast<int>(b_bg * (1 - alpha));
    int a_div = static_cast<int>(a_bg * beta);

    // Create and return the divider color
    return QColor(r_div, g_div, b_div, a_div);
}
// 获取用Gradient表示的Divider的两头的颜色;
QList<QColor> ExColors::dividerColors(const QColor &background, qreal alpha)
{
    // Ensure alpha is within [0, 1] range
    alpha = qBound(0.0, alpha, 1.0);

    // Extract the RGBA components of the background color
    int r_bg = background.red();
    int g_bg = background.green();
    int b_bg = background.blue();
    int a_bg = background.alpha();

    // Generate the top color (slightly lighter)
    auto topColor = QColor(
        qBound(0, r_bg + static_cast<int>((255 - r_bg) * alpha), 255),
        qBound(0, g_bg + static_cast<int>((255 - g_bg) * alpha), 255),
        qBound(0, b_bg + static_cast<int>((255 - b_bg) * alpha), 255),
        a_bg
    );

    // Generate the bottom color (slightly darker)
    auto bottomColor = QColor(
        qBound(0, r_bg - static_cast<int>(r_bg * alpha), 255),
        qBound(0, g_bg - static_cast<int>(g_bg * alpha), 255),
        qBound(0, b_bg - static_cast<int>(b_bg * alpha), 255),
        a_bg
    );

    // Create and return the divider color
    QList<QColor> l;
    l.append(topColor);
    l.append(bottomColor);
    return l;
}