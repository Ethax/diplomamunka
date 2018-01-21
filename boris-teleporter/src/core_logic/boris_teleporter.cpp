#include <core_logic/boris_teleporter.h>

using namespace diplomamunka::boris;
namespace fs = boost::filesystem;

PathReplacer::PathReplacer() :
        rootDirectory(fs::current_path()) {
}

PathReplacer::PathReplacer(const std::set<Path>& replacementPaths, const Path& rootDirectory) :
        replacementPaths(replacementPaths),
        rootDirectory(rootDirectory) {
}

void PathReplacer::setReplacementPaths(const std::set<Path>& replacementPaths) {
    this->replacementPaths = replacementPaths;
}

void PathReplacer::setRootDirectory(const Path& rootDirectory) {
    this->rootDirectory = rootDirectory;
}

std::size_t PathReplacer::replacePaths(std::istream& inStream, std::ostream& outStream) {

}

bool PathReplacer::operator==(const PathReplacer& other) const {
    return replacementPaths == other.replacementPaths && rootDirectory == other.rootDirectory;
}

bool PathReplacer::operator!=(const PathReplacer& other) const {
    return !(*this == other);
}


