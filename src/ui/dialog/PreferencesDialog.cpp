#include "PreferencesDialog.h"
#include "ui/widget/BrowseLayout.h"
#include "external/settings/Settings.h"
#include "core/Utils.h"
#include <QtWidgets>

PreferencesDialog::PreferencesDialog(Settings* settings, QWidget* parent) : StandardDialog(parent), m_settings(settings) {
    setWindowTitle(tr("Preferences"));

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(createProjectLocationGroupBox());
    verticalLayout->addWidget(createNormLocationGroupBox());

    setContentLayout(verticalLayout);
    resizeToWidth(600);
    m_workspaceBrowseLayout->setFocus();
}

void PreferencesDialog::accept() {
    Settings::ProjectLocation projectLocation;
    projectLocation.workspace = m_workspaceBrowseLayout->text();
    projectLocation.host = m_hostLineEdit->text();

    m_settings->setProjectLocation(projectLocation);

    Settings::NormLocation normLocation;
    normLocation.type = m_homeRadioButton->isChecked() ? Settings::NormLocation::Type::Home : Settings::NormLocation::Type::Custom;
    normLocation.directory = m_customBrowseLayout->text();

    m_settings->setNormLocation(normLocation);

    StandardDialog::accept();
}

QGroupBox* PreferencesDialog::createProjectLocationGroupBox() {
    m_workspaceBrowseLayout = new BrowseLayout(m_settings->projectLocation().workspace);
    m_hostLineEdit = new QLineEdit(m_settings->projectLocation().host);

    auto layout = new QFormLayout;
    layout->addRow(tr("Local workspace:"), m_workspaceBrowseLayout);
    layout->addRow(tr("Remote host:"), m_hostLineEdit);

    auto groupBox = new QGroupBox(tr("Project Location"));
    groupBox->setLayout(layout);
    return groupBox;
}

QGroupBox* PreferencesDialog::createNormLocationGroupBox() {
    m_homeRadioButton = new QRadioButton("NORM_HOME");
    m_directoryRadioButton = new QRadioButton(tr("Directory"));

    m_homeLineEdit = new QLineEdit(Utils::normHome());
    m_homeLineEdit->setReadOnly(true);

    m_customBrowseLayout = new BrowseLayout(m_settings->normLocation().directory);

    auto clickedHandler = [=, this] {
        m_homeLineEdit->setEnabled(m_homeRadioButton->isChecked());
        m_customBrowseLayout->setWidgetsEnabled(m_directoryRadioButton->isChecked());
    };

    connect(m_homeRadioButton, &QRadioButton::toggled, clickedHandler);
    connect(m_directoryRadioButton, &QRadioButton::toggled, clickedHandler);

    if (m_settings->normLocation().type == Settings::NormLocation::Type::Home) {
        m_homeRadioButton->setChecked(true);
    } else {
        m_directoryRadioButton->setChecked(true);
    }

    auto layout = new QGridLayout;
    layout->addWidget(m_homeRadioButton, 0, 0);
    layout->addWidget(m_homeLineEdit, 0, 1);
    layout->addWidget(m_directoryRadioButton, 1, 0);
    layout->addLayout(m_customBrowseLayout, 1, 1);

    auto groupBox = new QGroupBox(tr("Norm Location"));
    groupBox->setLayout(layout);
    return groupBox;
}
