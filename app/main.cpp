#include <core/Application.h>
#include <ui/MainWindow.h>
#include <settings/FileSettings.h>
#include <QLoggingCategory>
#include <QVulkanInstance>

int main(int argc, char* argv[]) {
    Application app(argc, argv);

    FileSettings settings;

    QLoggingCategory::setFilterRules("qt.vulkan=true");

    QVulkanInstance instance;
    instance.setLayers({ "VK_LAYER_KHRONOS_validation" });
    instance.setApiVersion(QVersionNumber(1, 4));

    if (!instance.create()) {
        qFatal("Failed to create Vulkan instance: %d", instance.errorCode());
    }

    MainWindow mainWindow(&settings);
    mainWindow.show();

    return app.exec();
}
