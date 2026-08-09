const std = @import("std");
const angie3d = @import("angie3d");
const Widget = angie3d.ui.widget.Widget;
const Box = angie3d.ui.widget.Box;
const Application = angie3d.core.Application;

const Normalizer = @This();

root: Box,

pub fn init(app: *Application) Normalizer {
    app.setTitle("Normalizer");

    return Normalizer{
        .root = Box.init(app.allocator),
    };
}

pub fn rootWidget(self: *Normalizer) *Widget {
    return &self.root.widget;
}
