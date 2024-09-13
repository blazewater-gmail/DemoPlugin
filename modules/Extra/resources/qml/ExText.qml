import QtQuick
import QtQuick.Controls
import Extra

Text {
    id:control
    property color textColor: ExColors.Primary
    color: textColor
    // renderType: FluTheme.nativeText ? Text.NativeRendering : Text.QtRendering
    font: ExTextStyle.Body
    verticalAlignment: Text.AlignVCenter
}