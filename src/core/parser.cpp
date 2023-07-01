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

    QCommandLineOption nameOption({"name", "n"}, "Specify a name");

    // create command
    QCommandLineParser createParser;
    createParser.setApplicationDescription("Create profile, project or model");

    // create profile
    QCommandLineParser createProfileParser;
    createProfileParser.setApplicationDescription("Profile option");

    createProfileParser.addOption(nameOption);
    createProfileParser.addOption({{"framework", "f"}, "Specify the framework."});
    createProfileParser.addOption({{"scope", "s"}, "What you want to do with your framework."});

    createParser.addOption({{"profile", "pf"}, "Create Profile"});
    //createParser.addSubParser(&createProfileParser {"profile", "pf"});

    // create project
    QCommandLineParser createProjectParser;
    createProjectParser.setApplicationDescription("Project option");

    createProjectParser.addOption(nameOption);
    createProjectParser.addOption({{"profile", "p"}, "Specify a profile."});
    createProjectParser.addOption({{"dataset", "d"}, "Specify the dataset"});

    createParser.addOption({{"project", "pj"}, "Create Project"});
    //createParser.addSubParser(&createProjectParser {"project", "pj"});

    // create model
    QCommandLineParser createModelParser;
    createModelParser.setApplicationDescription("Model option");

    createProjectParser.addOption(nameOption);
    createProjectParser.addOption({{"project", "p"}, "Specify a project."});
    createProjectParser.addOption({{"model", "m"}, "Specify the model."});

    createParser.addOption({{"model", "m"}, "Create Model"});
    // createParser.addSubParser(&createModelParser {"model", "m"});

    // create dataset
    QCommandLineParser createDatasetParser;
    createModelParser.setApplicationDescription("Dataset option");

    createDatasetParser.addOption(nameOption);
    createDatasetParser.addOption({{"labels", "l"}, "Specify the labels."});
    createDatasetParser.addOption({{"labelpath", "lp"}, "Specify the label path."});
    createDatasetParser.addOption({{"imagepath", "i"}, "Specify the images path."});

    createParser.addOption({{"dataset", "d"}, "Create Dataset"});
    //createParser.addSubParser(&createProjectParser, {"dataset", "d"});

    parser.addOption({{"create", "c"}, "Create Command"});
    //parser.addSubParser(&createParser, {"create", "c"});

    // train command
    QCommandLineParser trainParser;
    trainParser.setApplicationDescription("Train your models");

    trainParser.addOption({{"modelname", "n"}, "Specify the name of the model."});
    trainParser.addOption({{"projectname", "n"}, "Specify the name of the project."});

    parser.addOption({{"train", "t"}, "Train Command"});
    //parser.addSubParser(&trainParser, {"train", "t"});

    // list command
    QCommandLineParser listParser;
    listParser.setApplicationDescription("List your datasets, profiles and projects");

    listParser.addOption({{"dataset", "d"}, "List your datasets"});
    listParser.addOption({{"profile", "pf"}, "List your profiles"});
    listParser.addOption({{"projects", "pj"}, "List your projects"});

    parser.addOption({{"list", "l"}, "List Command"});
    //parser.addSubParser(&listParser, {"list", "l"});

    // process the args
    parser.process(app);

    if (parser.isSet("create"))
    {
        createParser.process(app); // potential mistake: else use parser.value("create") instead of app
        if (createParser.isSet("profile"))
        {
            createProfileParser.process(app); // same as line 102
            clparser::_checkRequiredOptions(createParser);
            profile::createProfile
            (
                createProfileParser.value(nameOption),
                createProfileParser.value("scope"),
                createProfileParser.value("framework")
            );
        }
        else if (createParser.isSet("project"))
        {
            createProjectParser.process(app); // same as line 102
            clparser::_checkRequiredOptions(createParser);
            project::createProject
            (
                createProjectParser.value(nameOption),
                createProjectParser.value("profile"),
                createProjectParser.value("dataset")
            );
        }
        else if (createParser.isSet("model"))
        {
            createModelParser.process(app); // same as line 102
            clparser::_checkRequiredOptions(createParser);
            model::createModel
                (
                    createModelParser.value(nameOption),
                    createModelParser.value("project"),
                    createModelParser.value("model")
                );
        }
        else if (createParser.isSet("model"))
        {
            createDatasetParser.process(app); // same as line 102
            clparser::_checkRequiredOptions(createParser);
            dataset::createDataset
                (
                    createDatasetParser.value(nameOption),
                    createDatasetParser.value("imagepath"),
                    createDatasetParser.value("labels"),
                    createDatasetParser.value("labelpath")
                );
        }
    }

    else if (parser.isSet("train"))
    {
        trainParser.process(app); // same as line 102
        clparser::_checkRequiredOptions(trainParser);
        model::trainModel
        (
            trainParser.value("modelname"),
            trainParser.value("projectname")
        );
    }

    else if (parser.isSet("list"))
    {
        listParser.process(app); // same as line 102
        // todo: implement this:
        /** if (listParser.isSet("dataset"))
        {
            dataset::list();
        }
        else if (listParser.isSet("profile"))
        {
            profile::list();
        }
        else
        {
            project::list();
        } **/
        qDebug() << "listing will be implemented soon"; // remove this then
    }
}

void clparser::_checkRequiredOptions
    (
    const QCommandLineParser& parser
    )
{
    for (const QString& optionName : parser.optionNames())
    {
        if (!parser.isSet(optionName))
        {
            qCritical() << "Option Required!";
        }
    }
}
