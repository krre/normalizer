use std::error::Error;

pub const NAME: &str = "Normalizer";
pub const ORGANIZATION: &str = "Norm";

pub struct Application {
    app: antiq::application::Application,
}

impl Application {
    pub fn new() -> Result<Self, Box<dyn Error>> {
        let app = antiq::application::ApplicationBuilder::new()
            .name(NAME)
            .organization(ORGANIZATION)
            .build()?;

        Ok(Self { app })
    }

    pub fn run(&self) -> Result<(), Box<dyn Error>> {
        self.app.run()
    }
}
