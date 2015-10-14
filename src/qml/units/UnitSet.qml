import QtQuick 2.5

Item {
    property alias project: project
    property alias module: module
    property alias instruction: instruction
    property alias argument: argument

    Component {
        id: project
        Project {}
    }

    Component {
        id: module
        Module {}
    }

    Component {
        id: func
        Function {}
    }

    Component {
        id: instruction
        Instruction {}
    }

    Component {
         id: argument
        Argument {}
    }
}
