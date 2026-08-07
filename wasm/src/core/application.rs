use antiq::{
    Application,
    ui::{Color, Ui3d},
};

#[derive(Default)]
pub struct Normalizer {}

impl Application for Normalizer {
    fn build_ui(&self) -> Ui3d {
        let mut ui = Ui3d::new();
        ui.set_background_color(&Color::from_rgb(0.25, 0.23, 0.23));
        ui
    }
}
