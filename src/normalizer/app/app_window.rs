use antiq::core::window::Window;
use antiq::core::Application;

pub struct AppWindow<'a> {
    _window: &'a Window,
}

impl<'a> AppWindow<'a> {
    pub fn new(app: &'a mut Application) -> Self {
        let window = app.create_window();
        window.set_title("Normalizer");
        Self { _window: window }
    }
}
