use super::renderer::{Renderer, SceneRenderer, UiRenderer};
use winit::{platform::unix::x11::util::VIRTUAL_CORE_POINTER, window::Window};
pub struct Engine {
    _instance: wgpu::Instance,
    surface: wgpu::Surface,
    adapter: wgpu::Adapter,
    device: wgpu::Device,
    queue: wgpu::Queue,
    renderers: Vec<Box<dyn Renderer>>,
}

impl Engine {
    pub async fn new(window: &Window) -> Self {
        let instance = wgpu::Instance::new(wgpu::Backends::all());
        let surface = unsafe { instance.create_surface(&window) };
        let adapter = instance
            .request_adapter(&wgpu::RequestAdapterOptions {
                power_preference: wgpu::PowerPreference::default(),
                force_fallback_adapter: false,
                compatible_surface: Some(&surface),
            })
            .await
            .expect("Failed to find an appropriate adapter");

        let (device, queue) = adapter
            .request_device(
                &wgpu::DeviceDescriptor {
                    label: None,
                    features: wgpu::Features::empty(),
                    // Make sure we use the texture resolution limits from the adapter, so we can support images the size of the swapchain.
                    limits: wgpu::Limits::downlevel_webgl2_defaults()
                        .using_resolution(adapter.limits()),
                },
                None,
            )
            .await
            .expect("Failed to create device");

        let swapchain_format = surface.get_preferred_format(&adapter).unwrap();
        let renderers: Vec<Box<dyn Renderer>> = vec![
            Box::new(SceneRenderer::new(&device, &swapchain_format)),
            Box::new(UiRenderer::new()),
        ];

        Self {
            _instance: instance,
            surface,
            adapter,
            device,
            queue,
            renderers,
        }
    }

    pub fn resize(&self, width: u32, height: u32) {
        let swapchain_format = self.surface.get_preferred_format(&self.adapter).unwrap();

        let config = wgpu::SurfaceConfiguration {
            usage: wgpu::TextureUsages::RENDER_ATTACHMENT,
            format: swapchain_format,
            width,
            height,
            present_mode: wgpu::PresentMode::Mailbox,
        };

        self.surface.configure(&self.device, &config);
    }

    pub fn render(&self) {
        println!("render");

        let frame = self
            .surface
            .get_current_texture()
            .expect("Failed to acquire next swap chain texture");
        let view = frame
            .texture
            .create_view(&wgpu::TextureViewDescriptor::default());
        let mut encoder = self
            .device
            .create_command_encoder(&wgpu::CommandEncoderDescriptor { label: None });

        for renderer in self.renderers.iter() {
            if renderer.is_dirty() {
                renderer.draw(&mut encoder, &view);
            }
        }

        self.queue.submit(Some(encoder.finish()));
        frame.present();
    }
}
