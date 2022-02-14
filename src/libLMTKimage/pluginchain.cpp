#include "pluginchain.h"

namespace image {

    PluginChain::~PluginChain()
    {

    }

    void image::PluginChain::operator()(Image& img)
    {
        for (size_t i = 0; i < chain.size(); i++)
        {
            if ((*this)[i] == nullptr) throw std::runtime_error("plugin chain: null operator");
            (*((*this)[i]))(img);
        }
    }

    ImageShader*& PluginChain::operator[](size_t idx)
    {
        if (idx >= chain.size()) throw std::out_of_range("Index out of range");
        //return *(chain.begin()+i);
        auto it = chain.begin()++;
        size_t i = 0;
        for (auto it = chain.begin(); it != chain.end(); ++it)
        {
            if (i++ == idx) return *it;
        }
    }

    void PluginChain::addEffect(ImageShader* fx, size_t passes)
    {
        if (!fx) return;
        for (size_t i = 0; i < passes; i++)
        {
            chain.push_back(fx);
        }
    }

    void PluginChain::addEffect(ImageShader* fx)
    {
        addEffect(fx, 1, chain.size());
    }

    void PluginChain::addEffect(ImageShader* fx, size_t passes, size_t idx)
    {
        auto it = chain.begin()++;
        size_t i = 0;
        while (it != chain.end())
        {
            ++it;
            if (i++ == idx) break;
        }
        for (size_t k = 0; k < passes; k++)
        {
            chain.insert(it, fx);
        }
    }

    void PluginChain::addEffects(std::vector<ImageShader*> fx)
    {
        // insert all elements
        chain.insert(chain.end(), fx.begin(), fx.end());
    }

    void PluginChain::removeEffect(ImageShader* fx)
    {
        if (fx) chain.remove(fx);
    }

    void PluginChain::removeEffect(size_t idx)
    {
        auto it = chain.begin()++;
        size_t i = 0;
        while (it != chain.end())
        {
            ++it;
            if (i++ == idx) break;
        }
        chain.erase(it);
    }

    size_t PluginChain::size()
    {
        return chain.size();
    }

    bool PluginChain::empty()
    {
        return chain.empty();
    }

}