#pragma once

#include "components/item.h"
#include <memory>

class LinkIcon;
class Icon;
class Connection;
class Schema;

struct LinkConnections
{
    Connection *begin;
    Connection *end;
};

class Link : public Item
{
public:
    explicit Link(Schema         *schema,
         unsigned        id,
         const char     *name,
         LinkConnections connections);
    virtual ~Link();

    void addLine();
    void draw();
    void showConfiguration() override;

    Schema *schema;

    LinkConnections connections;

    std::unique_ptr<std::string> name;

    unsigned                  id;
    std::unique_ptr<LinkIcon> icon;
};
