var operators = [
    { name: "Print", shortcut: "P", action: printOperator },
    { name: "Add", shortcut: "Ctrl+A", action: addOperator },
    { name: "Remove", shortcut: "Ctrl+R", action: removeOperator },
    { name: "Update", shortcut: "Ctrl+U", action: updateOperator }
]

function add() {
    for (var i = 0; i < operators.length; i++) {
        OperatorModel.addOperator(operators[i])
    }
}

function printOperator() {
    print("print")
}

function addOperator() {
    print("add")
}

function removeOperator() {
    print("remove")
}

function updateOperator() {
    print("update")
}
