use std::{
    error::Error,
    rc::{Rc, Weak},
};

use antiq::core::Size2D;

use crate::style::BACKGROUND_COLOR;

use super::{application::NAME, Preferences};

pub struct MainWindow {
    window: Weak<antiq::core::Window>,
    preferences: Rc<Preferences>,
}

impl MainWindow {
    pub fn new(
        context: Rc<antiq::core::Context>,
        preferences: Rc<Preferences>,
    ) -> Result<Self, Box<dyn Error>> {
        let window = antiq::core::Window::new(context)?;
        let w = window.upgrade().unwrap();
        w.set_title(NAME);
        w.set_size(Size2D::new(1200, 800));
        w.set_color(BACKGROUND_COLOR);
        w.set_visible(true);

        Ok(Self {
            window,
            preferences,
        })
    }
}

impl Drop for MainWindow {
    fn drop(&mut self) {
        self.preferences.save();
    }
}
