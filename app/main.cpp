#include <core/Application.h>
#include <ui/MainWindow.h>
#include <QLoggingCategory>
#include <QVulkanInstance>

int main(int argc, char* argv[]) {
    Application app(argc, argv);

    QLoggingCategory::setFilterRules("qt.vulkan=true");

    QVulkanInstance instance;
    instance.setLayers({ "VK_LAYER_KHRONOS_validation" });
    instance.setApiVersion(QVersionNumber(1, 4));

    if (!instance.create()) {
        qFatal("Failed to create Vulkan instance: %d", instance.errorCode());
    }

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
