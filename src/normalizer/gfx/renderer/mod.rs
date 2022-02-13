pub mod scene_renderer;
pub mod ui_renderer;

pub use scene_renderer::SceneRenderer;
pub use ui_renderer::UiRenderer;

pub trait Renderer {
    fn draw(&self);
    fn render(&self);
    fn is_dirty(&self) -> bool;
}
