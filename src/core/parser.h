#ifndef PARSER_H
#define PARSER_H

#include <QCommandLineParser>
#include <QCoreApplication>
#include <QList>

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

#endif PARSER_H
