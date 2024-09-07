use std::sync::Arc;

use wgpu::{Adapter, Device, Instance, Queue, Surface};
use winit::dpi::PhysicalSize;

pub struct Renderer {
    instance: Instance,
    adapter: Adapter,
    device: Device,
    queue: Queue,
    surface: Surface<'static>,
    surface_config: wgpu::SurfaceConfiguration,
}

impl Renderer {
    pub fn new(window: Arc<winit::window::Window>) -> Self {
        let instance = wgpu::Instance::default();
        // FIXME: Founded adapter may not match the window surface. Better use instance.request_adapter() with appropriate surface.
        let adapter = Self::find_adapter(&instance);

        println!("Graphics adapter: {}", adapter.get_info().name);

        let device_descriptor = wgpu::DeviceDescriptor::default();
        let (device, queue) =
            pollster::block_on(adapter.request_device(&device_descriptor, None)).unwrap();

        let size = window.clone().inner_size();
        let surface = instance.create_surface(window).unwrap();

        let surface_config = surface
            .get_default_config(&adapter, size.width, size.height)
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

    pub fn render(&self) {}
}
