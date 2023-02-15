use std::cell::RefCell;
use std::rc::Rc;

use antiq::core::Window;
use antiq::core::{Application, Color};

use super::Preferences;

pub struct AppWindow {
    preferences: RefCell<Preferences>,
    window: Rc<Window>,
}

impl AppWindow {
    pub fn new(app: &Application) -> Self {
        let window = app.create_window();
        window.set_title("Normalizer");
        window.set_color(Color::new(0.3, 0.3, 0.3, 1.0));

        Self {
            preferences: RefCell::new(Preferences::new()),
            window,
        }
    }

    pub fn finish(&self) {
        let mut prefs = self.preferences.borrow_mut();

        (prefs.window.width, prefs.window.height) = self.window.size();
        (prefs.window.x, prefs.window.y) = self.window.position();

        prefs.save();

        println!("finish");
    }
}
