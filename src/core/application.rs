pub struct Normalizer {}

impl Normalizer {
    pub fn new() -> Self {
        Self {}
    }
}

impl antiq::Application for Normalizer {
    fn run(&self) {}
}

impl Default for Normalizer {
    fn default() -> Self {
        Self::new()
    }
}
