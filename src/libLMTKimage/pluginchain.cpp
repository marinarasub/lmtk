#include "pluginchain.h"

namespace image {

    PluginChain::~PluginChain()
    {
        for (size_t i = 0; i < chain.size(); i++)
        {
            if (chain[i]) delete chain[i];
            chain[i] = nullptr;
        }
    }

    void image::PluginChain::operator()(Image& img)
    {
        for (size_t i = 0; i < chain.size(); i++)
        {
            if (chain[i] == nullptr) throw std::runtime_error("plugin chain: null operator");
            (*chain[i])(img);
        }
    }

    ImageShader* PluginChain::operator[](size_t i)
    {
        //if (i >= chain.size()) throw std::out_of_range("Index out of range");
        return chain[i];
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
        addEffect(fx, 1);
    }

    void PluginChain::addEffects(std::vector<ImageShader*> fx)
    {
        // insert all elements
        chain.insert(chain.end(), fx.begin(), fx.end());
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