use antiq::entity::Application;
use antiq::widget::ApplicationWindow;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut app = Application::new();

    let mut app_window = ApplicationWindow::new(&mut app)?;
    app_window.set_title("Normalizer");
    app_window.set_visible(true);

    app.add_window(app_window);

    app.run()
}
