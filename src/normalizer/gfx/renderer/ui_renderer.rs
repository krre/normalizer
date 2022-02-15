use super::Renderer;
use wgpu::{CommandEncoder, TextureView};

pub struct UiRenderer {}

impl UiRenderer {
    pub fn new() -> Self {
        Self {}
    }
}

impl Renderer for UiRenderer {
    fn draw(&self, encoder: &mut CommandEncoder, view: &TextureView) {}

    fn is_dirty(&self) -> bool {
        return false;
    }
}
