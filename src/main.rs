use std::cell::RefCell;

use antiq::core::Application;
use normalizer::app::AppWindow;

fn main() -> Result<(), Box<dyn std::error::Error + Send + Sync>> {
    env_logger::init();

    Application::set_organization("Norm");
    Application::set_name("Normalizer");

    let app = RefCell::new(Application::new());
    let app_window = AppWindow::new(app);
    app_window.run();
    Ok(())
}
