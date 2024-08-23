use std::error::Error;

use normalizer::core::Application;

fn main() -> Result<(), Box<dyn Error>> {
    let mut app = Application::new();
    app.run()?;
    Ok(())
}
