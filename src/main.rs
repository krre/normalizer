use normalizer::core::app::App;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    env_logger::init();
    let app = pollster::block_on(App::new())?;
    app.run();
    Ok(())
}
