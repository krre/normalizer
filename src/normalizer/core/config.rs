use serde_derive::{Deserialize, Serialize};
use std::fs;
use std::path::PathBuf;
use std::sync::Mutex;
use winit;

lazy_static! {
    pub static ref CONFIG: Mutex<Config> = Mutex::new(Config::new());
}

#[derive(Deserialize, Serialize, Debug)]
pub struct Config {
    pub window: Option<Window>,
}

#[derive(Deserialize, Serialize, Debug)]
pub struct Window {
    pub x: i32,
    pub y: i32,
    pub width: u32,
    pub height: u32,
}

fn dir() -> PathBuf {
    let mut result = dirs::config_dir().unwrap();
    result.push("norm");
    result
}

fn path() -> PathBuf {
    let mut result = dir();
    result.push("normalizer.conf");
    result
}

pub fn save() {
    let _ = fs::create_dir_all(dir());
    let config = serde_json::to_string(&(*CONFIG)).unwrap();
    let _ = fs::write(path(), config);
}

pub fn save_window(window: &winit::window::Window) {
    CONFIG.lock().unwrap().window = Some(Window {
        x: window.outer_position().unwrap().x,
        y: window.outer_position().unwrap().y,
        width: window.inner_size().width,
        height: window.inner_size().height,
    });

    save();
}

pub fn restore_window(window: &mut winit::window::Window) {
    if let Some(w) = &CONFIG.lock().unwrap().window {
        window.set_outer_position(winit::dpi::PhysicalPosition::new(w.x, w.y));
        window.set_inner_size(winit::dpi::PhysicalSize::new(w.width, w.height));
    }
}

impl Config {
    pub fn new() -> Self {
        let config_path = path();

        if config_path.exists() {
            let config_text = fs::read_to_string(config_path).unwrap();
            let config = serde_json::from_slice::<Config>(config_text.as_bytes());

            if let Ok(config) = config {
                return config;
            }
        }

        Self { window: None }
    }
}

impl Default for Config {
    fn default() -> Self {
        Self::new()
    }
}
