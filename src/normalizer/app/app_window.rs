use std::rc::Rc;

use antiq::core::Window;
use antiq::core::{Application, Color};

use super::Preferences;

pub struct AppWindow {
    preferences: Preferences,
    window: Rc<Window>,
}

impl AppWindow {
    pub fn new(app: &mut Application) -> Self {
        let window = app.create_window();
        window.set_title(&Application::name().unwrap());
        window.set_color(Color::new(0.3, 0.3, 0.3, 1.0));

        let mut preferences = Preferences::new();

        if preferences.load() {
            window.set_position(preferences.window.x, preferences.window.y);
            window.set_size(preferences.window.width, preferences.window.height);
        }

        Self {
            preferences,
            window,
        }
    }

    pub fn finish(&self) {}
}

impl Drop for AppWindow {
    fn drop(&mut self) {
        (
            self.preferences.window.width,
            self.preferences.window.height,
        ) = self.window.size();

        (self.preferences.window.x, self.preferences.window.y) = self.window.position();

        self.preferences.save();
    }
}
