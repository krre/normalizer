function run(event) {
    if (!commandState) {
        switch (event.text) {
            case "a": commandState = "Add"; break
            case "d": commandState = "Delete"; break
            case "u": commandState = "Update"; break
            case "m": commandState = "Move"; break
        }
    } else if (commandState === "Add" || commandState === "Update") {
        switch (event.text) {
            case "e": commandState = "Expression"; break
            case "l": commandState = "Literal"; break
        }
    }
}

function cancel() {
    commandState = ""
}

function add(value) {
    if (value) {
        if (commandState === "Expression") {
            addExpression(value)
        } else if (commandState === "Literal") {
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

