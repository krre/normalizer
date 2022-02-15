use super::Renderer;
use std::borrow::Cow;
use wgpu::{Device, RenderPipeline, TextureFormat};

pub struct SceneRenderer {
    render_pipeline: RenderPipeline,
}

impl SceneRenderer {
    pub fn new(device: &Device, swapchain_format: &TextureFormat) -> Self {
        let shader = device.create_shader_module(&wgpu::ShaderModuleDescriptor {
            label: None,
            source: wgpu::ShaderSource::Wgsl(Cow::Borrowed(include_str!("../shaders/shader.wgsl"))),
        });

        let pipeline_layout = device.create_pipeline_layout(&wgpu::PipelineLayoutDescriptor {
            label: None,
            bind_group_layouts: &[],
            push_constant_ranges: &[],
        });

        let render_pipeline = device.create_render_pipeline(&wgpu::RenderPipelineDescriptor {
            label: None,
            layout: Some(&pipeline_layout),
            vertex: wgpu::VertexState {
                module: &shader,
                entry_point: "vs_main",
                buffers: &[],
            },
            fragment: Some(wgpu::FragmentState {
                module: &shader,
                entry_point: "fs_main",
                targets: &[(*swapchain_format).into()],
            }),
            primitive: wgpu::PrimitiveState::default(),
            depth_stencil: None,
            multisample: wgpu::MultisampleState::default(),
            multiview: None,
        });

        Self { render_pipeline }
    }
}

impl Renderer for SceneRenderer {
    fn draw(&self) {
        println!("SceneRenderer draw")
    }

    fn render(&self) {
        println!("SceneRenderer render")
    }

    fn is_dirty(&self) -> bool {
        return false;
    }
}
