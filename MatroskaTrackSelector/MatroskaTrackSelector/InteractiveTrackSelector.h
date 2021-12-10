#pragma once

#include <map>
#include <set>
#include <fstream>

#include "Common.h"
#include "TrackPrioritizer.h"
#include "TrackManager.h"

DECL_EXCEPTION(FileSelectionError);

class InteractiveTrackSelector
{
public:
    InteractiveTrackSelector(const string& track_selection_rules_file);

    InteractiveTrackSelector(const InteractiveTrackSelector&) = delete;
    InteractiveTrackSelector& operator=(const InteractiveTrackSelector&) = delete;

public:
    void select_default_tracks_interactively(std::fstream& file_stream, const wstring& file_name);

private:
    using TrackGroupChoices = std::map<vector<TrackEntry>, size_t>;
    using TrackSingleChoices = std::set<TrackEntry>;

private:
    static TrackEntry* _s_select_default_track_interactively(
        const Tracks& tracks,
        const string& track_set_name,
        const TrackPriorityDescriptor& track_priorities,
        const TrackGroupChoices& track_group_choices,
        const TrackSingleChoices& track_single_choices
    );

private:
    const TrackPrioritizer m_track_prioritizer;

    // Maps between track groups and indices of the chosen track in those groups
    TrackGroupChoices m_subtitle_group_choices;
    TrackGroupChoices m_audio_group_choices;

    // Contains 
    TrackSingleChoices m_single_subtitle_choices;
    TrackSingleChoices m_single_audio_choices;
};

