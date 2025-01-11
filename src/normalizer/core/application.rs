use std::{cell::RefCell, error::Error, rc::Rc};

use antiq::preferences::{Format, PreferencesBuilder};

use super::MainWindow;

pub const NAME: &str = "Normalizer";
pub const ORGANIZATION: &str = "Norm";

pub struct Application {
    app: antiq::application::Application,
    main_window: MainWindow,
}

impl Application {
    pub fn new() -> Result<Self, Box<dyn Error>> {
        let app = antiq::application::ApplicationBuilder::new()
            .name(NAME)
            .organization(ORGANIZATION)
            .build()?;

        let mut preferences = PreferencesBuilder::new(app.context().clone())
            .format(Format::Pretty)
            .build();
        preferences.load();

        let preferences = Rc::new(RefCell::new(preferences));
        let main_window = MainWindow::new(app.context().clone(), preferences.clone())?;

        Ok(Self { app, main_window })
    }

    pub fn run(&self) -> Result<(), Box<dyn Error>> {
        self.app.run()
    }
}
