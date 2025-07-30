use antiq::{Application, ui::Ui3d};

pub struct Normalizer {}

impl Normalizer {
    fn new() -> Self {
        Self {}
    }
}

impl Application for Normalizer {
    fn build_ui(&self) -> Ui3d {
        Ui3d {}
    }
}

impl Default for Normalizer {
    fn default() -> Self {
        Self::new()
    }
}
