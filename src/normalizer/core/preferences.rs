use serde::{Deserialize, Serialize};

pub type Preferences = antiq::core::Preferences<Settings>;

#[derive(Default, Serialize, Deserialize)]
pub struct Settings {
    pub window: Window,
}

#[derive(Default, Serialize, Deserialize)]
pub struct Window {
    pub x: i32,
    pub y: i32,
    pub width: u32,
    pub height: u32,
    pub is_maximized: bool,
}
