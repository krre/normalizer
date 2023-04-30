use std::cell::RefCell;
use std::rc::Rc;

use antiq::core::window::{Id, Settings};
use antiq::core::Window;
use antiq::core::{Application, Color};

use super::Preferences;

pub struct AppWindow {
    app: Application,
    preferences: Rc<RefCell<Preferences>>,
    window_id: Id,
}

impl AppWindow {
    pub fn new() -> Self {
        let mut settings = Settings::new();
        settings.set_title(&Application::name().unwrap());
        settings.set_color(Color::new(0.3, 0.3, 0.3, 1.0));

        let mut preferences = Preferences::new();

        if preferences.load() {
            settings.set_position(preferences.window.position);
            settings.set_size(preferences.window.size);
            settings.set_maximized(preferences.window.is_maximized);
        }

        let mut app = Application::new();

        let window_id = {
            let window = app.create_window(settings);
            window.id()
        };

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
