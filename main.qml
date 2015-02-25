import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import Qt.labs.settings 1.0
import QtQuick.Controls 1.2

ApplicationWindow {
	id: window
	title: qsTr("Client")
	width: 640
	height: 480
	minimumWidth: 640
	minimumHeight: 320
	visible: true

	// Save window properties to restore at next start.
	Settings {
		category: "client"

		property alias x: window.x
		property alias y: window.y
		property alias width: window.width
		property alias height: window.height
		property alias flags: window.flags
		property alias orientation: window.contentOrientation
	}

	// Define signals emitted by QML
	signal signalStartVM(string uuid)

	// Define slots for signals from C++
	function onNameChanged() {
		console.log("QML:) ", Client.name)
	}

	// Register component in C++
	Component.onCompleted: {
		// Register instance in C++ class
		Client.setQmlItem(window)

		// Connect C++ signals to QML slots
		Client.nameChanged.connect(onNameChanged)

		// Connect QML signals to C++ slots
		window.signalStartVM.connect(Client.slotStartVM)
	}

	// Create the actions used for menus.
	Action {
		id: startVM
		text: qsTr("Start VM")
		shortcut: StandardKey.Copy
		enabled: true
		onTriggered: {
			Client.startVM("foobar")
			signalStartVM("abcdef")
			Client.name = "gogobla"
		}
	}

	menuBar: MenuBar {
		Menu {
			title: qsTr("&File")
			MenuItem {
				text: qsTr("&Open")
				onTriggered: messageDialog.show(qsTr("Open action triggered"));
			}
			MenuItem {
				text: qsTr("E&xit")
				onTriggered: Qt.quit();
			}
			MenuItem { action: startVM }
		}
	}

	MainForm {
		anchors.fill: parent
		button1.onClicked: {
			startVM.trigger()
		}
		button2.onClicked: {
			messageDialog.show(qsTr("Button 2 pressed"))
		}
		button3.onClicked: {
			messageDialog.show(qsTr("Button 3 pressed"))
		}
	}

	MessageDialog {
		id: messageDialog
		title: qsTr("May I have your attention, please?")

		function show(caption) {
			messageDialog.text = caption;
			messageDialog.open();
		}
	}
}
