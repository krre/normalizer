use std::{cell::RefCell, error::Error, rc::Rc};

use antiq::{
    application::Application,
    preferences::{Format, PreferencesBuilder},
    ui::d2::geometry::Size2D,
    window::Window,
};

use crate::style::BACKGROUND_COLOR;

use super::{Preferences, application::NAME, preferences::AppPreferences};

pub struct MainWindow {
    window: Rc<RefCell<Window>>,
    preferences: Preferences,
}

impl MainWindow {
    pub fn new(app: &Application) -> Result<Self, Box<dyn Error>> {
        let mut window = Window::new(app)?;
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
            window: Rc::new(RefCell::new(window)),
            preferences,
        })
    }

    fn save_preferences(&mut self) {
        let window = self.window.borrow();
        let data = self.preferences.get_mut();
        data.window.pos = window.position();
        data.window.size = window.size();
        self.preferences.save();
    }
}

impl Drop for MainWindow {
    fn drop(&mut self) {
        self.save_preferences();
    }
}
