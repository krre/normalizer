// GSG - Greenery Scene Graph

function Scene() {
    this.currentNode = new CurrentNode()
    this.render = function() { print("render") }
}

function CurrentNode() {
    this.moduleId = "0"
}
