const angie3d = @import("angie3d");
const Normalizer = @import("Normalizer.zig");

export fn start() void {
    angie3d.runApp(Normalizer);
}
