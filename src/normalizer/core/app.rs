use crate::core::config;
use crate::gfx::engine::Engine;
use winit::{
    event::{Event, WindowEvent},
    event_loop::{ControlFlow, EventLoop},
    window::{Window, WindowBuilder},
};

pub struct App {
    event_loop: EventLoop<()>,
    window: Window,
    gfx_engine: Engine,
}

impl App {
    pub async fn new() -> Result<Self, Box<dyn std::error::Error>> {
        let event_loop = EventLoop::new();
        let mut window = WindowBuilder::new()
            .with_title("Normalizer")
            .with_visible(false)
            .build(&event_loop)?;
        config::restore_window(&mut window);
        let gfx_engine = Engine::new(&window).await;

        Ok(Self {
            event_loop,
            window,
            gfx_engine,
        })
    }

    pub fn run(self) {
        self.event_loop.run(move |event, _, control_flow| {
            *control_flow = ControlFlow::Wait;

            match event {
                Event::WindowEvent {
                    event: WindowEvent::CloseRequested,
                    window_id,
                } if window_id == self.window.id() => {
                    config::save_window(&self.window);
                    *control_flow = ControlFlow::Exit
                }
                Event::WindowEvent {
                    event: WindowEvent::Resized(size),
                    ..
                } => {
                    self.gfx_engine.resize(size.width, size.height);
                    self.window.set_visible(true);
                }
                Event::RedrawRequested(_) => {
                    self.gfx_engine.render();
                }
                _ => (),
            }
        });
    }
}
