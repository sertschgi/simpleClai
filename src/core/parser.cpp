#include "parser.h"

#include "../commands/dataset.h"
#include "../commands/model.h"
#include "../commands/profile.h"
#include "../commands/project.h"
#include "../commands/frameworks.h"

// #include "../utils/errors.h"

#include <QDebug>
#include <QCoreApplication>

#include "clparser/Parser.hpp"


void clparser::parseArgs
    (
    int argc,
    char *argv[]
    )
{
    /*    ############################# CREATE COMMAND #############################    */

    // CREATE DATASET

    ClPosArg datasetNamePosArg("dataset-name", true);
    ClOption datasetNameOption(
        "dataset-name", { "n", "name" }, "Specify the name of your dataset.",
        { datasetNamePosArg }
        );

    ClPosArg datasetLabelPosArg("dataset-label", true);
    ClOption datasetLabelOption(
        "dataset-label", { "l", "labels" },
        "Specify the path of your labelmap.pbtxt", { datasetLabelPosArg }
        );

    ClPosArg datsetLabelPathPosArg("dataset-label-path", true);
    ClOption datsetLabelPathOption(
        "dataset-label-path", { "a", "labels_path" }, "Specify the label path.",
        { datsetLabelPathPosArg }
        );

    ClPosArg datasetImagePathPosArg("dataset-image-path", true);
    ClOption datasetImagePathOption(
        "dataset-image-path", { "m", "images_path" },
        "Specify the images path.", { datasetImagePathPosArg }
        );

    ClCommand createDatasetCommand(
        "dataset", { datasetNameOption, datasetLabelOption,
         datsetLabelPathOption, datasetImagePathOption }, "creates a dataset"
        );


    // CREATE PROFILE

    ClPosArg profileNamePosArg("profile-name", true);
    ClOption profileNameOption(
        "profile-name", { "n", "name" }, "Specify the name of your profile.",
        { profileNamePosArg }
        );

    ClPosArg profileFrameworkPosArg("profile-framework", true);
    ClOption profileFrameworkOption(
        "profile-framework", { "f", "framework" },
        "Specify the framework you want to use.", { profileFrameworkPosArg }
        );

    ClPosArg profileScopePosArg("profile-scope", true);
    ClOption profileScopeOption(
        "profile-scope", { "s", "scope" },
        "Specify which field of machine learning you want to use.", { profileScopePosArg }
        );

    ClCommand createProfileCommand(
        "profile",
        { profileNameOption, profileFrameworkOption, profileScopeOption },
        "creates a profile"
        );


    // CREATE PROJECT

    ClPosArg projectNamePosArg("project-name", true);
    ClOption projectNameOption(
        "project-name", { "n", "name" }, "Specify the name of your project.",
        { projectNamePosArg }
        );

    ClPosArg projectProfilePosArg("project-profile", true);
    ClOption projectProfileOption(
        "project-profile", { "p", "profile" },
        "Specify the profile you want to use for your project.", { projectProfilePosArg }
        );

    ClPosArg projectDatasetPosArg("project-dataset", true);
    ClOption projectDatasetOption(
        "project-dataset", { "d", "dataset" },
        "Specify the dataset you want to use.", { projectDatasetPosArg }
        );

    ClCommand createProjectCommand(
        "project",
        { projectNameOption, projectProfileOption, projectDatasetOption },
        "creates a project"
        );


    // CREATE MODEL

    ClPosArg modelNamePosArg("model-name", true);
    ClOption modelNameOption(
        "model-name", { "n", "name" }, "Specify the name of your model.",
        { modelNamePosArg }
        );

    ClPosArg modelProjectPosArg("model-project", true);
    ClOption modelProjectOption(
        "model-project", { "p", "project" },
        "Specify the project you want to use for your model.", { modelProjectPosArg }
        );

    ClPosArg modelModelPosArg("model-model", true);
    ClOption modelModelOption(
        "model-model", { "m", "model" }, "Specify the model you want to use.",
        { modelModelPosArg }
        );

    ClCommand createModelCommand(
        "model", { modelNameOption, modelProjectOption, modelModelOption },
        "creates a model"
        );


    // CREATE COMMAND

    ClCommandPtrList createCommands = { createDatasetCommand,
                                       createProfileCommand,
                                       createProjectCommand,
                                       createModelCommand };

    ClCommand createCommand("create", createCommands, "creates your stuff");


    /*    ############################# TRAIN COMMAND #############################    */

    ClPosArg trainProjectPosArg("train-project", true);
    ClOption trainProjectOption(
        "model-project", { "p", "project" },
        "Specify the project your model is located in.", { trainProjectPosArg }
        );

    ClPosArg trainModelPosArg("train-model", true);
    ClOption trainModelOption(
        "train-model", { "m", "model" }, "Specify the model you want to train.",
        { trainModelPosArg }
        );

    ClPosArg trainArgsPosArg("train-args");
    ClOption trainArgsOption(
        "train-model", { "a", "args" }, "Specify special arguments needed for your scope.",
        { trainArgsPosArg }
        );


    ClOptionPtrList trainOptions = { trainProjectOption, trainModelOption, trainArgsOption };
    ClCommand trainCommand("train", trainOptions, "trains your model");

    /*    ############################# LIST COMMAND #############################    */

    ClOption listDatasetsOption("list-framework", {"d", "datasets"}, "List the datasets.");

    ClOption listProfilesOption("list-profiles", {"r", "profiles"}, "List the profiles.");

    ClOption listProjectsOption("list-projects", {"p", "projects"}, "List the projects.");

    ClPosArg listScopePosArg("list-model-scope");
    ClPosArg listframeworkPosArg("list-model-framework");
    ClOption listModelsOption("list-models", {"s", "model-scope"}, "List the models of a scope (-f required).", { listScopePosArg });

    ClOption listFrameworksOption("list-framework", {"f", "frameworks"}, "List the frameworks.");

    ClOptionPtrList listOptions = {
        listDatasetsOption,
        listProfilesOption,
        listProjectsOption,
        listModelsOption,
        listFrameworksOption
    };
    ClCommand listCommand("list", listOptions, "lists stuff");


    /*    ############################# DELETE COMMAND #############################    */

    // DELETE DATASET

    ClCommand deleteDatasetCommand(
        "dataset", { datasetNameOption }, "deletes a dataset"
        );


    // DELETE PROFILE

    ClCommand deleteProfileCommand(
        "profile", { profileNameOption }, "deletes a profile"
        );


    // DELETE PROJECT

    ClCommand deleteProjectCommand(
        "project", { projectNameOption }, "deletes a project"
        );


    // DELETE MODEL

    ClCommand deleteModelCommand(
        "model", { modelNameOption, modelProjectOption }, "deletes a model"
        );


    ClOption confirmationOption("confirm", {"y", "yes"}, "Continue without asking.");

    ClCommandPtrList deleteCommands = {
        deleteDatasetCommand,
        deleteProfileCommand,
        deleteProjectCommand,
        deleteModelCommand
    };

    ClCommand deleteCommand("delete", { confirmationOption }, deleteCommands, "deletes stuff");


    /*    ############################# PARSER #############################    */

    ClParser parser({ createCommand, listCommand, trainCommand, deleteCommand });
    parser.addAppName("sclai");
    parser.addAppVersion("0.0.1");
    parser.addHelpOption();
    parser.addVersionOption();

    parser.parse(argc, argv);


    /*    ############################# CREATE HANDLING #############################    */

    // CREATE DATASET

    if (createDatasetCommand.isSet())
        dataset::createDataset(
            QString(datasetNamePosArg.cvalue()),
            QString(datasetLabelPosArg.cvalue()),
            QString(datsetLabelPathPosArg.cvalue()),
            QString(datasetImagePathPosArg.cvalue())
            );


    // CREATE PROFILE

    if (createProfileCommand.isSet())
        profile::createProfile(
            QString(profileNamePosArg.cvalue()),
            QString(profileFrameworkPosArg.cvalue()),
            QString(profileScopePosArg.cvalue())
            );


    // CREATE PROJECT

    if (createProjectCommand.isSet())
        project::createProject(
            QString(projectNamePosArg.cvalue()),
            QString(projectProfilePosArg.cvalue()),
            QString(projectDatasetPosArg.cvalue())
            );


    // CREATE MODEL

    if (createModelCommand.isSet())
        model::createModel(
            QString(modelNamePosArg.cvalue()),
            QString(modelProjectPosArg.cvalue()),
            QString(modelModelPosArg.cvalue())
            );


    /*    ############################# TRAIN HANDLING #############################    */

    if (trainCommand.isSet())
        model::trainModel(QString(trainModelPosArg.cvalue()), QString(trainProjectPosArg.cvalue()), QString(trainArgsPosArg.cvalue()));


    /*    ############################# LIST HANDLING #############################    */

    if (listDatasetsOption.isSet())
        dataset::list();

    if (listProfilesOption.isSet())
        profile::list();

    if (listProjectsOption.isSet())
        project::list();

    if (listModelsOption.isSet())
        model::list(QString(listScopePosArg.cvalue()), QString(listframeworkPosArg.cvalue()));

    if (listFrameworksOption.isSet())
        frameworks::list();


    /*    ############################# DELETION HANDLING #############################    */

    if (deleteDatasetCommand.isSet())
        dataset::deleteDataset(QString(datasetNamePosArg.cvalue()), confirmationOption.isSet());

    if (deleteProfileCommand.isSet())
        profile::deleteProfile(QString(profileNamePosArg.cvalue()), confirmationOption.isSet());

    if (deleteProjectCommand.isSet())
        project::deleteProject(QString(projectNamePosArg.cvalue()), confirmationOption.isSet());

    if (deleteModelCommand.isSet())
        model::deleteModel(QString(modelNamePosArg.cvalue()), QString(modelProjectPosArg.cvalue()), confirmationOption.isSet());


}


