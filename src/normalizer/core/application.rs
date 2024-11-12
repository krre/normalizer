use std::cell::RefCell;
use std::error::Error;
use std::rc::Rc;

use winit::application::ApplicationHandler;
use winit::event::WindowEvent;
use winit::event_loop::{ActiveEventLoop, ControlFlow, EventLoop};
use winit::keyboard::{Key, ModifiersState};

use crate::renderer::Renderer;

use super::{Preferences, Window};

pub const NAME: &str = "Normalizer";
pub const ORGANIZATION: &str = "Norm";

pub struct Application {
    window: Option<Rc<RefCell<Window>>>,
    preferences: Preferences,
    renderer: Option<Renderer>,
}

impl Application {
    pub fn new() -> Self {
        Self {
            window: None,
            preferences: Preferences::default(),
            renderer: None,
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
        let mut attrs = winit::window::Window::default_attributes();

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

        attrs = attrs.with_title(NAME.to_string()).with_visible(false);

        let winit_window = event_loop.create_window(attrs).unwrap();
        let window = Rc::new(RefCell::new(Window::new(winit_window)));
        self.renderer = Some(Renderer::new(window.clone()));
        self.renderer.as_mut().unwrap().render();
        window.borrow().set_visible(true);

        self.window = Some(window);
    }

    fn window_event(
        &mut self,
        event_loop: &ActiveEventLoop,
        _id: winit::window::WindowId,
        event: WindowEvent,
    ) {
        let window = self.window.as_mut().unwrap();

        match event {
            WindowEvent::ModifiersChanged(modifiers) => {
                window.borrow_mut().set_modifiers(modifiers.state());
            }

            WindowEvent::KeyboardInput {
                event,
                is_synthetic: false,
                ..
            } => {
                if event.state.is_pressed() {
                    if let Key::Character(ch) = event.logical_key.as_ref() {
                        if ch.to_uppercase() == "Q"
                            && window.borrow().modifiers() == &ModifiersState::CONTROL
                        {
                            event_loop.exit();
                        }
                    }
                }
            }

            WindowEvent::CloseRequested => {
                let pref_window = &mut self.preferences.window;
                pref_window.is_maximized = window.borrow().is_maximized();

                if !window.borrow().is_maximized() {
                    pref_window.width = window.borrow().width();
                    pref_window.height = window.borrow().height();

                    pref_window.x = window.borrow().x();
                    pref_window.y = window.borrow().y();
                }

                event_loop.exit();
            }

            WindowEvent::Resized(size) => {
                self.renderer.as_mut().unwrap().resize_surface(size);
            }

            WindowEvent::RedrawRequested => {
                window.borrow().redraw();
                self.renderer.as_mut().unwrap().render();
            }
            _ => (),
        }
    }
}
