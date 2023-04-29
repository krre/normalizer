use std::cell::RefCell;

use antiq::core::layout;
use antiq::core::window::Id;
use antiq::core::{Application, Color};

use super::Preferences;

pub struct AppWindow {
    preferences: Preferences,
    window_id: Id,
    app: RefCell<Application>,
}

impl AppWindow {
    pub fn new(app: RefCell<Application>) -> Self {
        let mut app_mut = app.borrow_mut();
        let window_id = app_mut.create_window(Box::new(layout::Box::new()));
        let mut window = app_mut.window_mut(window_id);
        window.set_title(&Application::name().unwrap());
        window.set_color(Color::new(0.3, 0.3, 0.3, 1.0));

        let mut preferences = Preferences::new();

        if preferences.load() {
            window.set_position(preferences.window.position);
            window.set_size(preferences.window.size);
            window.set_maximized(preferences.window.is_maximized);
        }

        drop(window);
        drop(app_mut);

        Self {
            preferences,
            window_id,
            app,
        }
    }

    pub fn run(&self) {
        self.app.borrow_mut().run();
    }
}

impl Drop for AppWindow {
    fn drop(&mut self) {
        let app_ref = self.app.borrow();
        let window = app_ref.window_ref(self.window_id);
        self.preferences.window.position = window.position();
        self.preferences.window.size = window.size();
        self.preferences.save();
    }
}
