#include "ThreadFile.hpp"

#include <utility>

ThreadFile::ThreadFile(std::string inPath) :
    m_path(std::move(inPath))
{
    m_stream.open(m_path);
}

void ThreadFile::write(const std::string &data) {
    std::lock_guard<std::mutex> lock(m_writeMutex);
    m_stream << data;
}
