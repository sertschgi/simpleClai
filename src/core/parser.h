#include <QCommandLineParser>

namespace clparser
{
    void parseArgs
        (
        const QCoreApplication& app
        );

    void _checkRequiredOptions
        (
        const QCommandLineParser& parser
        );
}

