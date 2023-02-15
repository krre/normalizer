use antiq::core::{Application, Color, Window};

use super::Preferences;

pub struct AppWindow<'a> {
    window: &'a Window,
    preferences: Preferences,
}

impl<'a> AppWindow<'a> {
    pub fn new(app: &'a mut Application) -> Self {
        let window = app.create_window();
        window.set_title("Normalizer");
        window.set_color(Color::new(0.3, 0.3, 0.3, 1.0));

        Self {
            window,
            preferences: Preferences::new(),
        }
    }
}

impl<'a> Drop for AppWindow<'a> {
    fn drop(&mut self) {
        (
            self.preferences.window.width,
            self.preferences.window.height,
        ) = self.window.size();

        (self.preferences.window.x, self.preferences.window.y) = self.window.position();

        self.preferences.save();
    }
}
