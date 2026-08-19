const angie3d = @import("angie3d");
const Application = angie3d.core.Application;
const Universe = angie3d.ui.Universe;
const View = angie3d.ui.View;

const Normalizer = @This();

universe: *Universe,

pub fn init(app: *Application) !Normalizer {
    app.setTitle("Normalizer");
    const universe = try app.allocator.create(Universe);

    app.multiverse.setView(.{
        .view = View{
            .universe = universe,
        },
    });

    return Normalizer{
        .universe = universe,
    };
}
