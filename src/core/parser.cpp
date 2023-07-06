#include "parser.h"

#include "../commands/dataset.h"
#include "../commands/model.h"
#include "../commands/profile.h"
#include "../commands/project.h"

#include <QDebug>
#include <QCommandLineParser>
#include <QCoreApplication>

void clparser::parseArgs
    (
    const QCoreApplication& app
    )
{
    QCommandLineParser parser;
    parser.setApplicationDescription("SimpleClAi parser");
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addPositionalArgument("command", "The command to execute.");

    parser.parse(app.arguments());

    QStringList args = parser.positionalArguments();
    QString command = args.isEmpty() ? QString() : args.first();

    if (command == "create")
    {
        parser.clearPositionalArguments();
        parser.addPositionalArgument("create", "Create a project, profile, dataset or model.", "create ...");

        parser.parse(QCoreApplication::arguments());

        args = parser.positionalArguments();
        command = args.isEmpty() ? QString() : args[1];

        if (command == "dataset")
        {
            parser.clearPositionalArguments();
            parser.addPositionalArgument("dataset", "Create a dataset.", "create dataset ...");

            QCommandLineOption datasetNameOption({"n", "name"}, "Specify the name of your dataset.");
            QCommandLineOption datasetLabelOption({"l", "labels"}, "Specify the labels you use in your project.");
            QCommandLineOption datsetLabelPathOption({"lp", "labels_path"}, "Specify the label path.");
            QCommandLineOption datasetImagePathOption({"ip", "images_path"}, "Specify the images path.");

            QList<QCommandLineOption> optionsList;
            optionsList << datasetNameOption << datasetLabelOption << datsetLabelPathOption << datasetImagePathOption;

            parser.addOptions(optionsList);

            parser.process(app.arguments());

            clparser::_checkRequiredOptions(parser, optionsList);

            qInfo() << "Creating dataset...";

            dataset::createDataset
                (
                parser.value(datasetNameOption),
                parser.value(datasetImagePathOption),
                parser.value(datasetLabelOption),
                parser.value(datsetLabelPathOption)
                );
        }

        else if (command == "profile")
        {
            parser.clearPositionalArguments();
            parser.addPositionalArgument("profile", "Create a profile.", "create profile ...");

            QCommandLineOption profileNameOption({"n", "name"}, "Specify the name of your profile.");
            QCommandLineOption profileFrameworkOption({"f", "framework"}, "Specify the framework you want to use.");
            QCommandLineOption profileScopeOption({"s", "scope"}, "Specify which field of machine lerning you want to use.");

            QList<QCommandLineOption> optionsList;
            optionsList << profileNameOption << profileFrameworkOption << profileScopeOption;

            parser.addOptions(optionsList);

            parser.process(app.arguments());

            clparser::_checkRequiredOptions(parser, optionsList);

            qInfo() << "Creating profile...";

            profile::createProfile
                (
                parser.value(profileNameOption),
                parser.value(profileFrameworkOption),
                parser.value(profileScopeOption)
                );

        }

        else if (command == "project")
        {
            parser.clearPositionalArguments();
            parser.addPositionalArgument("project", "Create a project.", "create project ...");

            QCommandLineOption projectNameOption({"n", "name"}, "Specify the name of your project.");
            QCommandLineOption projectProfileOption({"p", "profile"}, "Specify the profile you want to use for your project.");
            QCommandLineOption projectDatasetOption({"d", "dataset"}, "Specify the dataset you want to use.");

            QList<QCommandLineOption> optionsList;
            optionsList << projectNameOption << projectProfileOption << projectDatasetOption;

            parser.addOptions(optionsList);

            parser.process(app.arguments());

            clparser::_checkRequiredOptions(parser, optionsList);

            qInfo() << "Creating project...";

            project::createProject
                (
                parser.value(projectNameOption),
                parser.value(projectProfileOption),
                parser.value(projectDatasetOption)
                );

        }

        else if (command == "model")
        {
            parser.clearPositionalArguments();
            parser.addPositionalArgument("model", "Create a model.", "create model ...");

            QCommandLineOption modelNameOption({"n", "name"}, "Specify the name of your model.");
            QCommandLineOption modelProjectOption({"p", "project"}, "Specify the project you want to use for your project.");
            QCommandLineOption modelModelOption({"m", "model"}, "Specify the model you want to use.");

            QList<QCommandLineOption> optionsList;
            optionsList << modelNameOption << modelProjectOption << modelModelOption;

            parser.addOptions(optionsList);

            parser.process(app.arguments());

            clparser::_checkRequiredOptions(parser, optionsList);

            qInfo() << "Creating model...";

            model::createModel
                (
                parser.value(modelNameOption),
                parser.value(modelProjectOption),
                parser.value(modelModelOption)
                );

        }

        else
        {
            parser.process(app);
        }
    }

    else if (command == "train")
    {
        parser.clearPositionalArguments();
        parser.addPositionalArgument("train", "Train your model.", "train ...");

        QCommandLineOption trainModelOption({"m", "model"}, "Specify the name of the model.");
        QCommandLineOption trainProjectOption({"p", "project"}, "Specify the name of the project.");

        QList<QCommandLineOption> optionsList;
        optionsList << trainModelOption << trainProjectOption;

        parser.addOptions(optionsList);

        parser.process(app.arguments());

        clparser::_checkRequiredOptions(parser, optionsList);

        qInfo() << "Initializing training...";

        model::trainModel
            (
            parser.value(trainModelOption),
            parser.value(trainProjectOption)
            );
    }

    else if (command == "list")
    {
        parser.clearPositionalArguments();
        parser.addPositionalArgument("list", "List your projects, profiles or datasets.", "list");

        // todo: add function call to list here.
    }

    else
    {
        parser.process(app);
    }
}

void clparser::_checkRequiredOptions
    (
    QCommandLineParser& parser,
    QList<QCommandLineOption>& optionsList
    )
{
    for (QCommandLineOption& option : optionsList)
    {
        if (!parser.isSet(option))
        {
            qInfo() << "Option Required!";
            parser.showHelp(1);
        }
    }
}
