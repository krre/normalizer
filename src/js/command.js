function run(event) {
    return
    if (commandState === "ready") {
        switch (event.text) {
            case "a": commandState = "add"; break
            case "i": commandState = "insert"; break
            case "d": commandState = "delete"; break
            case "u": commandState = "update"; break
            case ".": increasePos(); break
            case ",": decreasePos(); break
            case "m": upLevel(); break
            case "/": downLevel(); break
        }
    } else if (commandState === "add" || commandState === "insert" || commandState === "update") {
        switch (event.text) {
            case "e": commandState += " | expression"; inputField.isActive = true; break
            case "l": commandState += " | literal"; inputField.isActive = true; break
        }
    }
}

function cancel() {
//    commandState = "ready"
//    inputField.isActive = false
}

function newItem(value) {
    if (value) {
        var operation = commandState.split(" ").join("").split("|")
        if (operation[0] === "add") {
            if (operation[1] === "expression") {
                addExpression(value)
            } else if (operation[1] === "literal") {
                addLiteral(value)
            }
        } else if (operation[0] === "insert") {
            if (operation[1] === "expression") {
                insertExpression(value)
            } else if (operation[1] === "literal") {
                insertLiteral(value)
            }
        }
    }
    cancel()
    currentTab.loadModel()
}

function addExpression(value) {
    var node = []
    node.push(value)
    if (currentTab.currentNode.length) {
        currentTab.currentNode.splice(currentTab.currentPos + 1, 0, node)
    } else {
        currentTab.currentNode.push(node)
    }

    currentTab.parentStack.push(currentTab.currentNode)
    currentTab.currentNode = node
    currentTab.currentPos = 0
}

function insertExpression(value) {
    var node = []
    node.push(value)
    if (currentTab.currentNode.length) {
        currentTab.currentNode.splice(currentTab.currentPos, 0, node)
    } else {
        currentNode.push(node)
    }
    currentTab.parentStack.push(currentTab.currentNode)
    currentTab.currentNode = node
    currentTab.currentPos = 0
}

function addLiteral(value) {
    currentTab.currentPos++
    currentTab.currentNode.splice(currentTab.currentPos, 0, value)
}

function insertLiteral(value) {
    currentTab.currentNode.splice(currentTab.currentPos, 0, value)
}

function increasePos() {
    if (currentNode.length > 1) {
        currentPos = Math.min(currentNode.length - 1, ++currentPos)
    }
//    print("currentPos", currentTab.currentPos)
}

function decreasePos() {
    if (currentNode.length > 1) {
        currentPos = Math.max(0, --currentPos)
    }
//    print("currentPos", currentTab.currentPos)
}

function upLevel() {
    if (currentTab.parentStack.length) {
        var innerNode = currentTab.currentNode
        currentTab.currentNode = currentTab.parentStack.pop()
        for (var index in currentTab.currentNode) {
            if (currentTab.currentNode[index] === innerNode) {
                currentTab.currentPos = index
            }
        }
    }
}

function downLevel() {
    if (currentTab.currentNode.length) {
        currentTab.parentStack.push(currentTab.currentNode)
        currentTab.currentNode = currentTab.currentNode[currentTab.currentPos]
        currentTab.currentPos = 0
    }
}

