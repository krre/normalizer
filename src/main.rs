use antiq::core::Application;
use normalizer::app::AppWindow;

fn main() -> Result<(), Box<dyn std::error::Error + Send + Sync>> {
    let app = Application::new();
    let _ = AppWindow::new(&app);
    app.run();
    Ok(())
}
