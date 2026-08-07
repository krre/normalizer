const std = @import("std");
const angie3d = @import("angie3d");
const console = angie3d.console;
const js = angie3d.js;
const Normalizer = @import("Normalizer.zig");

export fn start() void {
    console.log("Application starting", .{});

    Normalizer.init(std.heap.wasm_allocator);
    js.event_handler = Normalizer.app.eventHandler();
    Normalizer.app.render();

    console.log("Application started", .{});
}
