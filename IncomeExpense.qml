import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    width: 400
    height: 300

    property real amount: 0 // 存款/取款金额
    property string transferTo: "" // 转账目标账户
    property real transferAmount: 0 // 转账金额

    Column {
        anchors.centerIn: parent
        spacing: 10

        Button {
            text: "存款"
            onClicked: {
                amount = 0; // 重置金额
                transferTo = ""; // 重置转账目标
                transferAmount = 0; // 重置转账金额
                // 打开存款对话框
                depositDialog.open()
            }
        }

        Button {
            text: "取款"
            onClicked: {
                amount = 0; // 重置金额
                transferTo = ""; // 重置转账目标
                transferAmount = 0; // 重置转账金额
                // 打开取款对话框
                withdrawDialog.open()
            }
        }

        Button {
            text: "转账"
            onClicked: {
                amount = 0; // 重置金额
                transferTo = ""; // 重置转账目标
                transferAmount = 0; // 重置转账金额
                // 打开转账对话框
                transferDialog.open()
            }
        }
    }

    Dialog {
        id: depositDialog
        title: "存款"
        standardButtons: Dialog.Ok | Dialog.Cancel

        Column {
            spacing: 10

            TextField {
                placeholderText: "金额"
                onTextChanged: amount = parseFloat(text)
            }

            // 金额选项按钮
            Row {
                spacing: 5
                Repeater {
                    model: [100, 500, 1000, 10000, -1] // -1 表示自定义金额
                    Button {
                        text: modelData === -1 ? "自定义金额" : modelData
                        onClicked: {
                            if (modelData !== -1) {
                                amount = modelData
                            }
                        }
                    }
                }
            }
        }

        onAccepted: {
            // 执行存款操作
            transfer(account, amount)
        }
    }

    Dialog {
        id: withdrawDialog
        title: "取款"
        standardButtons: Dialog.Ok | Dialog.Cancel

        Column {
            spacing: 10

            TextField {
                placeholderText: "金额"
                onTextChanged: amount = parseFloat(text)
            }

            // 金额选项按钮
            Row {
                spacing: 5
                Repeater {
                    model: [100, 500, 1000, 10000, -1] // -1 表示自定义金额
                    Button {
                        text: modelData === -1 ? "自定义金额" : modelData
                        onClicked: {
                            if (modelData !== -1) {
                                amount = modelData
                            }
                        }
                    }
                }
            }
        }

        onAccepted: {
            // 执行取款操作
             transfer(account, -amount)
        }
    }

    Dialog {
        id: transferDialog
        title: "转账"
        standardButtons: Dialog.Ok | Dialog.Cancel

        Column {
            spacing: 10

            TextField {
                placeholderText: "目标账户"
                onTextChanged: transferTo = text
            }

            TextField {
                placeholderText: "金额"
                onTextChanged: transferAmount = parseFloat(text)
            }

            // 金额选项按钮
            Row {
                spacing: 5
                Repeater {
                    model: [100, 500, 1000, 10000, -1] // -1 表示自定义金额
                    Button {
                        text: modelData === -1 ? "自定义金额" : modelData
                        onClicked: {
                            if (modelData !== -1) {
                                transferAmount = modelData
                            }
                        }
                    }
                }
            }
        }

        onAccepted: {
            // 执行转账操作
            transfer(transferTo, transferAmount)
        }
    }
}
