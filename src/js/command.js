function run(event) {
    if (commandState === "ready") {
        switch (event.text) {
            case "a": commandState = "add"; break
            case "d": commandState = "delete"; break
            case "u": commandState = "update"; break
            case "m": commandState = "move"; break
        }
    } else if (commandState === "add" || commandState === "update") {
        switch (event.text) {
            case "e": commandState = "expression"; break
            case "l": commandState = "literal"; break
        }
    }
}

function cancel() {
    commandState = "ready"
}

function add(value) {
    if (value) {
        if (commandState === "expression") {
            addExpression(value)
        } else if (commandState === "literal") {
            addLiteral(value)
        }
    }
    cancel()
    print(JSON.stringify(currentTab.astModel))
}

function addExpression(value) {
    var node = {}
    node[value] = []
    currentTab.currentNode.push(node)
    print("expression:", value)
    currentTab.currentNode = node[value]
}

function addLiteral(value) {
    currentTab.currentNode.push(value)
    print("literal:", value)
}

