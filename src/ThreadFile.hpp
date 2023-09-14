
#ifndef GENALGO_THREADFILE_HPP
#define GENALGO_THREADFILE_HPP


#include <string>
#include <fstream>
#include <mutex>

class ThreadFile {

public:
    ThreadFile(std::string inPath);

    void write(const std::string& data);

private:
    std::string m_path;
    std::ofstream m_stream;
    std::mutex m_writeMutex;
};


#endif //GENALGO_THREADFILE_HPP
