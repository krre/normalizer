use antiq::core::Application;
use normalizer::app::AppWindow;

fn main() {
    let mut app = Application::new();
    AppWindow::new(&mut app);
    app.run();
}
