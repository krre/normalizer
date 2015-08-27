var Ready = "ready"
var Add = "add"
var Edit = "edit"
var Delete = "delete"
var Go = "go"

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



