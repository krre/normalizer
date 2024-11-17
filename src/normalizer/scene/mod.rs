use crate::renderer::Renderer;

pub mod scene2d;
pub mod scene3d;

pub trait Scene {
    fn draw(&self, renderer: &Renderer);
}
