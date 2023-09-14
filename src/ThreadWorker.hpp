#ifndef GENALGO_THREADWORKER_HPP
#define GENALGO_THREADWORKER_HPP

#include <thread>
#include <filesystem>
#include <fstream>
#include <vector>
#include "evoConfig.hpp"
#include "ThreadFile.hpp"
#include "Instance.hpp"

namespace fs = std::filesystem;

class ThreadWorker {

public:
    ThreadWorker(evoConfig &config, std::shared_ptr<ThreadFile> resFile, const std::vector<std::string> &instances,
                 unsigned long start, unsigned long end);
    void solve();
    void solveOne(const std::string &inFile);
    void doEstimation(Instance &instance);

private:
    struct Estimation {
        int population;
        int generations;
        int tournament;
        double mutation;
    };

    std::vector<std::string> m_instances;
    evoConfig& m_config;
    std::shared_ptr<ThreadFile> m_resultFile;
    unsigned long m_start;
    unsigned long m_end;
    void fillAlgoConfig(Estimation& estimation);
};


#endif //GENALGO_THREADWORKER_HPP
