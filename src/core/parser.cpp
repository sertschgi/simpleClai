#include "parser.h"

#include "../commands/dataset.h"
#include "../commands/model.h"
#include "../commands/profile.h"
#include "../commands/project.h"
#include "../commands/frameworks.h"

#include "../utils/errors.h"

#include <QDebug>
#include <QCommandLineParser>
#include <QCoreApplication>

void checkRequiredOptions
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

void createDatasetCommand
    (
    QCommandLineParser& parser
    )
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

    parser.process(QCoreApplication::arguments());

    checkRequiredOptions(parser, optionsList);

    qInfo() << "\033[32m[INFO]: Creating dataset...\033[0m";

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
    catch (const error::GeneralError& Error)
    {
        qFatal() << Error.what();
    }
}

void createProfileCommand
    (
        QCommandLineParser& parser
        )
{
    parser.clearPositionalArguments();
    parser.addPositionalArgument("profile", "Create a profile.", "create profile ...");

    QCommandLineOption profileNameOption({"n", "name"}, "Specify the name of your profile.", "name");
    QCommandLineOption profileFrameworkOption({"f", "framework"}, "Specify the framework you want to use.", "framework");
    QCommandLineOption profileScopeOption({"s", "scope"}, "Specify which field of machine lerning you want to use.", "scope");

    QList<QCommandLineOption> optionsList;
    optionsList << profileNameOption << profileFrameworkOption << profileScopeOption;

    parser.addOptions(optionsList);

    parser.process(QCoreApplication::arguments());

    checkRequiredOptions(parser, optionsList);

    qInfo() << "\033[32m[INFO]: Creating profile...\033[0m";

    try
    {
        profile::createProfile
            (
            parser.value(profileNameOption),
            parser.value(profileFrameworkOption),
            parser.value(profileScopeOption)
            );
    }
    catch (const error::GeneralError& Error)
    {
        qFatal() << Error.what();
    }
}

void createProjectCommand
    (
        QCommandLineParser& parser
        )
{
    parser.clearPositionalArguments();
    parser.addPositionalArgument("project", "Create a project.", "create project ...");

    QCommandLineOption projectNameOption({"n", "name"}, "Specify the name of your project.", "name");
    QCommandLineOption projectProfileOption({"p", "profile"}, "Specify the profile you want to use for your project.", "profile");
    QCommandLineOption projectDatasetOption({"d", "dataset"}, "Specify the dataset you want to use.", "dataset");

    QList<QCommandLineOption> optionsList;
    optionsList << projectNameOption << projectProfileOption << projectDatasetOption;

    parser.addOptions(optionsList);

    parser.process(QCoreApplication::arguments());

    checkRequiredOptions(parser, optionsList);

    qInfo() << "\033[32m[INFO]: Creating project...\033[0m";

    try
    {
        project::createProject
            (
            parser.value(projectNameOption),
            parser.value(projectProfileOption),
            parser.value(projectDatasetOption)
            );
    }
    catch (const error::GeneralError& Error)
    {
        qFatal() << Error.what();
    }
}

void createModelCommand
    (
        QCommandLineParser& parser
        )
{
    parser.clearPositionalArguments();
    parser.addPositionalArgument("model", "Create a model.", "create model ...");

    QCommandLineOption modelNameOption({"n", "name"}, "Specify the name of your model.", "name");
    QCommandLineOption modelProjectOption({"p", "project"}, "Specify the project you want to use for your model.", "project");
    QCommandLineOption modelModelOption({"m", "model"}, "Specify the model you want to use.", "model");

    QList<QCommandLineOption> optionsList;
    optionsList << modelNameOption << modelProjectOption << modelModelOption;

    parser.addOptions(optionsList);

    parser.process(QCoreApplication::arguments());


    checkRequiredOptions(parser, optionsList);

    qInfo() << "\033[32m[INFO]: Creating model...\033[0m";

    try
    {
        model::createModel
            (
            parser.value(modelNameOption),
            parser.value(modelProjectOption),
            parser.value(modelModelOption)
            );
    }
    catch (const error::GeneralError& Error)
    {
        qFatal() << Error.what();
    }
}

void createCommand
    (
        QCommandLineParser& parser
        )
{
    parser.clearPositionalArguments();
    parser.addPositionalArgument("create", "Create a project, profile, dataset or model.", "create ...");

    parser.parse(QCoreApplication::arguments());

    QStringList args = parser.positionalArguments();
    QString command = args.isEmpty() ? QString() : args[1];

    if (command == "dataset")
    {
        createDatasetCommand(parser);
    }

    else if (command == "profile")
    {
        createProfileCommand(parser);
    }

    else if (command == "project")
    {
        createProjectCommand(parser);
    }

    else if (command == "model")
    {
        createModelCommand(parser);
    }

    else
    {
        parser.process(QCoreApplication::arguments());
        parser.showHelp(1);
    }
}

