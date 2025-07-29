use antiq::Application;

pub struct Normalizer {}

impl Normalizer {
    fn new() -> Self {
        Self {}
    }
}

impl Application for Normalizer {
    fn run(&self) {
        antiq::log("Run Webassembly Normalizer");
    }
}

impl Default for Normalizer {
    fn default() -> Self {
        Self::new()
    }
}
