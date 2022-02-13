use super::Renderer;

pub struct UiRenderer {}

impl Renderer for UiRenderer {
    fn draw(&self) {
        println!("UiRenderer draw")
    }

    fn render(&self) {
        println!("UiRenderer render")
    }

    fn is_dirty(&self) -> bool {
        return false;
    }
}
