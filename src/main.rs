use normalizer::core::app::App;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let app = pollster::block_on(App::new())?;
    app.run();
    Ok(())
}
