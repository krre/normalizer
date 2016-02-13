.import "utils.js" as Utils
.import "object-factory.js" as ObjectFactory

var panelPath = "qrc:/qml/components/Panel.qml"

var operators = [
    { name: "Print", shortcut: "P", action: printOp },
    { name: "Flow", shortcut: "F", action: flowOp },
    { name: "Add", shortcut: "Ctrl+A", action: addOp },
    { name: "Remove", shortcut: "Ctrl+R", action: removeOp },
    { name: "Update", shortcut: "Ctrl+U", action: updateOp },
    { name: "Project", shortcut: "", action: projectOp },
    { name: "Module", shortcut: "", action: moduleOp },
    { name: "Function", shortcut: "", action: functionOp },
    { name: "Expression", shortcut: "", action: expressionOp },
    { name: "Condition", shortcut: "", action: conditionOp }
]

function add() {
    for (var i = 0; i < operators.length; i++) {
        OperatorModel.addOperator(operators[i])
    }
}

function printOp() {
    program.print = ObjectFactory.print()
}

function flowOp() {
    program.flow = ObjectFactory.flow()
}

function addOp() {
    print("add")
}

function removeOp() {
    print("remove")
}

function updateOp() {
    print("update")
}

function projectOp() {
    print("project")
}

function moduleOp() {
    print("module")
}

function functionOp() {
    panel = Utils.createDynamicObject(currentTab, panelPath, { state: "function" })
    panel.enter.connect(function(value) {
        var records = sproutDb.query("SELECT * FROM Functions WHERE moduleId=0")
        for (var i = 0; i < records.length; i++) {
            print(JSON.stringify(records[i]))
        }

    //    sproutDb.query("INSERT INTO Functions(name, moduleId) VALUES('func', %1)".arg(pos.moduleId))
    })
}

function expressionOp() {
    print("expression")
}

function conditionOp() {
    print("condition")
}
