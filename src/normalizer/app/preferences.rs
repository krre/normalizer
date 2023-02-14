use serde::{Deserialize, Serialize};

#[derive(Default, Serialize, Deserialize)]
pub struct Preferences {
    pub window: Window,
}

#[derive(Default, Serialize, Deserialize)]
pub struct Window {
    pub x: u32,
    pub y: u32,
    pub width: u32,
    pub height: u32,
}

impl Preferences {
    pub fn new() -> Self {
        Self {
            ..Default::default()
        }
    }

    pub fn save(&self) {
        let value = serde_json::to_string(&self).unwrap();
        println!("value {}", value);
    }
}
