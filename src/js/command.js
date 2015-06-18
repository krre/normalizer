function run(event) {
    if (commandState === "ready") {
        switch (event.text) {
            case "a": commandState = "add"; break
            case "d": commandState = "delete"; break
            case "u": commandState = "update"; break
            case "m": commandState = "move"; break
            case ".": increasePos(); break
            case ",": decreasePos(); break
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
    print("currentPos", currentTab.currentPos)
}

function addExpression(value) {
    var node = []
    node.push(value)
    currentTab.currentNode.push(node)
    currentTab.currentNode = node
    currentTab.currentPos = 0
}

function addLiteral(value) {
    currentTab.currentNode.push(value)
    currentTab.currentPos++
}

function increasePos() {
    if (currentNode.length > 1) {
        currentPos = Math.min(currentNode.length - 1, ++currentPos)
    }
    print("currentPos", currentTab.currentPos)
}

function decreasePos() {
    if (currentNode.length > 1) {
        currentPos = Math.max(0, --currentPos)
    }
    print("currentPos", currentTab.currentPos)
}

