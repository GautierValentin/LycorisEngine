#include "ECS/Entity.h"
#include "components/Script.h"

Script::Script(ScriptDesc desc) : Component(desc.entity), _win(desc.window)
{
}

Script::~Script()
{
}
