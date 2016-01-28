import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4

Item
{
    id: theParent
    signal textChanged(variant textArea)
    property variant textArea: textArea

    Component
    {
        id: textArea
        TextArea
        {
            id: tArea

            onTextChanged: theParent.textChanged(tArea);
        }
    }

    MessageDialog
    {
        id: saveDialogQuestion
        objectName: "saveDialogQuestion"
        title: "Close file"
        text: "Save contents before closing?"
        standardButtons: StandardButton.Yes | StandardButton.No | StandardButton.Cancel
        modality: Qt.ApplicationModal
    }
}
