const std = @import("std");
const angie3d = @import("angie3d");
const Widget = angie3d.ui.widget.Widget;
const Box = angie3d.ui.widget.Box;
const Application = angie3d.core.Application;

const Self = @This();

root: Box,

pub fn init(app: *Application) Self {
    app.setTitle("Normalizer");

    return Self{
        .root = Box.init(app.allocator),
    };
}

pub fn rootWidget(self: *Self) *Widget {
    return &self.root.widget;
}
