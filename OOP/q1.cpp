#include <QApplication>
#include <QPushButton>

int q1(int argc, char* argv[])
{
    // 1. Create the application object (manages UI resources and event loop)
    QApplication app(argc, argv);

    // 2. Create a widget (a button is a widget)
    QPushButton button("Quit");

    // 3. Connect a user action (click) to a piece of code (app.quit)
    QObject::connect(&button, &QPushButton::clicked, &app, &QApplication::quit);

    // 4. Show the widget
    button.show();

    // 5. Enter the main event loop (waits for user interactions)
    return app.exec();
}