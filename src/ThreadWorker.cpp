#include "ThreadWorker.hpp"

#include <utility>
#include "evoConfig.hpp"
#include "Instance.hpp"
#include "Evolution.hpp"
#include "Individual.hpp"

ThreadWorker::ThreadWorker(evoConfig &config, std::shared_ptr<ThreadFile> resFile,
                           const std::vector<std::string> &instances,
                           unsigned long start, unsigned long end) :
    m_instances(instances),
    m_config(config),
    m_resultFile(std::move(resFile)),
    m_start(start),
    m_end(end)
{
}

void ThreadWorker::solve() {
    for (unsigned long i = m_start; i < m_end; i++) {
        solveOne(m_instances[i]);
    }
}

void ThreadWorker::solveOne(const std::string& inFile) {
    for (int i = 0; i < m_config.runs; i++) {
        Instance instance(inFile);
        if (m_config.estimate) {
            doEstimation(instance);
        }
        Evolution evo = Evolution(instance, &m_config);
        Individual best = evo.doGenetics();
        std::ostringstream oss;
        if (!best.isValid()) {
            oss << instance.getID() << " " << -1 << " " << best << "0" << std::endl;
        } else {
            oss << instance.getID() << " " << std::to_string(best.getTrueFitness()) << " " << best << "0" << std::endl;
        }
        m_resultFile->write(oss.str());
    }
}

void ThreadWorker::doEstimation(Instance& instance) {
    Estimation estimations[3] = {
            {150, 1000, 2, 0.025}, // for uf20
            {250, 2000, 15, 0.025}, // for uf50
            {250, 2000, 20, 0.02}, // for the rest
    };
    if (instance.varCount() == 20) {
        fillAlgoConfig(estimations[0]);
    } else if (instance.varCount() == 50) {
        fillAlgoConfig(estimations[1]);
    } else {
        fillAlgoConfig(estimations[2]);
    }
}

void ThreadWorker::fillAlgoConfig(ThreadWorker::Estimation &estimation) {
    m_config.populationSize = estimation.population;
    m_config.generations = estimation.generations;
    m_config.tournamentSize = estimation.tournament;
    m_config.mutationProbability = estimation.mutation;
}
