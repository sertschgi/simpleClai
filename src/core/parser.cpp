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

        parser.parse(app.arguments());

        args = parser.positionalArguments();
        command = args.isEmpty() ? QString() : args[1];

        if (command == "dataset")
        {
            parser.clearPositionalArguments();
            parser.addPositionalArgument("dataset", "Create a dataset.", "create dataset ...");

            QCommandLineOption datasetNameOption({"n", "name"}, "Specify the name of your dataset.", "name");
            QCommandLineOption datasetLabelOption({"l", "labels"}, "Specify the path of your labelmap.pbtxt", "labels");
            QCommandLineOption datsetLabelPathOption({"a", "labels_path"}, "Specify the label path.", "label_path");
            QCommandLineOption datasetImagePathOption({"m", "images_path"}, "Specify the images path.", "image_path");

            QList<QCommandLineOption> optionsList;
            optionsList << datasetNameOption << datasetLabelOption << datsetLabelPathOption << datasetImagePathOption;

            parser.addOptions(optionsList);

            parser.process(app);

            clparser::_checkRequiredOptions(parser, optionsList);

            qInfo() << "\033[32m[INFO]: Creating dataset..." << "\033[0m";

            try
            {
            dataset::createDataset
                (
                parser.value(datasetNameOption),
                parser.value(datasetLabelOption),
                parser.value(datasetImagePathOption),
                parser.value(datsetLabelPathOption)
                );
            }
            catch (const dataset::DatasetError& Error)
            {
            qFatal() << Error.what();
            }
        }

        else if (command == "profile")
        {
            parser.clearPositionalArguments();
            parser.addPositionalArgument("profile", "Create a profile.", "create profile ...");

            QCommandLineOption profileNameOption({"n", "name"}, "Specify the name of your profile.", "name");
            QCommandLineOption profileFrameworkOption({"f", "framework"}, "Specify the framework you want to use.", "framework");
            QCommandLineOption profileScopeOption({"s", "scope"}, "Specify which field of machine lerning you want to use.", "scope");

            QList<QCommandLineOption> optionsList;
            optionsList << profileNameOption << profileFrameworkOption << profileScopeOption;

            parser.addOptions(optionsList);

            parser.process(app.arguments());

            clparser::_checkRequiredOptions(parser, optionsList);

            qInfo() << "[INFO]: Creating profile...";

            try
            {
            profile::createProfile
                (
                parser.value(profileNameOption),
                parser.value(profileFrameworkOption),
                parser.value(profileScopeOption)
                );
            }
            catch (std::exception Error)
            {
            qFatal() << "\033[31m" << Error.what() << "\033[0m";
            }
        }

        else if (command == "project")
        {
            parser.clearPositionalArguments();
            parser.addPositionalArgument("project", "Create a project.", "create project ...");

            QCommandLineOption projectNameOption({"n", "name"}, "Specify the name of your project.", "name");
            QCommandLineOption projectProfileOption({"p", "profile"}, "Specify the profile you want to use for your project.", "profile");
            QCommandLineOption projectDatasetOption({"d", "dataset"}, "Specify the dataset you want to use.", "dataset");

            QList<QCommandLineOption> optionsList;
            optionsList << projectNameOption << projectProfileOption << projectDatasetOption;

            parser.addOptions(optionsList);

            parser.process(app.arguments());

            clparser::_checkRequiredOptions(parser, optionsList);

            qInfo() << "[INFO]: Creating project...";

            try
            {
            project::createProject
                (
                parser.value(projectNameOption),
                parser.value(projectProfileOption),
                parser.value(projectDatasetOption)
                );
            }
            catch (std::exception Error)
            {
                qFatal() << "\033[31m" << Error.what() << "\033[0m";
            }

        }

        else if (command == "model")
        {
            parser.clearPositionalArguments();
            parser.addPositionalArgument("model", "Create a model.", "create model ...");

            QCommandLineOption modelNameOption({"n", "name"}, "Specify the name of your model.", "name");
            QCommandLineOption modelProjectOption({"p", "project"}, "Specify the project you want to use for your model.", "project");
            QCommandLineOption modelModelOption({"m", "model"}, "Specify the model you want to use.", "model");

            QList<QCommandLineOption> optionsList;
            optionsList << modelNameOption << modelProjectOption << modelModelOption;

            parser.addOptions(optionsList);

            parser.process(app.arguments());

            clparser::_checkRequiredOptions(parser, optionsList);

            qInfo() << "[INFO]: Creating model...";

            try
            {
            model::createModel
                (
                parser.value(modelNameOption),
                parser.value(modelProjectOption),
                parser.value(modelModelOption)
                );
            }
            catch (std::exception Error)
            {
                qFatal() << "\033[31m" << Error.what() << "\033[0m";
            }

        }

        else
        {
            parser.process(app);
            parser.showHelp(1);
        }
    }

    else if (command == "train")
    {
        parser.clearPositionalArguments();
        parser.addPositionalArgument("train", "Train your model.", "train ...");

        QCommandLineOption trainModelOption({"m", "model"}, "Specify the name of the model.", "name");
        QCommandLineOption trainProjectOption({"p", "project"}, "Specify the name of the project.", "project");

        QList<QCommandLineOption> optionsList;
        optionsList << trainModelOption << trainProjectOption;

        parser.addOptions(optionsList);

        parser.process(app.arguments());

        clparser::_checkRequiredOptions(parser, optionsList);

        qInfo() << "[INFO]: Initializing training...";

        try
        {
        model::trainModel
            (
            parser.value(trainModelOption),
            parser.value(trainProjectOption)
            );
        }
        catch (std::exception Error)
        {
            qFatal() << "\033[31m" << Error.what() << "\033[0m";
        }
    }

    else if (command == "list")
    {
        parser.clearPositionalArguments();
        parser.addPositionalArgument("list", "List your projects, profiles or datasets.", "list [...]");

        QCommandLineOption listDatasetsOption({"d", "datasets"}, "List the datasets.");
        QCommandLineOption listProfilesOption({"f", "profiles"}, "List the profiles.");
        QCommandLineOption listProjectsOption({"p", "projects"}, "List the projects.");

        QList<QCommandLineOption> optionsList;
        optionsList << listDatasetsOption << listProfilesOption << listProjectsOption;

        parser.addOptions(optionsList);

        parser.process(app.arguments());

        if (parser.isSet(listDatasetsOption))
        {
            dataset::list();
        }
        else if (parser.isSet(listProfilesOption))
        {
            profile::list();
        }
        else
        {
            project::list();
        }
    }

    else
    {
        parser.process(app);
        parser.showHelp(1);
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
            qCritical() << "\033[33m[ERROR] <CRITICAL>: Option Required!\033[0m";
            parser.showHelp(1);
        }
    }
}
