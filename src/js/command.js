
function run(event) {
    if (!mainRoot.commandState) {
        switch (event.text) {
            case "a": mainRoot.commandState = "Add"; break
            case "d": mainRoot.commandState = "Delete"; break
            case "u": mainRoot.commandState = "Update"; break
            case "m": mainRoot.commandState = "Move"; break
        }
    } else if (mainRoot.commandState === "Add" || mainRoot.commandState === "Update") {
        switch (event.text) {
            case "e": mainRoot.commandState = "Expression"; break
            case "l": mainRoot.commandState = "Literal"; break
        }
    }
}

function cancel() {
    mainRoot.commandState = ""
}

function add(value) {
    if (value) {
        if (mainRoot.commandState === "Expression") {
            addExpression(value)
        } else if (mainRoot.commandState === "Literal") {
            addLiteral(value)
        }
    }
    cancel()
    print(JSON.stringify(currentTab.astModel))
}

function addExpression(value) {
    print("expression:", value)
}

function addLiteral(value) {
    print("literal:", value)
}

