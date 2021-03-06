template<class Action>
void JsonActionIOHandler<Action>::loadBindingsFile(const std::string& path, std::function<std::string(Action)> stringToAction)
{
    mPrimaryBindings.clear();
    mSecondaryBindings.clear();

    std::ifstream file(path);

    if(!file)
        throw fea::InputFileNotFoundException("Error! Entity file not found: " + path + '\n');

    Json::Value root;
    Json::Reader reader;

    reader.parse(file, root, false);
    file.close();

    std::string names[2] {"primary", "secondary"};

    for(int i = 0; i < 2; i++)
    {
        const Json::Value& array = root[names[i]];
        if(array.isArray())
        {
            for(const Json::Value& binding : array)
            {
                std::string type = binding["type"].asString();

                ActionTrigger tempTrigger;
                Action tempAction = stringToAction(binding["action"].asString());

                // TODO: std::stoi(Json::Value.asString()) needed?
                if(type == "keypress")
                {
                    tempTrigger.type = ActionTrigger::KEYPRESS;
                    tempTrigger.keyCode = (Keyboard::Code) std::stoi(binding["key"].asString());
                }
                else if(type == "keyrelease")
                {
                    tempTrigger.type = ActionTrigger::KEYRELEASE;
                    tempTrigger.keyCode = (Keyboard::Code) std::stoi(binding["key"].asString());
                }
                else if(type == "mousepress")
                {
                    tempTrigger.type = ActionTrigger::MOUSEPRESS;
                    tempTrigger.mouseButton = (Mouse::Button) std::stoi(binding["mousebutton"].asString());
                }
                else if(type == "mouserelease")
                {
                    tempTrigger.type = ActionTrigger::MOUSERELEASE;
                    tempTrigger.mouseButton = (Mouse::Button) std::stoi(binding["mousebutton"].asString());
                }
                else if(type == "gamepadpress")
                {
                    tempTrigger.type = ActionTrigger::GAMEPADPRESS;
                    tempTrigger.gamepadButton = (uint32_t) std::stoi(binding["gamepadbutton"].asString());
                    tempTrigger.gamepadId = (uint32_t) std::stoi(binding["gamepadid"].asString());
                }
                else if(type == "gamepadrelease")
                {
                    tempTrigger.type = ActionTrigger::GAMEPADRELEASE;
                    tempTrigger.gamepadButton = (uint32_t) std::stoi(binding["gamepadbutton"].asString());
                    tempTrigger.gamepadId = (uint32_t) std::stoi(binding["gamepadid"].asString());
                }

                mPrimaryBindings.emplace(tempTrigger, tempAction);
            }
        }
    }
}

template<class Action>
void JsonActionIOHandler<Action>::saveBindingsFile(const std::string& path, const std::map<ActionTrigger, Action>& primaryActions) const
{
    saveBindingsFile(path, primaryActions, std::map<ActionTrigger, Action>());
}

template<class Action>
void JsonActionIOHandler<Action>::saveBindingsFile(const std::string& path, const std::map<ActionTrigger, Action>& primaryActions, const std::map<ActionTrigger, Action>& secondaryActions) const
{
    std::ofstream file(path);

    if(!file)
        throw fea::InputFileNotFoundException("Error! Action bindings file not found: " + path + '\n');

    Json::Value root;
    
    const std::map<ActionTrigger, Action>* actions[2] {&primaryActions, &secondaryActions};
    Json::Value arrays[2];
    std::string names[2] {"primary", "secondary"};
    
    for(int i = 0; i < 2; i++)
    {
        for(auto binding : *actions[i])
        {
            Json::Value bindingEntry;

            switch(binding.first.type)
            {
                case ActionTrigger::KEYPRESS:
                    bindingEntry["type"] = "keypress";
                    bindingEntry["key"] = std::to_string(binding.first.keyCode);
                    break;
                case ActionTrigger::KEYRELEASE:
                    bindingEntry["type"] = "keyrelease";
                    bindingEntry["key"] = std::to_string(binding.first.keyCode);
                    break;
                case ActionTrigger::MOUSEPRESS:
                    bindingEntry["type"] = "mousepress";
                    bindingEntry["mousebutton"] = std::to_string(binding.first.mouseButton);
                    break;
                case ActionTrigger::MOUSERELEASE:
                    bindingEntry["type"] = "mouserelease";
                    bindingEntry["mousebutton"] = std::to_string(binding.first.mouseButton);
                    break;
                case ActionTrigger::GAMEPADPRESS:
                    bindingEntry["type"] = "gamepadpress";
                    bindingEntry["gamepadid"] = std::to_string(binding.first.gamepadId);
                    bindingEntry["gamepadbutton"] = std::to_string(binding.first.gamepadButton);
                    break;
                case ActionTrigger::GAMEPADRELEASE:
                    bindingEntry["type"] = "gamepadrelease";
                    bindingEntry["gamepadid"] = std::to_string(binding.first.gamepadId);
                    bindingEntry["gamepadbutton"] = std::to_string(binding.first.gamepadButton);
                    break;
                default:
                    break;
            }

            std::stringstream ss;
            ss << binding.second;

            bindingEntry["action"] = ss.str();

            arrays[i].append(bindingEntry);
        }

        if(!actions[i]->empty())
            root[names[i]] = arrays[i];
    }

    // TODO: use FastWriter or StyledWriter?
    Json::FastWriter writer;
    file << writer.write(root);

    file.close();
}

template<class Action>
const std::map<ActionTrigger, Action>& JsonActionIOHandler<Action>::getPrimaryBindings() const
{
    return mPrimaryBindings;
}

template<class Action>
const std::map<ActionTrigger, Action>& JsonActionIOHandler<Action>::getSecondaryBindings() const
{
    return mSecondaryBindings;
}