void trainCommand
    (
    QCommandLineParser& parser
    )
{
    parser.clearPositionalArguments();
    parser.addPositionalArgument("train", "Train your model.", "train ...");

    QCommandLineOption trainModelOption({"m", "model"}, "Specify the name of the model.", "name");
    QCommandLineOption trainProjectOption({"p", "project"}, "Specify the name of the project.", "project");

    QList<QCommandLineOption> optionsList;
    optionsList << trainModelOption << trainProjectOption;

    parser.addOptions(optionsList);

    parser.process(QCoreApplication::arguments());

    checkRequiredOptions(parser, optionsList);

    qInfo() << "\033[32m[INFO]: Initializing training...\033[0m";

    try
    {
    model::trainModel
        (
        parser.value(trainModelOption),
        parser.value(trainProjectOption)
        );
    }
    catch (const error::GeneralError& Error)
    {
        qFatal() << Error.what();
    }
}

void listCommand
    (
    QCommandLineParser& parser
    )
{
    parser.clearPositionalArguments();
    parser.addPositionalArgument("list", "List your projects, profiles or datasets.", "list [...]");

    QCommandLineOption listDatasetsOption({"d", "datasets"}, "List the datasets.");
    QCommandLineOption listProfilesOption({"r", "profiles"}, "List the profiles.");
    QCommandLineOption listProjectsOption({"p", "projects"}, "List the projects.");
    QCommandLineOption listModelsOption({"m", "models"}, "List the models.", "framework, scope");
    QCommandLineOption listFrameworksOption({"f", "frameworks"}, "List the frameworks.");

    QList<QCommandLineOption> optionsList;
    optionsList << listDatasetsOption << listProfilesOption << listProjectsOption << listFrameworksOption << listModelsOption;

    parser.addOptions(optionsList);

    parser.process(QCoreApplication::arguments());

    if (parser.optionNames().size() == 0)
    {
        qInfo() << "\033[33m[ERROR] <CRITICAL>: No option specified.\033[0m";
        parser.showHelp(1);
    }

    QStringList args = parser.positionalArguments();

    if (parser.isSet(listDatasetsOption))
    {
        dataset::list();
    }

    if (parser.isSet(listProfilesOption))
    {
        profile::list();
    }

    if (parser.isSet(listProjectsOption))
    {
        project::list();
    }

    if (parser.isSet(listModelsOption))
    {
        if (!(args.size() > 3))
        {
            qCritical() << "\033[31mnot enough options!\nPositional argument\n   - 1: framework\n   - 2: scope\033[0m\n";
            parser.showHelp(1);
        }
        model::list(args[1], args[2]);
    }

    if (parser.isSet(listFrameworksOption))
    {
        frameworks::list();
    }
}

void deleteCommand
    (
    QCommandLineParser& parser
    )
{
    parser.clearPositionalArguments();
    parser.addPositionalArgument("delete", "Delete your projects, profiles, profiles or models", "delete [...]");

    QCommandLineOption deleteDatasetOption({"d", "dataset"}, "Delete a dataset.", "dataset");
    QCommandLineOption deleteProfilesOption({"r", "profile"}, "Delete a profile.", "profile");
    QCommandLineOption deleteProjectsOption({"p", "project"}, "Delete a project.", "project");
    QCommandLineOption deleteModelsOption({"m", "model"}, "Delete a model.", "model");
    QCommandLineOption confirmationOption({"y", "yes"}, "Continue without asking.");

    QList<QCommandLineOption> optionsList;
    optionsList << deleteDatasetOption << deleteProfilesOption << deleteProjectsOption << deleteModelsOption << confirmationOption;

    parser.addOptions(optionsList);

    parser.process(QCoreApplication::arguments());

    if (parser.optionNames().size() == 0)
    {
        qInfo() << "\033[33m[ERROR] <CRITICAL>: No option specified.\033[0m";
        parser.showHelp(1);
    }

    QStringList args = parser.positionalArguments();

    if (args[1].isEmpty())
    {
        qCritical() << "\033[31mnot enough arguments!\nPositional argument\n   - 1: name\033[0m\n";
        parser.showHelp(1);
    }

    const QString& name = args[1];

    bool confirmation = false;

    if (parser.isSet(confirmationOption))
    {
        confirmation = true;
    }

    if (parser.isSet(deleteDatasetOption))
    {
        dataset::deleteDataset(name, confirmation);
    }

    if (parser.isSet(deleteProfilesOption))
    {
        profile::deleteProfile(name, confirmation);
    }

    //if (parser.isSet(deleteProjectsOption))
    //{
    //    project::deleteProject(name, confirmation);
    //}

    if (parser.isSet(deleteModelsOption))
    {

        if (!(args.size() > 3))
        {
            qCritical() << "\033[31mnot enough options!\nPositional argument\n   - 1: name\n   - 2: project\033[0m\n";
            parser.showHelp(1);
        }
        model::deleteModel(name, args[2] ,confirmation);
    }

}

void clparser::parseArgs
    (
    )
{
    QCommandLineParser parser;
    parser.setApplicationDescription("SimpleClAi parser");
    parser.addHelpOption();

    parser.addVersionOption();

    parser.addPositionalArgument("command", "The command to execute.");

    parser.parse(QCoreApplication::arguments());

    QStringList args = parser.positionalArguments();
    QString command = args.isEmpty() ? QString() : args.first();

    if (command == "create")
    {
        createCommand(parser);
    }

    else if (command == "train")
    {
        trainCommand(parser);
    }

    else if (command == "list")
    {
        listCommand(parser);
    }

    else if (command == "delete")
    {
        deleteCommand(parser);
    }

    else
    {
        parser.process(QCoreApplication::arguments());
        parser.showHelp(1);
    }
}


