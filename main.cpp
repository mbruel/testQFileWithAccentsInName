#include <QCoreApplication>
#include <iostream>
#include <cstdio>

#include <QCommandLineParser>
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

    QStringList args = QCoreApplication::arguments();
    QTextStream cout(stdout);
    if (!parser.parse(args) || !parser.isSet(optInput))
    {
        cout << QString("Error syntax... it should be: testQFileWithAccentsInName -i <path_to_file>\n");
        return 1;
    }

    std::cout << "argv[2] using stdio: " << argv[2] << "\n";
    cout << "argv[2] using QTextStream: " << argv[2] << "\n";

    QString filePath = parser.value(optInput);
    cout << "Try to open file using QCommandLineParser: " << filePath << "\n" << Qt::flush;
    QFile file(filePath);
    int res = file.open(QIODevice::ReadOnly|QIODevice::Text);
    cout << (res ? QString("OK\n")
                 : QString("ERROR #%1: %2...\n").arg(file.error()).arg(file.errorString()))
         << Qt::flush;
    if (res)
        file.close();

    filePath = args.at(2);
    cout << "\nTry to open file using directly QCoreApplication::arguments: " << filePath << "\n" << Qt::flush;
    QFile file2(filePath);
    res = file.open(QIODevice::ReadOnly|QIODevice::Text);
    cout << (res ? QString("OK\n")
                 : QString("ERROR #%1: %2...\n").arg(file.error()).arg(file.errorString()))
         << Qt::flush;

    FILE *cFile = fopen(argv[2], "r");
    cout << "\nTry to open cFile using fopen on argv[2]\n" << Qt::flush;
    cout << (cFile ? "OK\n" : "ERROR\n") << Qt::flush;
    if (cFile)
        fclose(cFile);

    return res ? 0 : 1;
}
