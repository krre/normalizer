use antiq::core::Application;
use normalizer::app::AppWindow;

fn main() -> Result<(), Box<dyn std::error::Error + Send + Sync>> {
    let mut app = Application::new();
    let app_window = AppWindow::new(&mut app);
    app.run();
    app_window.finish();
    Ok(())
}
