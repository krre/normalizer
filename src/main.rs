use antiq::entity::Application;
use antiq::widget::ApplicationWindow;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let app = Application::new();

    let mut app_window = ApplicationWindow::new(&app)?;
    app_window.set_title("Normalizer");

    app.run()
}
