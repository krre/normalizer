use std::{cell::RefCell, error::Error, rc::Rc};

use antiq::core::Size2D;

use crate::style::BACKGROUND_COLOR;

use super::{application::NAME, Preferences};

pub struct MainWindow {
    window: Rc<antiq::core::Window>,
    preferences: Rc<RefCell<Preferences>>,
}

impl MainWindow {
    pub fn new(
        context: Rc<antiq::core::Context>,
        preferences: Rc<RefCell<Preferences>>,
    ) -> Result<Self, Box<dyn Error>> {
        let window = antiq::core::Window::new(context)?.upgrade().unwrap();
        window.set_title(NAME);
        window.set_size(Size2D::new(1200, 800));
        window.set_color(BACKGROUND_COLOR);
        window.set_visible(true);

        Ok(Self {
            window,
            preferences,
        })
    }
}

impl Drop for MainWindow {
    fn drop(&mut self) {
        let mut prefs = self.preferences.borrow_mut();
        let data = prefs.get_mut();
        data.window.pos = self.window.position();
        data.window.size = self.window.size();
        prefs.save();
    }
}
