#include "Args.hpp"
#include <filesystem>

namespace fs = std::filesystem;

bool Args::parseArgs(int argc, char *argv[], evoConfig &config) {
    try {
        m_cmd.parse(argc, argv);
        checkArgs();
    } catch (TCLAP::ArgException& ex) {
        std::cerr << "error: " << ex.error() << " for " << ex.argId() << std::endl;
        return false;
    }
    if (m_genArg.isSet()
        || m_popSize.isSet()
        || m_tourSize.isSet()
        || m_mutProb.isSet()) {
        fillAlgoConfig(config);
    } else {
        config.estimate = true;
    }
    fillConfig(config);
    return true;
}

Args::Args() :
        m_cmd("Solver for weighted SAT using genetic algorithm", ' ', "1.0"),
        m_genArg("g", "generations", "generations count",
             false, 2000, "Specify generations count", m_cmd),
        m_popSize("p", "population", "population size",
             false, 250, "Specify population size", m_cmd),
        m_tourSize("T", "tournament", "tournament size",
               false, 20, "Specify tournament size", m_cmd),
        m_runs("r", "runs", "runs on instance",
               false, 1, "Specify how many times to run on one instance", m_cmd),
        m_threads("t", "threads", "threads count",
           false, 1, "Specify how many threads to run", m_cmd),
        m_resetAfter("e", "reset", "specify when reset",
              false, 10, "Specify how many generation can be same before reset", m_cmd),
        m_mutProb("m", "mutation", "mutation probability",
              false, 0.02, "Specify mutation probability", m_cmd),
        m_crossProb("c", "cross", "crossover probability",
                  false, 1, "Specify crossover probability", m_cmd),
        m_dir("d", "directory", "input directory",
          true, "",
          "Specify input directory", m_cmd),
        m_outFile("o", "outFile", "output file",
              false, "",
              "save output to specified file", m_cmd),
        m_prog("s", "progress", "Record progress to file", m_cmd, false)
{
}

void Args::checkArgs() {
    if (m_genArg.getValue() > maxConfig::maxGenerations) {
        throw TCLAP::ArgException("Generations can be max "+std::to_string(maxConfig::maxGenerations),
                                  m_genArg.shortID());
    }
    if (m_popSize.getValue() > maxConfig::maxPopulationSize) {
        throw TCLAP::ArgException("Population size can be max "+std::to_string(maxConfig::maxPopulationSize),
                                  m_popSize.shortID());
    }
    if (m_tourSize.getValue() > maxConfig::maxTournamentSize) {
        throw TCLAP::ArgException("Population size can be max "+std::to_string(maxConfig::maxTournamentSize),
                                  m_tourSize.shortID());
    }
    if (!exists(fs::path(m_dir.getValue()))) {
        throw TCLAP::ArgException("\""+m_dir.getValue()+"\""+" is not valid directory",
                                  m_dir.shortID());
    }
}

void Args::fillConfig(evoConfig& config) {
    config.runs = m_runs.getValue();
    config.resetAfter = m_resetAfter.getValue();
    config.crossoverProbability = m_crossProb.getValue();
    config.instancesDir = std::move(m_dir.getValue());
    config.threads = m_threads.getValue();
    config.progress = m_prog.getValue();
    if (m_outFile.getValue().empty()) {
        config.outFile = config.instancesDir+"-opt-GA.dat";
    } else {
        config.outFile = std::move(m_outFile.getValue());
    }
}

void Args::fillAlgoConfig(evoConfig &config) {
    config.estimate = false;
    config.generations = m_genArg.getValue();
    config.populationSize = m_popSize.getValue();
    config.tournamentSize = m_tourSize.getValue();
    config.mutationProbability = m_mutProb.getValue();
}
