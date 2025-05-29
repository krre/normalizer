use std::error::Error;

use super::MainWindow;

pub const NAME: &str = "Normalizer";
pub const ORGANIZATION: &str = "Norm";

pub struct Application {
    app: antiq::application::Application,
    _main_window: MainWindow,
}

impl Application {
    pub fn new() -> Result<Self, Box<dyn Error>> {
        let app = antiq::application::ApplicationBuilder::new()
            .name(NAME)
            .organization(ORGANIZATION)
            .build()?;

        let main_window = MainWindow::new(&app)?;

        Ok(Self {
            app,
            _main_window: main_window,
        })
    }

    pub fn run(&self) -> Result<(), Box<dyn Error>> {
        self.app.run()
    }
}
