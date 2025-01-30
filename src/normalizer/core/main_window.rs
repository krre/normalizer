use std::{error::Error, rc::Rc};

use antiq::{
    application::Application,
    core::Size2D,
    preferences::{Format, PreferencesBuilder},
};

use crate::style::BACKGROUND_COLOR;

use super::{application::NAME, preferences::AppPreferences, Preferences};

pub struct MainWindow {
    window: Rc<antiq::window::Window>,
    preferences: Preferences,
}

impl MainWindow {
    pub fn new(app: &Application) -> Result<Self, Box<dyn Error>> {
        let window = antiq::window::Window::new(app.context())?
            .upgrade()
            .unwrap();
        window.set_title(NAME);
        window.set_color(BACKGROUND_COLOR);
        window.set_visible(true);

        let mut preferences = PreferencesBuilder::new(&app).format(Format::Pretty).build();
        preferences.load();

        if preferences.is_loaded() {
            let data: &AppPreferences = preferences.get_ref();
            window.set_position(data.window.pos);
            window.set_size(data.window.size);
        } else {
            window.set_size(Size2D::new(1200, 800));
        }

        Ok(Self {
            window,
            preferences,
        })
    }
}

impl Drop for MainWindow {
    fn drop(&mut self) {
        let data = self.preferences.get_mut();
        data.window.pos = self.window.position();
        data.window.size = self.window.size();
        self.preferences.save();
    }
}
