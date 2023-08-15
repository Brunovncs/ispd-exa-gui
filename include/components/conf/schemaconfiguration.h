#pragma once
#include "components/conf/itemconfiguration.h"

class SchemaConfiguration : public ItemConfiguration
{
public:
    SchemaConfiguration(std::string name, unsigned id);

    unsigned    getId() override;
    std::string getName() override;

    void        setId(unsigned id) override;
    void        setName(std::string name) override;

private:
    std::string name;
    unsigned id;
};
