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
        window.set_title("Normalizer");
        window.set_color(Color::new(0.3, 0.3, 0.3, 1.0));

        Self {
            preferences: Preferences::new(),
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
