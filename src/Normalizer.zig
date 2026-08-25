const angie3d = @import("angie3d");
const Application = angie3d.core.Application;
const View = angie3d.ui.View;
const Node = angie3d.ui.node.Node;

const Normalizer = @This();

scene: Node,

pub fn init(app: *Application) !Normalizer {
    app.setTitle("Normalizer");
    var normalizer = Normalizer{ .scene = Node.init() };

    app.setView(.{
        .view = View.init(&normalizer.scene),
    });

    return normalizer;
}
