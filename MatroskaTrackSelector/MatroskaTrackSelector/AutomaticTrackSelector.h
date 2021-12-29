#pragma once

#include "Common.h"
#include "TrackManager.h"

/*
 * This module is a wrapper for TrackManager that lets the user select a subtile track and an
 * audio track seperately instead using the `set_default_tracks` function of TrackManager.
 */
class AutomaticTrackSelector : public TrackManager
{
public:
    explicit AutomaticTrackSelector(const wstring& file) : 
        TrackManager(file),
        m_selected_subtitle_track_index(static_cast<size_t>(-1)),
        m_selected_audio_track_index(static_cast<size_t>(-1))
    {}

    AutomaticTrackSelector(const AutomaticTrackSelector&) = delete;
    AutomaticTrackSelector& operator=(const AutomaticTrackSelector&) = delete;

public:
    // Mark a track for selection and if both tracks are marked for selection, actually perform the selection
    // and return true. Otherwise, only one track type has been marked for selection and no actual selection
    // has been made, return false.
    bool mark_subtitle_track_for_selection(const size_t track_index);
    bool mark_audio_track_for_selection(const size_t track_index);

private:
    size_t m_selected_subtitle_track_index;
    size_t m_selected_audio_track_index;
};

