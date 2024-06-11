#include "ui/MainWindow.h"
#include "ui/editor/3d/VulkanWindow.h"
#include "core/Application.h"
#include <QVulkanInstance>

int main(int argc, char* argv[]) {
    // Hack to fix styling with Qt 6.5 on GTK3
    qunsetenv("GNOME_DESKTOP_SESSION_ID");
    qunsetenv("XDG_CURRENT_DESKTOP");

    Application app(argc, argv);

    QVulkanInstance instance;

    if (!instance.create()) {
        qFatal("Failed to create Vulkan instance: %d", instance.errorCode());
    }

    MainWindow mainWindow(new VulkanWindow(&instance));
    mainWindow.show();

    return app.exec();
}
