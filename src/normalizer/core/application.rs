use std::error::Error;

use super::{MainWindow, Preferences};

pub const NAME: &str = "Normalizer";
pub const ORGANIZATION: &str = "Norm";

pub struct Application {
    app: antiq::core::Application,
    main_window: MainWindow,
    preferences: Preferences,
}

impl Application {
    pub fn new() -> Result<Self, Box<dyn Error>> {
        let app = antiq::core::ApplicationBuilder::new()
            .name(NAME)
            .organization(ORGANIZATION)
            .build()?;

        let main_window = MainWindow::new(app.context().clone())?;

        Ok(Self {
            app,
            main_window,
            preferences: Preferences::new(),
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
