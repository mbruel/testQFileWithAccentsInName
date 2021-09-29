#include <QCoreApplication>
#include <QCommandLineParser>
#include <iostream>
#include <QTextStream>
#include <QFile>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const QString optInput = "input";
    const QList<QCommandLineOption> sCmdOptions = {
        {{"i", optInput}, "input file to upload (single file or directory), you can use it multiple times", optInput}
    };
    QCommandLineParser parser;
    parser.setApplicationDescription("testQFileWithAccentsInName");
    parser.addOptions(sCmdOptions);

    // Process the actual command line arguments given by the user
    QStringList args;
    for (int i = 0; i < argc; ++i)
        args << argv[i];

    QTextStream cout(stdout);
    if (!parser.parse(args) || !parser.isSet(optInput))
    {
        cout << QString("Error syntax... it should be: testQFileWithAccentsInName -i <path_to_file>\n");
        return 1;
    }

    std::cout << "argv[2] using stdio: " << argv[2] << "\n";
    cout << "argv[2] using QTextStream: " << argv[2] << "\n";

    QString filePath = parser.value(optInput);
    cout << "Try to open file " << filePath << "\n" << Qt::flush;
    QFile file(filePath);
    int res = file.open(QIODevice::ReadOnly|QIODevice::Text);
    cout << (res ? QString("OK\n")
                 : QString("ERROR #%1: %2...\n").arg(file.error()).arg(file.errorString()))
         << Qt::flush;

    filePath = argv[2];
    cout << "Try to open file2 " << filePath << "\n" << Qt::flush;
    QFile file2(filePath);
    res = file.open(QIODevice::ReadOnly|QIODevice::Text);
    cout << (res ? QString("OK\n")
                 : QString("ERROR #%1: %2...\n").arg(file.error()).arg(file.errorString()))
         << Qt::flush;


    return res ? 0 : 1;
}
