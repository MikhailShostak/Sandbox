namespace Core
{

int Application::Run()
{
    Running = true;

    for (auto &component : Components)
    {
        component->Load(*this);
    }

    while (Running)
    {
        for (auto& component : Components)
        {
            if (component->Enabled)
            {
                component->Update(*this);
            }
        }
    }

    for (auto& component : Components)
    {
        component->Unload(*this);
    }

    return ErrorCode;
}

}
