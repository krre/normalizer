use std::{error::Error, rc::Rc};

use super::{MainWindow, Preferences};

pub const NAME: &str = "Normalizer";
pub const ORGANIZATION: &str = "Norm";

pub struct Application {
    app: antiq::core::Application,
    main_window: MainWindow,
    preferences: Rc<Preferences>,
}

impl Application {
    pub fn new() -> Result<Self, Box<dyn Error>> {
        let app = antiq::core::ApplicationBuilder::new()
            .name(NAME)
            .organization(ORGANIZATION)
            .build()?;

        let mut preferences = Preferences::new();
        preferences.load();

        let preferences = Rc::new(preferences);
        let main_window = MainWindow::new(app.context().clone(), preferences.clone())?;

        Ok(Self {
            app,
            main_window,
            preferences,
        })
    }

    pub fn run(&self) -> Result<(), Box<dyn Error>> {
        self.app.run()
    }
}

impl Drop for Application {
    fn drop(&mut self) {
        self.preferences.save();
    }
}
