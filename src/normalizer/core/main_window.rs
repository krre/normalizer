use std::{
    cell::RefCell,
    error::Error,
    rc::{Rc, Weak},
};

use antiq::{
    application::Application,
    core::{Size2D, UpgradeOrErr},
    preferences::{Format, PreferencesBuilder},
    window::Window,
};

use crate::style::BACKGROUND_COLOR;

use super::{Preferences, application::NAME, preferences::AppPreferences};

pub struct MainWindow {
    window: Weak<RefCell<Window>>,
    preferences: Preferences,
}

impl MainWindow {
    pub fn new(app: &Application) -> Result<Self, Box<dyn Error>> {
        let window = Window::new(app)?.upgrade_or_err()?;
        let mut win = window.borrow_mut();
        win.set_title(NAME);
        win.set_color(BACKGROUND_COLOR);
        win.set_visible(true);

        let mut preferences = PreferencesBuilder::new(&app).format(Format::Pretty).build();
        preferences.load();

        if preferences.is_loaded() {
            let data: &AppPreferences = preferences.get_ref();
            win.set_position(data.window.pos);
            win.set_size(data.window.size);
        } else {
            win.set_size(Size2D::new(1200, 800));
        }

        Ok(Self {
            window: Rc::downgrade(&window),
            preferences,
        })
    }
}

impl Drop for MainWindow {
    fn drop(&mut self) {
        if let Some(w) = self.window.upgrade() {
            let windon = w.borrow();
            let data = self.preferences.get_mut();
            data.window.pos = windon.position();
            data.window.size = windon.size();
            self.preferences.save();
        }
    }
}
