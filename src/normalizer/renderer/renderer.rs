use std::{cell::RefCell, rc::Rc};

use wgpu::{Adapter, Device, Instance, Queue, Surface};
use winit::dpi::PhysicalSize;

use crate::{core::Window, style::BACKGROUND_COLOR};

pub struct Renderer {
    #[allow(dead_code)]
    instance: Instance,
    #[allow(dead_code)]
    adapter: Adapter,
    device: Device,
    queue: Queue,
    surface: Surface<'static>,
    surface_config: wgpu::SurfaceConfiguration,
}

impl Renderer {
    pub fn new(window: Rc<RefCell<Window>>) -> Self {
        let instance = wgpu::Instance::default();
        // FIXME: Founded adapter may not match the window surface. Better use instance.request_adapter() with appropriate surface.
        let adapter = Self::find_adapter(&instance);

        println!("Graphics adapter: {}", adapter.get_info().name);

        let device_descriptor = wgpu::DeviceDescriptor::default();
        let (device, queue) =
            pollster::block_on(adapter.request_device(&device_descriptor, None)).unwrap();

        let surface = instance.create_surface(window.borrow().inner()).unwrap();

        let surface_config = surface
            .get_default_config(&adapter, window.borrow().width(), window.borrow().height())
            .expect("Surface isn't supported by the adapter.");

        surface.configure(&device, &surface_config);

        Self {
            instance,
            adapter,
            device,
            queue,
            surface,
            surface_config,
        }
    }

    fn find_adapter(instance: &Instance) -> Adapter {
        for adapter in instance.enumerate_adapters(wgpu::Backends::all()) {
            if adapter.get_info().device_type == wgpu::DeviceType::DiscreteGpu {
                return adapter;
            }
        }

        let adapter_options = wgpu::RequestAdapterOptions {
            ..Default::default()
        };

        return pollster::block_on(instance.request_adapter(&adapter_options)).unwrap();
    }

    pub fn resize_surface(&mut self, size: PhysicalSize<u32>) {
        self.surface_config.width = size.width.max(1);
        self.surface_config.height = size.height.max(1);
        self.surface.configure(&self.device, &self.surface_config);
    }

    pub fn render(&self) {
        let surface_texture = self.surface.get_current_texture().unwrap();
        let texture_view = surface_texture
            .texture
            .create_view(&wgpu::TextureViewDescriptor::default());
        self.clear_view(&texture_view, &BACKGROUND_COLOR);
        surface_texture.present();
    }

    fn clear_view(&self, view: &wgpu::TextureView, color: &wgpu::Color) {
        let mut encoder = self
            .device
            .create_command_encoder(&wgpu::CommandEncoderDescriptor { label: None });
        {
            let _rpass = encoder.begin_render_pass(&wgpu::RenderPassDescriptor {
                label: None,
                color_attachments: &[Some(wgpu::RenderPassColorAttachment {
                    view: &view,
                    resolve_target: None,
                    ops: wgpu::Operations {
                        load: wgpu::LoadOp::Clear(*color),
                        store: wgpu::StoreOp::Store,
                    },
                })],
                depth_stencil_attachment: None,
                timestamp_writes: None,
                occlusion_query_set: None,
            });
        }

        self.queue.submit(Some(encoder.finish()));
    }
}
