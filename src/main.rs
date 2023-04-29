use antiq::core::Application;
use normalizer::app::AppWindow;

fn main() -> Result<(), Box<dyn std::error::Error + Send + Sync>> {
    env_logger::init();

    Application::set_organization("Norm");
    Application::set_name("Normalizer");

    let mut app_window = AppWindow::new();
    app_window.run();

    Ok(())
}
