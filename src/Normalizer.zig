const std = @import("std");
const Allocator = std.mem.Allocator;
const angie3d = @import("angie3d");
const Box = angie3d.ui.widget.Box;
const Application = angie3d.ui.Application;

const Umbrella = @This();

pub var app: Application = undefined;
var root: Box = undefined;

pub fn init(allocator: Allocator) void {
    root = Box.init(allocator);
    app = Application.init(allocator, &root.widget);
    Application.setTitle("Normalizer");
}
