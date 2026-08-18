const angie3d = @import("angie3d");
const Application = angie3d.core.Application;
const Universe = angie3d.ui.Universe;
const View = angie3d.ui.View;

const Normalizer = @This();

universe: *Universe,

pub fn init(app: *Application) Normalizer {
    app.setTitle("Normalizer");

    const universe = app.allocator.create(Universe) catch |err| {
        switch (err) {
            error.OutOfMemory => @panic("Out of memory to create Universe"),
        }
    };

    const view = View{
        .universe = universe,
    };
    app.multiverse.setView(.{ .view = view });

    return Normalizer{
        .universe = universe,
    };
}
