import QtQuick
import QtQuick.Controls
import demo
import Extra

ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 600
    title: qsTr("Demo Plugin")

    ExText {
        width: root.width
        text: qsTr("Demo Plugin")
        color: 'black'
        font: ExTextStyle.Title
        // height: font.pixelSize
        anchors.verticalCenter: parent.verticalCenter // Center vertically
        horizontalAlignment: Text.AlignHCenter // Center horizontally
    }
}
