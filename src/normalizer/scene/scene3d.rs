use crate::renderer::Renderer;

use super::Scene;

pub struct Scene3d {}

impl Scene3d {
    pub fn new() -> Self {
        Self {}
    }
}

impl Scene for Scene3d {
    fn draw(&self, renderer: &Renderer) {}
}
