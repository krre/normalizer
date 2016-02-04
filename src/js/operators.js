.import "object-factory.js" as ObjectFactory

var operators = [
    { name: "Print", shortcut: "P", action: printOp },
    { name: "Flow", shortcut: "F", action: flowOp },
    { name: "Add", shortcut: "Ctrl+A", action: addOp },
    { name: "Remove", shortcut: "Ctrl+R", action: removeOp },
    { name: "Update", shortcut: "Ctrl+U", action: updateOp }
]

function add() {
    for (var i = 0; i < operators.length; i++) {
        OperatorModel.addOperator(operators[i])
    }
}

function printOp() {
    print("print")
}

function flowOp() {
    print("flow")
    program.flow = ObjectFactory.flow()
    isDirty = true
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
