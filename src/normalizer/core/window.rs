use std::sync::Arc;

use winit::keyboard::ModifiersState;

use crate::{
    renderer::Renderer,
    scene::{scene2d::Scene2d, scene3d::Scene3d, Scene},
};

pub struct Window {
    winit_window: Arc<winit::window::Window>,
    modifiers: ModifiersState,
    scene2d: Scene2d,
    scene3d: Scene3d,
}

impl Window {
    pub fn new(winit_window: winit::window::Window) -> Self {
        Self {
            winit_window: Arc::new(winit_window),
            modifiers: Default::default(),
            scene2d: Scene2d::new(),
            scene3d: Scene3d::new(),
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

    pub fn set_modifiers(&mut self, modifiers: ModifiersState) {
        self.modifiers = modifiers;
    }

    pub fn modifiers(&self) -> &ModifiersState {
        &self.modifiers
    }

    pub fn redraw(&self) {
        self.winit_window.request_redraw();
    }

    pub fn inner(&self) -> Arc<winit::window::Window> {
        self.winit_window.clone()
    }

    pub fn draw(&self, renderer: &Renderer) {
        self.scene3d.draw(renderer);
        self.scene2d.draw(renderer);
    }
}
