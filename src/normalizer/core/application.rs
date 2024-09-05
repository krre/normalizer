use std::error::Error;

use winit::application::ApplicationHandler;
use winit::event::WindowEvent;
use winit::event_loop::{ActiveEventLoop, ControlFlow, EventLoop};
use winit::window::{Window, WindowId};

use crate::renderer::Renderer;

use super::Preferences;

pub const NAME: &str = "Normalizer";
pub const ORGANIZATION: &str = "Norm";

pub struct Application {
    window: Option<Window>,
    preferences: Preferences,
    renderer: Renderer,
}

impl Application {
    pub fn new() -> Self {
        Self {
            window: None,
            preferences: Preferences::default(),
            renderer: Renderer::new(),
        }
    }

    pub fn run(&mut self) -> Result<(), Box<dyn Error>> {
        let event_loop = EventLoop::new()?;
        event_loop.set_control_flow(ControlFlow::Wait);
        event_loop.run_app(self)?;
        Ok(())
    }
}

impl Drop for Application {
    fn drop(&mut self) {
        self.preferences.save();
    }
}

impl ApplicationHandler for Application {
    fn resumed(&mut self, event_loop: &ActiveEventLoop) {
        let mut attrs = Window::default_attributes();

        if self.preferences.load() {
            if self.preferences.window.is_maximized {
                attrs = attrs.with_maximized(self.preferences.window.is_maximized);
            } else {
                attrs = attrs
                    .with_position(winit::dpi::PhysicalPosition::new(
                        self.preferences.window.x,
                        self.preferences.window.y,
                    ))
                    .with_inner_size(winit::dpi::PhysicalSize::new(
                        self.preferences.window.width,
                        self.preferences.window.height,
                    ));
            }
        }

        attrs = attrs.with_title(NAME.to_string());

        self.window = Some(event_loop.create_window(attrs).unwrap());
    }

    fn window_event(&mut self, event_loop: &ActiveEventLoop, _id: WindowId, event: WindowEvent) {
        let window = self.window.as_ref().unwrap();

        match event {
            WindowEvent::CloseRequested => {
                let pref_window = &mut self.preferences.window;
                pref_window.is_maximized = window.is_maximized();

                if !window.is_maximized() {
                    pref_window.width = window.inner_size().width;
                    pref_window.height = window.inner_size().height;

                    pref_window.x = window.outer_position().as_ref().unwrap().x;
                    pref_window.y = window.outer_position().as_ref().unwrap().y;
                }

                event_loop.exit();
            }
            WindowEvent::RedrawRequested => {
                window.request_redraw();
                self.renderer.render();
            }
            _ => (),
        }
    }
}
