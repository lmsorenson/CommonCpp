// Copyright 2020, Lucas Sorenson, All rights reserved.
#pragma once
#include "../../abstract/semantic_analyzer/public/SemanticNet.hpp"

namespace sdg {

class CSVNet : public SemanticNet
{

public:

private:
    int16_t classify(std::shared_ptr<const PropertySetBase> properties) const override;
    int8_t compare_semantics(const std::shared_ptr<const LexicalItem> item, std::vector<std::string> &err) override;
    ItemPayload decompose(::std::shared_ptr<LexicalItem> item) override;
    virtual std::shared_ptr<LexicalItem> MakeLexicalItem(ItemType type, std::shared_ptr<const NodeProperties> props, std::vector<std::string> &error) override;
};

}// namespace sdg