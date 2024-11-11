use std::sync::Arc;

pub struct Window {
    winit_window: Arc<winit::window::Window>,
}

impl Window {
    pub fn new(winit_window: winit::window::Window) -> Self {
        Self {
            winit_window: Arc::new(winit_window),
        }
    }

    pub fn width(&self) -> u32 {
        self.winit_window.inner_size().width
    }

    pub fn height(&self) -> u32 {
        self.winit_window.inner_size().height
    }

    pub fn x(&self) -> i32 {
        self.winit_window.outer_position().as_ref().unwrap().x
    }

    pub fn y(&self) -> i32 {
        self.winit_window.outer_position().as_ref().unwrap().y
    }

    pub fn is_maximized(&self) -> bool {
        self.winit_window.is_maximized()
    }

    pub fn set_visible(&self, visible: bool) {
        self.winit_window.set_visible(visible);
    }

    pub fn redraw(&self) {
        self.winit_window.request_redraw();
    }

    pub fn inner(&self) -> Arc<winit::window::Window> {
        self.winit_window.clone()
    }
}
