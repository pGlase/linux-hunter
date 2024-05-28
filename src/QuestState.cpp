#include "QuestState.hpp"

bool IsQuestFinished(QuestState state)
{
    switch(state){
    case QuestState::Success:
        [[fallthrough]];
    case QuestState::Completed:
        [[fallthrough]];
    case QuestState::Abandon:
        [[fallthrough]];
    case QuestState::Quit:
        return true;
    default:
        return false;
    }
}

