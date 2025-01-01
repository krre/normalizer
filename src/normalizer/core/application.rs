use std::{error::Error, rc::Weak};

use antiq::core::Size2D;

use super::Preferences;

pub const NAME: &str = "Normalizer";
pub const ORGANIZATION: &str = "Norm";

pub struct Application {
    app: antiq::core::Application,
    window: Weak<antiq::core::Window>,
    preferences: Preferences,
}

impl Application {
    pub fn new() -> Result<Self, Box<dyn Error>> {
        let app = antiq::core::ApplicationBuilder::new()
            .name(NAME)
            .organization(ORGANIZATION)
            .build()?;

        let window = antiq::core::Window::new(app.context().clone())?;
        let w = window.upgrade().unwrap();
        w.set_title(NAME);
        w.set_size(Size2D::new(1200, 800));
        w.set_visible(true);

        Ok(Self {
            app,
            window,
            preferences: Preferences::default(),
        })
    }

    pub fn run(&self) -> Result<(), Box<dyn Error>> {
        self.app.run()
    }

    pub(crate) fn update_preferences(&mut self) {
        let window = self.window.upgrade().unwrap();
        let pref_window = &mut self.preferences.window;
        pref_window.is_maximized = false; // window.is_maximized();

        if !pref_window.is_maximized {
            pref_window.width = window.size().width();
            pref_window.height = window.size().height();

            pref_window.x = window.position().x();
            pref_window.y = window.position().y();
        }
    }
}

impl Drop for Application {
    fn drop(&mut self) {
        self.preferences.save();
    }
}
