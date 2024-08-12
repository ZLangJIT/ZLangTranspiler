#ifndef ZLANG_STREAM_H
#define ZLANG_STREAM_H

#include <fstream>
#include <memory>
#include <functional>

#include <mmap_iterator.h>

struct Stream {
    std::string path = "unknown";
    std::shared_ptr<MMapHelper> map;
    std::shared_ptr<MMapIterator> map_begin;
    std::shared_ptr<MMapIterator> map_end;
    std::shared_ptr<MMapIterator> map_it;

    inline bool open(const char * path) {
        this->path = path;
        map.reset(new MMapHelper(path, 'r'));
        map_begin.reset(new MMapIterator(*map, 0));
        map_end.reset(new MMapIterator(*map, map->length()));
        map_it.reset(new MMapIterator(*map, 0));
        return map_it->is_open();
    }
    
    inline const MMapIterator & begin() { return *map_begin; }
    inline const MMapIterator & end() { return *map_end; }
    inline MMapIterator & iter() { return *map_it; }
};

#endif