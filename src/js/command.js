var Ready = 0
var Add = 1
var Insert = 2
var Update = 3
var Delete = 4

function run(event) {
    if (commandState === Ready) {
        switch (event.text) {
            case "a": commandState = Add; break
            case "i": commandState = Insert; break
            case "d": commandState = Delete; break
            case "u": commandState = Update; break
        }
    } else if (commandState === Add) {
        switch (event.text) {

        }
    } else if (commandState === Insert) {
        switch (event.text) {

        }
    } else if (commandState === Delete) {
        switch (event.text) {

        }
    } else if (commandState === Update) {
        switch (event.text) {

        }
    }
}

function cancel() {
    commandState = Ready
}


