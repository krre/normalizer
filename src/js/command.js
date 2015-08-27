var Ready = 0
var Add = 1
var Edit = 2
var Delete = 3
var Go = 4

function run(event) {
    if (commandState === Ready) {
        switch (event.text) {
            case "a": commandState = Add; break
            case "d": commandState = Delete; break
            case "e": commandState = Edit; break
            case "g": commandState = Go; break
        }
    } else if (commandState === Add) {
        switch (event.text) {

        }
    } else if (commandState === Delete) {
        switch (event.text) {

        }
    } else if (commandState === Edit) {
        switch (event.text) {

        }
    } else if (commandState === Go) {
        switch (event.text) {

        }
    }
}

function cancel() {
    commandState = Ready
}


