#include <QCommandLineParser>
#include <QTextStream>
#include <QFile>
int main(int argc, char *argv[])
{
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

    QString filePath = parser.value(optInput);
    cout << "Try to open file " << filePath << "\n" << Qt::flush;
    QFile file(filePath);
    int res = file.open(QIODevice::ReadOnly|QIODevice::Text);
    cout << (res ? "OK\n" : "ERROR...\n") << Qt::flush;
    return res;
}
