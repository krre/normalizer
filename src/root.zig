const std = @import("std");
const angie3d = @import("angie3d");
const Normalizer = @import("Normalizer.zig");

export fn main() void {
    angie3d.runApp(Normalizer, std.heap.wasm_allocator);
}
