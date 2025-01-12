use antiq::{
    core::{Pos2D, Size2D},
    preferences,
};
use serde::{Deserialize, Serialize};

pub type Preferences = preferences::Preferences<AppPreferences>;

#[derive(Default, Serialize, Deserialize)]
pub struct AppPreferences {
    pub window: Window,
}

#[derive(Default, Serialize, Deserialize)]
pub struct Window {
    pub pos: Pos2D,
    pub size: Size2D,
    pub is_maximized: bool,
}
