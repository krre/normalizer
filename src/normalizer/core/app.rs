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
        let window = WindowBuilder::new()
            .with_title("Normalizer")
            .build(&event_loop)?;
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
                } if window_id == self.window.id() => *control_flow = ControlFlow::Exit,
                _ => (),
            }
        });
    }
}
