#include <filesystem>
#include <thread>
#include "Evolution.hpp"
#include "evoConfig.hpp"
#include "Args.hpp"
#include "ThreadWorker.hpp"

namespace fs = std::filesystem;

int main(int argc, char * argv[]) {

    evoConfig config;
    Args args;

    if (!args.parseArgs(argc, argv, config)) {
        return EXIT_FAILURE;
    }

    FastPRNG::seed();
    std::shared_ptr<ThreadFile> thrFile = std::make_shared<ThreadFile>(config.outFile);
    std::vector<ThreadWorker> threadWorkers;
    std::vector<std::thread> threads;
    std::vector<std::string> instances;
    fs::path instancesDir = fs::path(config.instancesDir);

    for (const auto &dirEntry: fs::recursive_directory_iterator(instancesDir)) {
        if (!dirEntry.is_directory()
            && dirEntry.path().extension() == ".mwcnf") {
            instances.emplace_back(dirEntry.path());
        }
    }

    for (unsigned long i = 0; i < config.threads; i++) {
        unsigned long start = i * (instances.size()/config.threads);
        unsigned long end = (i+1) * (instances.size()/config.threads);
        if (i+1 == config.threads) {
            end = instances.size();
        }
        threadWorkers.emplace_back(config, thrFile, instances, start, end);
    }

    for (auto &it: threadWorkers) {
        threads.emplace_back(&ThreadWorker::solve, &it);
    }

    for (auto &it: threads) {
        it.join();
    }

    return EXIT_SUCCESS;
}
