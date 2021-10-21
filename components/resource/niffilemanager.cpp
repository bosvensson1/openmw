#include "niffilemanager.hpp"

#include <osg/Object>
#include <osg/Stats>

#include <components/vfs/manager.hpp>

#include "objectcache.hpp"

namespace Resource
{

    class NifFileHolder : public osg::Object
    {
    public:
        NifFileHolder(const Nif::NIFFilePtr& file)
            : mNifFile(file)
        {
        }
        NifFileHolder(const NifFileHolder& copy, const osg::CopyOp& copyop)
            : mNifFile(copy.mNifFile)
        {
        }

        NifFileHolder()
        {
        }

        META_Object(Resource, NifFileHolder)

        Nif::MutableNIFFilePtr mNifFile;
    };

    NifFileManager::NifFileManager(const VFS::Manager *vfs)
        : ResourceManager(vfs)
    {
    }

    NifFileManager::~NifFileManager()
    {
    }

    Nif::NIFFilePtr NifFileManager::get(const std::string &name)
    {
        osg::ref_ptr<osg::Object> obj = mCache->getRefFromObjectCache(name);
        if (obj)
            return static_cast<NifFileHolder*>(obj.get())->mNifFile;
        else
        {
            Nif::MutableNIFFilePtr file (new Nif::NIFFile(mVFS->get(name), name));
            obj = new NifFileHolder(file);
            mCache->addEntryToObjectCache(name, obj);
            return file;
        }
    }

    Nif::MutableNIFFilePtr NifFileManager::consume(const std::string &name)
    {
        osg::ref_ptr<osg::Object> obj = mCache->consumeRefFromObjectCache(name);
        if (obj)
            return static_cast<NifFileHolder*>(obj.get())->mNifFile;
        else
            return Nif::MutableNIFFilePtr(new Nif::NIFFile(mVFS->get(name), name);
    }

    void NifFileManager::reportStats(unsigned int frameNumber, osg::Stats *stats) const
    {
        stats->setAttribute(frameNumber, "Nif", mCache->getCacheSize());
    }

}
