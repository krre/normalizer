use antiq::core::window::Window;
use antiq::core::{Application, Color};

pub struct AppWindow<'a> {
    _window: &'a Window,
}

impl<'a> AppWindow<'a> {
    pub fn new(app: &'a mut Application) -> Self {
        let window = app.create_window();
        window.set_title("Normalizer");
        window.set_color(Color::new(0.3, 0.3, 0.3, 1.0));
        Self { _window: window }
    }
}
