#ifndef GENALGO_ARGS_HPP
#define GENALGO_ARGS_HPP

#include "evoConfig.hpp"
#include <tclap/CmdLine.h>

class Args {
public:
    Args();
    bool parseArgs(int argc, char *argv[], evoConfig &config);

private:
    void checkArgs();
    void fillAlgoConfig(evoConfig& config);
    void fillConfig(evoConfig &config);

    TCLAP::CmdLine m_cmd;
    TCLAP::ValueArg<unsigned int> m_genArg;
    TCLAP::ValueArg<unsigned int> m_popSize;
    TCLAP::ValueArg<unsigned int> m_tourSize;
    TCLAP::ValueArg<unsigned int> m_runs;
    TCLAP::ValueArg<unsigned int> m_threads;
    TCLAP::ValueArg<unsigned int> m_resetAfter;
    TCLAP::ValueArg<double> m_mutProb;
    TCLAP::ValueArg<double> m_crossProb;
    TCLAP::ValueArg<std::string> m_dir;
    TCLAP::ValueArg<std::string> m_outFile;
    TCLAP::SwitchArg m_prog;
};


#endif //GENALGO_ARGS_HPP
