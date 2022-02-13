use super::Renderer;

pub struct SceneRenderer {}

impl Renderer for SceneRenderer {
    fn draw(&self) {
        println!("SceneRenderer draw")
    }

    fn render(&self) {
        println!("SceneRenderer render")
    }

    fn is_dirty(&self) -> bool {
        return false;
    }
}
