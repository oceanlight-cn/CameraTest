import QtQuick 2.0

import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

import com.wiseelement.qmlcomponents 1.0
import QtQuick.Window 2.2

Window {
    visible: true
    id: root
    property int row_spacing: 10
    width: 300
    height: 600

    Rectangle{
            id: layer1
            width: parent.width
            height: Math.floor(parent.height/3)
            border.color: "black"
            border.width: 1

            Text {
                x: 5
                text: qsTr("operation plane:")
            }

            GridLayout
            {
                columns: 2

                x: 10
                y: 20

                Label {
                    id: lblStartTime
                    text: qsTr("test start time:")
                }

                TextField{
                    id:txtStartTime
                    width: 50
                }

                Label {
                    text: qsTr("test duration:")
                }

                TextField{
                    id:txtDuration

                }

                Label {
                    text: qsTr("decode fail times:")
                }

                Text{
                    id:txtFailTimes
                    text: qsTr("")
                }

                Label {
                    id: lblCenterPos
                    text: qsTr("Decode Center Pos:")
                }

                TextField{
                    id:txtCenterPos

                }

                Button {
                    style: ButtonStyle
                    {
                        background: Rectangle {
                                    implicitWidth: 100
                                    implicitHeight: 30
                                    color: "lightgrey"
                                    radius: 2
                                }
                     }

                    Text {
                        id: btnStart
                        text: qsTr("start")
                        anchors.centerIn: parent
                    }
                }

                Button {
                    style: ButtonStyle
                    {
                        background: Rectangle {
                                    implicitWidth: 100
                                    implicitHeight: 30
                                    color: "lightgrey"
                                    radius: 2
                                }
                     }

                    Text {
                        id: btnStop
                        text: qsTr("stop")
                        anchors.centerIn: parent
                    }
                }
            }

        }

        Rectangle{
            id: layerDataSource
            width: parent.width
            height: Math.floor(parent.height/6)
            anchors.topMargin: 10
            anchors.top: layer1.bottom
            border.color: "black"
            border.width: 1

            Text {
                x: 5
                text: qsTr("datasource:")
            }

            Column
            {
                spacing: 10

                x: 10
                y: 20

                CheckBox {
                    text: qsTr("Ethernet")
                }

                CheckBox {
                    text: qsTr("SerialPort")
                }

            }

        }
        Rectangle{
            id: layerNetwork
            width: parent.width
            height: Math.floor(parent.height/6)
            anchors.topMargin: 10
            anchors.top: layerDataSource.bottom
            border.color: "black"
            border.width: 1

            Text {
                x: 5
                text: qsTr("network setting:")
            }

            GridLayout
            {
                columns: 2

                x: 10
                y: 20

                Label {
                    id: lblIp
                    text: qsTr("ip:")
                }

                TextField{
                    id:txtIp

                }

                Label {
                    id: lblPort
                    text: qsTr("port:")
                 }

                TextField{
                    id:txtPort

                }
            }

        }

        Rectangle{
            id: layerSerialPort
            width: parent.width
            height: Math.floor(parent.height/3)
            anchors.topMargin: 10
            anchors.top: layerNetwork.bottom
            border.color: "black"
            border.width: 1

            Text {
                x: 5
                text: qsTr("serialport setting:")
            }

            GridLayout
            {
                columns: 2

                x: 10
                y: 20

                Label {
                    id: lblComPort
                    text: "ComPort;"
                }

                ComboBox {
                    id: cboComs
                    width: 100
                    model: ListModel {
                        id: cbItems
                    }
                }

                Label {
                    id: lblBaudRate
                    text: qsTr("BaudRate:")
                 }

                ComboBox {
                    id: cboBaudRate
                    width: 100
                    model: [ "1200" , "2400" , "4800" , "9600" , "19200" , "38400" , "57600" , "115200" ]
                }

                Label {
                    id: lblParity
                    text: qsTr("Parity:")
                 }

                ComboBox {
                    id: cboParity
                    width: 100
                    model: ["NONE" , "ODD" , "EVEN" , "MARK" , "SPACE"]
                }

                Label {
                    id: lblDatabits
                    text: qsTr("Databits:")
                 }

                ComboBox {
                    id: cboDatabits
                    width: 100
                    model: ["5" , "6" , "7" , "8"]
                }

                Label {
                    id: lblStopbits
                    text: qsTr("Stopbits:")
                 }

                ComboBox {
                    id: cboStopbits
                    width: 100
                    model: ["1" , "1.5" , "2"]
                }
            }

        }

    SerialPort{
        id:serialport
    }

    Component.onCompleted: {
        serialport.loadcoms();
    }

    Connections{
        target:serialport
        onComChanged:
        {
            var portComs = serialport.getcoms();
            for(var i= 0; i < portComs.length; i++)
            {
                cbItems.append({'text':portComs[i]});
            }
        }
    }
}

