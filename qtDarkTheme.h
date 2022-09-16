#include <QStyleFactory>

QPalette createDarkQPallette(){ // Returns a nice looking theme for the application
    QPalette palette;
    QColor darkGray(53, 53, 53);
    QColor gray(128, 128, 128);
    QColor black(25, 25, 25);
    QColor blue(42, 130, 218);
    palette.setColor(QPalette::Window, darkGray);
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Base, black);
    palette.setColor(QPalette::AlternateBase, darkGray);
    palette.setColor(QPalette::ToolTipBase, blue);
    palette.setColor(QPalette::ToolTipText, Qt::white);
    palette.setColor(QPalette::Text, Qt::white);
    palette.setColor(QPalette::Button, darkGray);
    palette.setColor(QPalette::ButtonText, Qt::white);
    palette.setColor(QPalette::Link, blue);
    palette.setColor(QPalette::Highlight, blue);
    palette.setColor(QPalette::HighlightedText, Qt::black);
    palette.setColor(QPalette::Active, QPalette::Button, gray.darker());
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, gray);
    palette.setColor(QPalette::Disabled, QPalette::WindowText, gray);
    palette.setColor(QPalette::Disabled, QPalette::Text, gray);
    palette.setColor(QPalette::Disabled, QPalette::Light, darkGray);
    return palette;
}