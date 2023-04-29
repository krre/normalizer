use std::cell::RefCell;
use std::rc::Rc;

use antiq::core::window::Id;
use antiq::core::{layout, Window};
use antiq::core::{Application, Color};

use super::Preferences;

pub struct AppWindow {
    preferences: Rc<RefCell<Preferences>>,
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

        let result = Self {
            preferences: Rc::new(RefCell::new(preferences)),
            window_id,
            app,
        };

        result.setup();
        result
    }

    pub fn run(&self) {
        self.app.borrow_mut().run();
    }

    fn setup(&self) {
        let app_ref = self.app.borrow();
        let mut window = app_ref.window_mut(self.window_id);

        let prefs = self.preferences.clone();
        let handler = move |w: &Window| {
            prefs.borrow_mut().window.position = w.position();
            prefs.borrow_mut().window.size = w.size();
            prefs.borrow().save();
        };

        window.set_drop_handler(Box::new(handler));
    }
}
