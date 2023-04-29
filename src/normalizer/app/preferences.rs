use std::{
    fs::{DirBuilder, File},
    io::{Read, Write},
    path::PathBuf,
};

use antiq::core::{Application, Position, Size};
use serde::{Deserialize, Serialize};

#[derive(Default, Serialize, Deserialize)]
pub struct Preferences {
    pub window: Window,
}

#[derive(Default, Serialize, Deserialize)]
pub struct Window {
    pub position: Position,
    pub size: Size,
    pub is_maximized: bool,
}

impl Preferences {
    pub fn new() -> Self {
        Self {
            ..Default::default()
        }
    }

    pub fn load(&mut self) -> bool {
        if let Ok(mut f) = File::open(Self::path()) {
            let mut contents = String::new();
            f.read_to_string(&mut contents).unwrap();
            *self = serde_json::from_slice::<Preferences>(contents.as_bytes()).unwrap();
            return true;
        }

        false
    }

    pub fn save(&self) {
        let value = serde_json::to_string(&self).unwrap();

        DirBuilder::new()
            .recursive(true)
            .create(Self::dir())
            .unwrap();

        let mut file = File::create(Self::path()).unwrap();
        file.write_all(value.as_bytes()).unwrap();
    }

    pub fn dir() -> String {
        let mut result = dirs::config_dir().unwrap();
        result.push(Application::organization().unwrap());
        result.to_str().unwrap().to_string()
    }

    pub fn path() -> String {
        let mut result = PathBuf::new();
        result.push(Self::dir());
        result.push(Application::name().unwrap() + ".prefs");
        result.to_str().unwrap().to_string()
    }
}
