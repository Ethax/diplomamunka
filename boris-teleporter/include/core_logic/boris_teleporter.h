#ifndef BORIS_TELEPORTER_H
#define BORIS_TELEPORTER_H

#include <iostream>
#include <set>
#include <boost/filesystem.hpp>

namespace diplomamunka { namespace boris {

using Path = boost::filesystem::path;

class PathReplacer {
public:    
    PathReplacer();
    PathReplacer(const std::set<Path>& replacementPaths, const Path& rootDirectory);

    void setReplacementPaths(const std::set<Path>& replacementPaths);
    void setRootDirectory(const Path& rootDirectory);

    std::size_t replacePaths(std::istream& inStream, std::ostream& outStream);

    bool operator==(const PathReplacer& other) const;
    bool operator!=(const PathReplacer& other) const;

private:
    std::set<Path> replacementPaths;
    Path rootDirectory;
};

}}

#endif /* BORIS_TELEPORTER_H */
