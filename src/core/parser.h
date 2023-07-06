#include <QCommandLineParser>

namespace clparser
{
    void parseArgs
        (
        const QCoreApplication& app
        );

    void _checkRequiredOptions
        (
        QCommandLineParser& parser,
        QList<QCommandLineOption>& optionsList
        );
}

