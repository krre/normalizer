use antiq::core::Application;

fn main() {
    let mut app = Application::new();

    let window = app.create_window();
    window.set_title("Normalizer");

    app.run();
}
