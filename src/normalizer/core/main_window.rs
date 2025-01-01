use std::{
    error::Error,
    rc::{Rc, Weak},
};

use antiq::core::Size2D;

use super::application::NAME;

pub struct MainWindow {
    window: Weak<antiq::core::Window>,
}

impl MainWindow {
    pub fn new(context: Rc<antiq::core::Context>) -> Result<Self, Box<dyn Error>> {
        let window = antiq::core::Window::new(context)?;
        let w = window.upgrade().unwrap();
        w.set_title(NAME);
        w.set_size(Size2D::new(1200, 800));
        w.set_visible(true);

        Ok(Self { window })
    }
}
