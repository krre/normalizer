use crate::renderer::Renderer;

use super::Scene;

pub struct Scene2d {}

impl Scene2d {
    pub fn new() -> Self {
        Self {}
    }
}

impl Scene for Scene2d {
    fn draw(&self, renderer: &Renderer) {}
}
