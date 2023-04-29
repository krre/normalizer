use std::cell::RefCell;
use std::rc::Rc;

use antiq::core::window::Id;
use antiq::core::{layout, Window};
use antiq::core::{Application, Color};

use super::Preferences;

pub struct AppWindow {
    app: Application,
    preferences: Rc<RefCell<Preferences>>,
    window_id: Id,
}

impl AppWindow {
    pub fn new() -> Self {
        let mut app = Application::new();
        let mut window = app.create_window(Box::new(layout::Box::new()));

        window.set_title(&Application::name().unwrap());
        window.set_color(Color::new(0.3, 0.3, 0.3, 1.0));

        let mut preferences = Preferences::new();

        if preferences.load() {
            window.set_position(preferences.window.position);
            window.set_size(preferences.window.size);
            window.set_maximized(preferences.window.is_maximized);
        }

        let window_id = window.id();

        drop(window);

        let result = Self {
            preferences: Rc::new(RefCell::new(preferences)),
            window_id,
            app,
        };

        result.setup();
        result
    }

    pub fn run(&mut self) {
        self.app.run();
    }

    fn setup(&self) {
        let mut window = self.app.window_mut(self.window_id);

        let prefs = self.preferences.clone();
        let handler = move |w: &Window| {
            let mut prefs = prefs.borrow_mut();
            prefs.window.position = w.position();
            prefs.window.size = w.size();
            prefs.save();
        };

        window.set_drop_handler(Box::new(handler));
    }
}
