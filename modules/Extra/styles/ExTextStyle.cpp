#include "styles/ExTextStyle.h"

ExTextStyle::ExTextStyle(QObject *parent) : QObject{parent} {
    m_family = QFont().defaultFamily();
#ifdef Q_OS_WIN
    m_family = "Source Han Sans CN Medium";
#endif

    QFont caption;
    caption.setFamily(m_family);
    caption.setPixelSize(12);
    Caption(caption);

    QFont body;
    body.setFamily(m_family);
    body.setPixelSize(13);
    Body(body);

    QFont bodyStrong;
    bodyStrong.setFamily(m_family);
    bodyStrong.setPixelSize(13);
    bodyStrong.setWeight(QFont::DemiBold);
    BodyStrong(bodyStrong);

    QFont subtitle;
    subtitle.setFamily(m_family);
    subtitle.setPixelSize(20);
    subtitle.setWeight(QFont::DemiBold);
    Subtitle(subtitle);

    QFont title;
    title.setFamily(m_family);
    title.setPixelSize(28);
    title.setWeight(QFont::DemiBold);
    Title(title);

    QFont titleLarge;
    titleLarge.setFamily(m_family);
    titleLarge.setPixelSize(40);
    titleLarge.setWeight(QFont::DemiBold);
    TitleLarge(titleLarge);

    QFont display;
    display.setFamily(m_family);
    display.setPixelSize(68);
    display.setWeight(QFont::DemiBold);
    Display(display);

    QFont button;
    button.setFamily(m_family);
    button.setPixelSize(20);
    Button(button);

    QFont buttonStrong;
    buttonStrong.setFamily(m_family);
    buttonStrong.setPixelSize(20);
    buttonStrong.setWeight(QFont::DemiBold);
    ButtonStrong(buttonStrong);

}
